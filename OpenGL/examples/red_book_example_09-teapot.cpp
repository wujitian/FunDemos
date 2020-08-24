#include <iostream>
using namespace std;

#include "vgl.h"
#include "vapp.h"
#include "vmath.h"

#include "LoadShaders.h"
#include "Teapot.h"

BEGIN_APP_DECLARATION(TeapotExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);

    // Member variables
    float aspect = 1.0f;

    GLuint  vao;
    GLuint  program;
    GLuint  PLoc;  // Projection matrix
    GLuint  InnerLoc;  // Inner tessellation paramter
    GLuint  OuterLoc;  // Outer tessellation paramter
    
    GLfloat  Inner = 10.0f;
    GLfloat  Outer = 10.0f;

END_APP_DECLARATION()

DEFINE_APP(TeapotExample, "Teapot Example")

void TeapotExample::Initialize(const char * title)
{
    base::Initialize(title);
    
    // Create a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    
    // Create and initialize a buffer object
    enum { ArrayBuffer, ElementBuffer, NumVertexBuffers };
    GLuint buffers[NumVertexBuffers];
    glGenBuffers( NumVertexBuffers, buffers );
    glBindBuffer( GL_ARRAY_BUFFER, buffers[ArrayBuffer] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(TeapotVertices),
                  TeapotVertices, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[ElementBuffer] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(TeapotIndices),
                  TeapotIndices, GL_STATIC_DRAW );
    
    // Load shaders and use the resulting shader program
    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER,          "../../shaders/teapot/teapot.vert" },
        { GL_TESS_CONTROL_SHADER,    "../../shaders/teapot/teapot.cont" },
        { GL_TESS_EVALUATION_SHADER, "../../shaders/teapot/teapot.eval" },
        { GL_FRAGMENT_SHADER,        "../../shaders/teapot/teapot.frag" },
        { GL_NONE, NULL }
    };

    program = LoadShaders( shaders );
    glUseProgram( program );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
    
    PLoc = glGetUniformLocation( program, "P" );
    InnerLoc = glGetUniformLocation( program, "Inner" );
    OuterLoc = glGetUniformLocation( program, "Outer" );

    glUniform1f( InnerLoc, Inner );
    glUniform1f( OuterLoc, Outer );
        
    vmath::mat4 modelview = vmath::translate( -0.2625f, -1.575f, -1.0f );
    modelview *= vmath::translate( 0.0f, 0.0f, -7.5f );
    glUniformMatrix4fv( glGetUniformLocation( program, "MV" ),
                        1, GL_TRUE, modelview );
    
    glPatchParameteri( GL_PATCH_VERTICES, NumTeapotVerticesPerPatch );
    
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
}

void TeapotExample::Display(bool auto_redraw)
{
    vmath::mat4 projection = vmath::perspective( 60.0, aspect, 5, 10 );
    glUniformMatrix4fv( PLoc, 1, GL_TRUE, projection );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDrawElements( GL_PATCHES, NumTeapotVertices,
                    GL_UNSIGNED_INT, BUFFER_OFFSET(0) );
                
    //GLenum mode = GL_LINE;
    //mode = ( mode == GL_FILL ? GL_LINE : GL_FILL );
    //glPolygonMode( GL_FRONT_AND_BACK, mode );

    base::Display();
}

void TeapotExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vao);
    //glDeleteBuffers(1, vbo);
}
void TeapotExample::Resize(int width, int height)
{
    glViewport(0, 0 , width, height);

    aspect = float(height) / float(width);
    printf("aspect = %f\n", aspect);
}

