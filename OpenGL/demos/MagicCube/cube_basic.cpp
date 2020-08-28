/*
 * Progarm Name: cube_basic.cpp
 * Created Time: 2020-08-24 19:05:41
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include "cube_basic.hpp"
#include <iostream>

using std::cout;
using std::endl;

CubeBasic::CubeBasic(float x, float y, float z, vec3 color_front, vec3 color_back,
                     vec3 color_top, vec3 color_bottom, vec3 color_left, vec3 color_right)
    : x_(x), y_(y), z_(z), 
      color_front_(color_front), color_back_(color_back),
      color_top_(color_top), color_bottom_(color_bottom), 
      color_left_(color_left), color_right_(color_right)
{
}

CubeBasic::~CubeBasic(void)
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void CubeBasic::SetCenterCoords(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}
    
void CubeBasic::SetColors(vec3 color_front, vec3 color_back, vec3 color_top, vec3 color_bottom,
    vec3 color_left, vec3 color_right)
{
    color_front_ = color_front;
    color_back_ = color_back;
    color_top_ = color_top;
    color_bottom_ = color_bottom;
    color_left_ = color_left;
    color_right_ = color_right;
}

void CubeBasic::Init(GLuint program)
{
    program_ = program;

    glUseProgram(program_);

    model_matrix_ = glGetUniformLocation(program_, "model_matrix");
    projection_matrix_ = glGetUniformLocation(program_, "projection_matrix");

    GLfloat cube_vertices[] =
    {
        x_-1.0f, y_-1.0f, z_-1.0f, 1.0f, x_+1.0f, y_+1.0f, z_-1.0f, 1.0f, x_+1.0f, y_-1.0f, z_-1.0f, 1.0f,  // back  
        x_+1.0f, y_+1.0f, z_-1.0f, 1.0f, x_-1.0f, y_-1.0f, z_-1.0f, 1.0f, x_-1.0f, y_+1.0f, z_-1.0f, 1.0f,  
        x_-1.0f, y_-1.0f, z_-1.0f, 1.0f, x_+1.0f, y_-1.0f, z_-1.0f, 1.0f, x_-1.0f, y_-1.0f, z_+1.0f, 1.0f,  // bottom  
        x_+1.0f, y_-1.0f, z_+1.0f, 1.0f, x_-1.0f, y_-1.0f, z_+1.0f, 1.0f, x_+1.0f, y_-1.0f, z_-1.0f, 1.0f,  
        x_-1.0f, y_-1.0f, z_-1.0f, 1.0f, x_-1.0f, y_-1.0f, z_+1.0f, 1.0f, x_-1.0f, y_+1.0f, z_-1.0f, 1.0f,  // left 
        x_-1.0f, y_+1.0f, z_-1.0f, 1.0f, x_-1.0f, y_-1.0f, z_+1.0f, 1.0f, x_-1.0f, y_+1.0f, z_+1.0f, 1.0f,  
        x_+1.0f, y_-1.0f, z_-1.0f, 1.0f, x_+1.0f, y_+1.0f, z_-1.0f, 1.0f, x_+1.0f, y_-1.0f, z_+1.0f, 1.0f,  // right 
        x_+1.0f, y_-1.0f, z_+1.0f, 1.0f, x_+1.0f, y_+1.0f, z_-1.0f, 1.0f, x_+1.0f, y_+1.0f, z_+1.0f, 1.0f,  
        x_+1.0f, y_+1.0f, z_-1.0f, 1.0f, x_-1.0f, y_+1.0f, z_-1.0f, 1.0f, x_-1.0f, y_+1.0f, z_+1.0f, 1.0f,  // top 
        x_+1.0f, y_+1.0f, z_-1.0f, 1.0f, x_-1.0f, y_+1.0f, z_+1.0f, 1.0f, x_+1.0f, y_+1.0f, z_+1.0f, 1.0f,  
        x_-1.0f, y_-1.0f, z_+1.0f, 1.0f, x_+1.0f, y_-1.0f, z_+1.0f, 1.0f, x_+1.0f, y_+1.0f, z_+1.0f, 1.0f,  // front  
        x_+1.0f, y_+1.0f, z_+1.0f, 1.0f, x_-1.0f, y_+1.0f, z_+1.0f, 1.0f, x_-1.0f, y_-1.0f, z_+1.0f, 1.0f,  
    };
    
    GLfloat cube_colors[12*12];
    int base = 0;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i*4 + 0] = color_back_[0];
        cube_colors[base + i*4 + 1] = color_back_[1];
        cube_colors[base + i*4 + 2] = color_back_[2];
        cube_colors[base + i*4 + 3] = 1.0;
    }
    base = 24;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i*4 + 0] = color_bottom_[0];
        cube_colors[base + i*4 + 1] = color_bottom_[1];
        cube_colors[base + i*4 + 2] = color_bottom_[2];
        cube_colors[base + i*4 + 3] = 1.0;
    }
    base = 48;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i*4 + 0] = color_left_[0];
        cube_colors[base + i*4 + 1] = color_left_[1];
        cube_colors[base + i*4 + 2] = color_left_[2];
        cube_colors[base + i*4 + 3] = 1.0;
    }
    base = 72;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i*4 + 0] = color_right_[0];
        cube_colors[base + i*4 + 1] = color_right_[1];
        cube_colors[base + i*4 + 2] = color_right_[2];
        cube_colors[base + i*4 + 3] = 1.0;
    }
    base = 96;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i*4 + 0] = color_top_[0];
        cube_colors[base + i*4 + 1] = color_top_[1];
        cube_colors[base + i*4 + 2] = color_top_[2];
        cube_colors[base + i*4 + 3] = 1.0;
    }
    base = 120;
    for (int i = 0; i < 6; ++i)
    {
        cube_colors[base + i*4 + 0] = color_front_[0];
        cube_colors[base + i*4 + 1] = color_front_[1];
        cube_colors[base + i*4 + 2] = color_front_[2];
        cube_colors[base + i*4 + 3] = 1.0;
    }
    
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices) + sizeof(cube_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_vertices), cube_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_vertices), sizeof(cube_colors), cube_colors);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(cube_vertices));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void CubeBasic::Draw(mat4 projection_matrix, mat4 model_matrix)
{
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glUniformMatrix4fv(projection_matrix_, 1, GL_FALSE, projection_matrix);
    glUniformMatrix4fv(model_matrix_, 1, GL_FALSE, model_matrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

