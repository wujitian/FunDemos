#include <iostream>
using namespace std;

#include "vgl.h"
#include "vapp.h"
#include "vmath.h"
#include "targa.h"

#include "LoadShaders.h"

#define POINT_COUNT 400

static inline float random_float()
{
    float res;
    unsigned int tmp;
    static unsigned int seed = 0x13371337;

    seed *= 16807;

    tmp = seed ^ (seed >> 4) ^ (seed << 15);

    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    return (res - 1.0f);
}

BEGIN_APP_DECLARATION(PointSpriteExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);

    // Member variables
    float aspect = 1.0f;
    GLuint render_prog;
    GLuint vao[1];
    GLuint vbo[1];
    GLuint ebo[1];
    GLuint sprite_texture;

    GLint render_model_matrix_loc;
    GLint render_projection_matrix_loc;
END_APP_DECLARATION()

DEFINE_APP(PointSpriteExample, "Point Sprite Example")

void PointSpriteExample::Initialize(const char * title)
{
    base::Initialize(title);
    
    GLenum format;
    int width, height;
    unsigned char * data;
    
    glGenTextures(1, &sprite_texture);
    glBindTexture(GL_TEXTURE_2D, sprite_texture);           // 2D  -->  sampler2D
    
    // new a buffer in load_targa. so need delete outside the function.
    data = load_targa("../media/sprite.tga", format, width, height);
    
    // changable texture allocate function.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    
    delete [] data;
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    static ShaderInfo shader_info[] =
    {
        { GL_VERTEX_SHADER, "../shaders/pointsprites/pointsprites.vs.glsl", 0 },
        { GL_FRAGMENT_SHADER, "../shaders/pointsprites/pointsprites.fs.glsl", 0 },
        //{ GL_FRAGMENT_SHADER, "../shaders/pointsprites/pointsprites2.fs.glsl", 0 },
        { GL_NONE, NULL, 0 }
    };

    render_prog = LoadShaders(shader_info);

    glUseProgram(render_prog);
    
    // "model_matrix" is actually an array of 4 matrices
    render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");
    
    // A single triangle
    static vmath::vec4 * vertex_positions;
    
    // Set up the vertex attributes
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, POINT_COUNT * sizeof(vmath::vec4), NULL, GL_STATIC_DRAW);
    
    //vertex_positions = (vec4 *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    vertex_positions = (vmath::vec4 *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    for (int n = 0; n < POINT_COUNT; n++)
    {
        vertex_positions[n] = vmath::vec4(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, 
                              random_float() * 2.0f - 1.0f, 1.0f);
        cout << "n=" << n << ",value=" << vertex_positions[n][0] << "," << vertex_positions[n][1]
             << "," << vertex_positions[n][2] << "," << vertex_positions[n][3] << endl;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void PointSpriteExample::Display(bool auto_redraw)
{
    float t = float(app_time() & 0x1FFF) / float(0x1FFF);
    t = t * 100;
    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

    vmath::mat4 model_matrix;

    // Setup
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set up the model and projection matrix
    vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 8.0f));
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);
    
    glBindTexture(GL_TEXTURE_2D, sprite_texture);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(32.0f);
    
    // Draw Arrays...
    //model_matrix = vmath::translate(0.0f, 0.0f, -2.0f); 
    model_matrix = vmath::translate(0.0f, 0.0f, -2.0f) *
                   vmath::rotate(t * 360.0f, Y) * vmath::rotate(t * 720.0f, Z);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
    glDrawArrays(GL_POINTS, 0, POINT_COUNT);

    base::Display();
}

void PointSpriteExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(render_prog);
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, vbo);
}
void PointSpriteExample::Resize(int width, int height)
{
    glViewport(0, 0 , width, height);

    aspect = float(height) / float(width);
}

