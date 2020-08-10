#include <iostream>
using namespace std;

#include "vgl.h"
#include "vapp.h"
#include "vmath.h"
#include "vermilion.h"
#include "LoadShaders.h"

BEGIN_APP_DECLARATION(LoadTextureExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);

    // Member variables
    float aspect = 1.0f;
    GLuint base_prog;
    GLuint vao;

    GLuint quad_vbo;

    GLuint tex;

END_APP_DECLARATION()

DEFINE_APP(LoadTextureExample, "Load Texture Example")

void LoadTextureExample::Initialize(const char * title)
{
    base::Initialize(title);
    
    base_prog = glCreateProgram();

    static const char quad_shader_vs[] =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec2 in_position;\n"
        "layout (location = 1) in vec2 in_tex_coord;\n"
        "\n"
        "out vec2 tex_coord;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = vec4(in_position, 0.5, 1.0);\n"
        "    tex_coord = in_tex_coord;\n"
        "}\n"
    ;

    static const char quad_shader_fs[] =
        "#version 330 core\n"
        "\n"
        "in vec2 tex_coord;\n"
        "\n"
        "layout (location = 0) out vec4 color;\n"
        "\n"
        "uniform sampler2D tex;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    color = texture(tex, tex_coord);\n"
        "}\n"
    ;

    vglAttachShaderSource(base_prog, GL_VERTEX_SHADER, quad_shader_vs);
    vglAttachShaderSource(base_prog, GL_FRAGMENT_SHADER, quad_shader_fs);
    
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    
    static const GLfloat quad_data[] =
    {
         1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, 1.0f,
         1.0f, 1.0f,

         0.0f, 0.0f,
         1.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(8 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glLinkProgram(base_prog);
    
    char buf[1024];
    glGetProgramInfoLog(base_prog, 1024, NULL, buf);
    
    vglImageData image;

    tex = vglLoadTexture("../media/test.dds", 0, &image);

    glTexParameteri(image.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    vglUnloadImage(&image);
}
void LoadTextureExample::Display(bool auto_redraw)
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);
    glUseProgram(base_prog);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    base::Display();
}

void LoadTextureExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(base_prog);
    glDeleteTextures(1, &tex);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &quad_vbo);
}
void LoadTextureExample::Resize(int width, int height)
{
    glViewport(0, 0 , width, height);

    aspect = float(height) / float(width);
    printf("aspect = %f\n", aspect);
}

