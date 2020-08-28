/*
 * Progarm Name: cube_basic.hpp
 * Created Time: 2020-08-24 19:11:55
 * Last modified: 
 * @author: fabio@foxmail.com 
 */

#ifndef __CUBE_BASIC_HPP__
#define __CUBE_BASIC_HPP__

#include "vgl.h"
#include "vmath.h"
using namespace vmath;

#define RED vec3(1.0, 0.0, 0.0)
#define GREEN vec3(0.0, 1.0, 0.0)
#define BLUE vec3(0.0, 0.0, 1.0)
#define YELLOW vec3(1.0, 1.0, 0.0)
#define PINK vec3(1.0, 0.0, 1.0)
#define ORANGE vec3(1.0, 0.75, 0.5)
#define WHITE vec3(1.0, 1.0, 1.0)
#define BLACK vec3(0.2, 0.2, 0.2)

class CubeBasic
{
public:
    CubeBasic(float x = 0.0, float y = 0.0, float z = 0.0, 
              vec3 color_front = RED, vec3 color_back = ORANGE, 
              vec3 color_top = YELLOW, vec3 color_bottom = WHITE,
              vec3 color_left = BLUE, vec3 color_right = GREEN);
    virtual ~CubeBasic(void);

    void Init(GLuint program);
    void SetCenterCoords(float x = 0.0, float y = 0.0, float z = 0.0);
    void SetColors(vec3 color_front = RED, vec3 color_back = ORANGE, 
              vec3 color_top = YELLOW, vec3 color_bottom = WHITE,
              vec3 color_left = BLUE, vec3 color_right = GREEN);
    void Draw(mat4 projection_matrix, mat4 model_matrix);

private:
    float x_ = 0.0;
    float y_ = 0.0;
    float z_ = 0.0;
    
    vec3 color_front_;
    vec3 color_back_;
    vec3 color_top_;
    vec3 color_bottom_;
    vec3 color_left_;
    vec3 color_right_;

    GLuint vao_;
    GLuint vbo_;
    GLuint program_;
    GLint model_matrix_;
    GLint projection_matrix_;
};

#endif //__CUBE_BASIC_HPP__

