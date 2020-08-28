#include <iostream>
#include <math.h>
using namespace std;

#include "vgl.h"
#include "vapp.h"
#include "vmath.h"

#include "LoadShaders.h"

#define PI 3.1415926f
#define NUM_POINTS 64
#define OUTER_RADIUS 2.0f

BEGIN_APP_DECLARATION(WanHuaTongExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);

    // Member variables
    GLuint draw_prog;
    GLuint vao_outer;
    GLuint vbo_outer;

    GLint model_matrix_loc;
    GLint projection_matrix_loc;

END_APP_DECLARATION()

DEFINE_APP(WanHuaTongExample, "Wan Hua Tong Example")

void WanHuaTongExample::Initialize(const char * title)
{
    base::Initialize(title);

    ShaderInfo shader_info[] =
    {
        { GL_VERTEX_SHADER, "../shaders/draw.vs.glsl" },
        { GL_FRAGMENT_SHADER, "../shaders/draw.fs.glsl" },
        { GL_NONE, NULL }
    };

    draw_prog = LoadShaders(shader_info);
    
    model_matrix_loc = glGetUniformLocation(draw_prog, "model_matrix");
    projection_matrix_loc = glGetUniformLocation(draw_prog, "projection_matrix");

    glUseProgram(draw_prog);

    // Generate circle points
    GLfloat * vertex_positions = new GLfloat[NUM_POINTS*4];
    for (int i = 0; i < NUM_POINTS; ++i)
    {
        float angle = 2.0f * PI / NUM_POINTS * i;    
        GLfloat x = OUTER_RADIUS * cos(angle);
        GLfloat y = OUTER_RADIUS * sin(angle);

        vertex_positions[i*4 + 0] = x;
        vertex_positions[i*4 + 1] = y;
        vertex_positions[i*4 + 2] = 0.0f;
        vertex_positions[i*4 + 3] = 1.0f;
    }
    
    // Set up the vertex attributes
    glGenVertexArrays(1, &vao_outer);
    glBindVertexArray(vao_outer);
    glGenBuffers(1, &vbo_outer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_outer);
    glBufferData(GL_ARRAY_BUFFER, NUM_POINTS*16, vertex_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    delete []vertex_positions;
}

void WanHuaTongExample::Display(bool auto_redraw)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup
    glEnable(GL_CULL_FACE);             //open culling
    glDisable(GL_DEPTH_TEST);

    glUseProgram(draw_prog);

    // Set up the model and projection matrix
    vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 500.0f));
    vmath::mat4 model_matrix = vmath::translate(0.0f, 0.0f, -5.0f);

    glBindVertexArray(vao_outer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_outer);

    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, projection_matrix);
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, model_matrix);
    glDrawArrays(GL_LINE_LOOP, 0, NUM_POINTS);

    base::Display();
}

void WanHuaTongExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(draw_prog);
    glDeleteVertexArrays(1, &vao_outer);
    glDeleteBuffers(1, &vbo_outer);
}
void WanHuaTongExample::Resize(int width, int height)
{
    glViewport(0, 0 , width, height);
}

