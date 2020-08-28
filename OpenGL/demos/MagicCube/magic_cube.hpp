/*
 * Progarm Name: magic_cube.hpp
 * Created Time: 2020-08-24 19:11:55
 * Last modified: 
 * @author: fabio@foxmail.com 
 */

#ifndef __MAGIC_CUBE_HPP__
#define __MAGIC_CUBE_HPP__

#include "cube_basic.hpp"

#define LEN 2.05f
#define THRESHOLD 0.01f
#define STRIDE 0.2f

class CubeUnit
{
public:
    CubeUnit(void){};
    virtual ~CubeUnit(void){};

    void SetCenterCoords(float x, float y, float z);
    void SetColors(vmath::vec3 front, vmath::vec3 back, vmath::vec3 top, vmath::vec3 bottom,
                   vmath::vec3 left, vmath::vec3 right);
    void Init(GLuint pro);
    void MatrixInit(void);
    void SetMove(float angle_x, float angle_y, float angle_z);
    bool IsRunning(void);
    void Draw(void);

private:
    CubeBasic cube;
    GLuint program;
    vmath::vec3 position;
    vmath::vec3 color_front;
    vmath::vec3 color_back;
    vmath::vec3 color_top;
    vmath::vec3 color_bottom;
    vmath::vec3 color_left;
    vmath::vec3 color_right;
    vmath::mat4 projection_matrix;
    vmath::mat4 base_model_matrix;
    vmath::mat4 angle_model_matrix;
    float var_angle_x = 0.0f;
    float var_angle_y = 0.0f;
    float var_angle_z = 0.0f;
    bool bRunning = false;
};

class MagicCube
{
public:
    MagicCube(void){};
    virtual ~MagicCube(void)
    {
        delete []pCubes_;
    };
    
    void Init(GLuint program);
    void Draw(void);
    bool CanMove(void);

    //Move Funciton
    void Move_F1(void);
    void Move_F2(void);
    void Move_F3(void);
    void Move_U1(void);
    void Move_U2(void);
    void Move_U3(void);
    void Move_R1(void);
    void Move_R2(void);
    void Move_R3(void);
    void Move_B1(void);
    void Move_B2(void);
    void Move_B3(void);
    void Move_D1(void);
    void Move_D2(void);
    void Move_D3(void);
    void Move_L1(void);
    void Move_L2(void);
    void Move_L3(void);
    void Move_X1(void);
    void Move_X2(void);
    void Move_X3(void);
    void Move_Y1(void);
    void Move_Y2(void);
    void Move_Y3(void);
    void Move_Z1(void);
    void Move_Z2(void);
    void Move_Z3(void);

private:
    int cubeIds_[27];
    CubeUnit *pCubes_;

    void SwithID_ClockWise(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2);
    void SwithID_Reverse(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2);
    void SwithID_AntiClockWise(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2);
};


#endif //__MAGIC_CUBE_HPP__

