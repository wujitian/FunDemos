#include <iostream>
using namespace std;

#include "vgl.h"
#include "vapp.h"
#include "vmath.h"

#include "LoadShaders.h"

BEGIN_APP_DECLARATION(InstancingExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);

    // Member variables
    float aspect = 1.0f;
    GLuint render_prog;

END_APP_DECLARATION()

DEFINE_APP(InstancingExample, "Drawing Commands Example")

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
    
}

void InstancingExample::Display(bool auto_redraw)
{
    float t = float(app_time() & 0x1FFF) / float(0x1FFF) * 20.0;
    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

    base::Display();
}

void InstancingExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(render_prog);
    //glDeleteVertexArrays(1, vao);
    //glDeleteBuffers(1, vbo);
}

void InstancingExample::Resize(int width, int height)
{
    glViewport( 0, 0, width, height);

    aspect = float(height) / float(width);
    printf("aspect = %f\n", aspect);
}

