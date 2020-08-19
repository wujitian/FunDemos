#include <iostream>
using namespace std;

#include "vgl.h"
#include "vapp.h"
#include "vmath.h"
#include "vbm.h"

#include "LoadShaders.h"

#define INSTANCE_COUNT 200

BEGIN_APP_DECLARATION(InstancingExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);

    // Member variables
    float aspect = 1.0f;
    GLuint render_prog;
    GLuint weight_vbo;
    GLuint color_vbo;
    
    GLint render_model_matrix_loc;
    GLint render_projection_matrix_loc;
    
    VBObject object;
END_APP_DECLARATION()

DEFINE_APP(InstancingExample, "Instancing Example")

void InstancingExample::Initialize(const char * title)
{
    base::Initialize(title);
    
    // Create the program for rendering the model
    render_prog = glCreateProgram();

    // This is the rendering vertex shader
    static const char render_vs[] =
        "#version 330\n"
        "\n"
        // Uniforms
        "uniform mat4 model_matrix[4];\n"
        "uniform mat4 projection_matrix;\n"
        "\n"
        // Regular vertex attributes
        "layout (location = 0) in vec4 position;\n"
        "layout (location = 1) in vec3 normal;\n"
        "\n"
        // Instanced vertex attributes
        "layout (location = 3) in vec4 instance_weights;\n"
        "layout (location = 4) in vec4 instance_color;\n"
        "\n"
        // Outputs to the fragment shader
        "out vec3 vs_fs_normal;\n"
        "out vec4 vs_fs_color;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    int n;\n"
        "    mat4 m = mat4(0.0);\n"
        "    vec4 pos = position;\n"
        // Normalize the weights so that their sum total is 1.0
        "    vec4 weights = normalize(instance_weights);\n"
        "    for (n = 0; n < 4; n++)\n"
        "    {\n"
        // Calulate a weighted average of the matrices
        "        m += (model_matrix[n] * weights[n]);\n"
        "    }\n"
        // Use that calculated matrix to transform the object.
        "    vs_fs_normal = normalize((m * vec4(normal, 0.0)).xyz);\n"
        "    vs_fs_color = instance_color;\n"
        "    gl_Position = projection_matrix * (m * pos);\n"
        "}\n";

    // Simple fragment shader
    static const char render_fs[] =
        "#version 330\n"
        "\n"
        "layout (location = 0) out vec4 color;\n"
        "\n"
        "in vec3 vs_fs_normal;\n"
        "in vec4 vs_fs_color;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    color = vs_fs_color * (0.1 + abs(vs_fs_normal.z)) + vec4(0.8, 0.9, 0.7, 1.0) * pow(abs(vs_fs_normal.z), 40.0);\n"
        "}\n";

    // Compile and link like normal
    vglAttachShaderSource(render_prog, GL_VERTEX_SHADER, render_vs);
    vglAttachShaderSource(render_prog, GL_FRAGMENT_SHADER, render_fs);

    glLinkProgram(render_prog);
    glUseProgram(render_prog);
    
    // "model_matrix" is actually an array of 4 matrices
    render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");
    
    // Load the object
    object.LoadFromVBM("../media/armadillo_low.vbm", 0, 1, 2);
    
    // Bind its vertex array object so that we can append the instanced attributes
    object.BindVertexArray();
    
    // Generate the colors of the objects
    vmath::vec4 colors[INSTANCE_COUNT];

    for (int n = 0; n < INSTANCE_COUNT; n++)
    {
        float a = float(n) / 4.0f;
        float b = float(n) / 5.0f;
        float c = float(n) / 6.0f;

        colors[n][0] = 0.5f * (sinf(a + 1.0f) + 1.0f);
        colors[n][1] = 0.5f * (sinf(b + 2.0f) + 1.0f);
        colors[n][2] = 0.5f * (sinf(c + 3.0f) + 1.0f);
        colors[n][3] = 1.0f;
    }
    
    // Create and allocate the VBO to hold the weights
    // Notice that we use the 'colors' array as the initial data, but only because
    // we know it's the same size.
    glGenBuffers(1, &weight_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, weight_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);

    // Here is the instanced vertex attribute - set the divisor
    glVertexAttribDivisor(3, 1);
    // It's otherwise the same as any other vertex attribute - set the pointer and enable it
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(3);

    // Same with the instance color array
    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glVertexAttribDivisor(4, 1);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(4);
    
    // Done (unbind the object's VAO)
    glBindVertexArray(0);
}

void InstancingExample::Display(bool auto_redraw)
{
    //float t = float(app_time() & 0x1FFF) / float(0x1FFF) * 200.0;
    float t = float(app_time()) / 1000000.0;
    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);
    
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // Set four model matrices
    vmath::mat4 model_matrix[4];

    for (int n = 0; n < 4; n++)
    {
        //model_matrix[n] = (vmath::scale(5.0f) *
        //                   vmath::rotate(t * 360.0f * 40.0f + float(n + 1) * 29.0f, 0.0f, 1.0f, 0.0f) *
        //                   vmath::rotate(t * 360.0f * 20.0f + float(n + 1) * 35.0f, 0.0f, 0.0f, 1.0f) *
        //                   vmath::rotate(t * 360.0f * 30.0f + float(n + 1) * 67.0f, 0.0f, 1.0f, 0.0f) *
        //                   vmath::translate((float)n * 10.0f - 15.0f, 0.0f, 0.0f) *
        //                   vmath::scale(0.01f));
        model_matrix[n] = (vmath::scale(5.0f) *
                           vmath::rotate(t * 10.0f + float(n + 1) * 29.0f, 0.0f, 1.0f, 0.0f));
    }
    glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, model_matrix[0]);

    // Set up the projection matrix
    vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 5000.0f) * 
                                  //vmath::translate(0.0f, 0.0f, -100.0f));
                                  vmath::translate(0.0f, 0.0f, -20.0f));
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);
    
    // Activate instancing program
    glUseProgram(render_prog);
    
    // Render INSTANCE_COUNT objects
    object.Render(0, INSTANCE_COUNT);

    base::Display();
}

void InstancingExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(render_prog);
    glDeleteBuffers(1, &weight_vbo);
    glDeleteBuffers(1, &color_vbo);
}

void InstancingExample::Resize(int width, int height)
{
    glViewport( 0, 0, width, height);

    aspect = float(height) / float(width);
    printf("aspect = %f\n", aspect);
}

