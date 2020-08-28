/*
 * Progarm Name: magic_cube.cpp
 * Created Time: 2020-08-27 13:34:07
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include "magic_cube.hpp"
#include <iostream>

using std::cout;
using std::endl;


void CubeUnit::SetCenterCoords(float x, float y, float z)
{
    position = vmath::vec3(x, y, z);
    cube.SetCenterCoords(x, y, z); 
}
    
void CubeUnit::SetColors(vmath::vec3 front, vmath::vec3 back, vmath::vec3 top, vmath::vec3 bottom,
               vmath::vec3 left, vmath::vec3 right)
{
    color_front = front;
    color_back = back;
    color_top = top;
    color_bottom = bottom;
    color_left = left;
    color_right = right;
    cube.SetColors(color_front, color_back, color_top, color_bottom, color_left, color_right);
}

void CubeUnit::Init(GLuint pro)
{
    program = pro;
    cube.Init(program);
}

void CubeUnit::MatrixInit(void)
{
    // Set up the model and projection matrix
    //vmath::mat4 view_projection_matrix = vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 500.0f);
    vmath::mat4 view_projection_matrix = vmath::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -30.0f, 30.0f);
    vmath::mat4 eye_matrix = vmath::lookat(vec3(8.0f, 8.0f, 0.0f), vec3(0.0f, 0.0f, -10.0f), vec3(0.0, 1.0, 0.0));
    projection_matrix = view_projection_matrix * eye_matrix;
    base_model_matrix = vmath::translate(0.0f, 0.0f, -10.0f);
    angle_model_matrix = vmath::rotate(0.0f, vec3(0.0f, 0.0f, 1.0f));
}

void CubeUnit::SetMove(float angle_x, float angle_y, float angle_z)
{
    if (true == bRunning)
    {
        cout << "Please wait action finish!" << endl;
        return;
    }

    var_angle_x = angle_x;
    var_angle_y = angle_y;
    var_angle_z = angle_z;

    bRunning = true;
}

bool CubeUnit::IsRunning(void)
{
    return bRunning;
}

void CubeUnit::Draw(void)
{ 
    bool bIn = false;
    if (var_angle_x > THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(STRIDE, vec3(1.0f, 0.0f, 0.0f)) * angle_model_matrix;
        var_angle_x -= STRIDE;
        bIn = true;
    } 
    else if (var_angle_x < -THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(-STRIDE, vec3(1.0f, 0.0f, 0.0f)) * angle_model_matrix;
        var_angle_x += STRIDE;
        bIn = true;
    }
    
    if (var_angle_y > THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(STRIDE, vec3(0.0f, 1.0f, 0.0f)) * angle_model_matrix;
        var_angle_y -= STRIDE;
        bIn = true;
    } 
    else if (var_angle_y < -THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(-STRIDE, vec3(0.0f, 1.0f, 0.0f)) * angle_model_matrix;
        var_angle_y += STRIDE;
        bIn = true;
    }
    
    if (var_angle_z > THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(STRIDE, vec3(0.0f, 0.0f, 1.0f)) * angle_model_matrix;
        var_angle_z -= STRIDE;
        bIn = true;
    } 
    else if (var_angle_z < -THRESHOLD)
    {
        angle_model_matrix = vmath::rotate(-STRIDE, vec3(0.0f, 0.0f, 1.0f)) * angle_model_matrix;
        var_angle_z += STRIDE;
        bIn = true;
    }

    if (false == bIn)
    {
        bRunning = false;
    }

    cube.Draw(projection_matrix, base_model_matrix*angle_model_matrix);
}
    
void MagicCube::Init(GLuint program)
{
    // new magic cube and init
    pCubes_ = new CubeUnit[27];
    pCubes_[0].SetCenterCoords(-LEN, LEN, LEN);
    pCubes_[0].SetColors(RED, BLACK, YELLOW, BLACK, BLUE, BLACK);
    pCubes_[0].Init(program);
    pCubes_[1].SetCenterCoords(0.0f, LEN, LEN);
    pCubes_[1].SetColors(RED, BLACK, YELLOW, BLACK, BLACK, BLACK);
    pCubes_[1].Init(program);
    pCubes_[2].SetCenterCoords(LEN, LEN, LEN);
    pCubes_[2].SetColors(RED, BLACK, YELLOW, BLACK, BLACK, GREEN);
    pCubes_[2].Init(program);
    pCubes_[3].SetCenterCoords(-LEN, 0.0f, LEN);
    pCubes_[3].SetColors(RED, BLACK, BLACK, BLACK, BLUE, BLACK);
    pCubes_[3].Init(program);
    pCubes_[4].SetCenterCoords(0.0f, 0.0f, LEN);
    pCubes_[4].SetColors(RED, BLACK, BLACK, BLACK, BLACK, BLACK);
    pCubes_[4].Init(program);
    pCubes_[5].SetCenterCoords(LEN, 0.0f, LEN);
    pCubes_[5].SetColors(RED, BLACK, BLACK, BLACK, BLACK, GREEN);
    pCubes_[5].Init(program);
    pCubes_[6].SetCenterCoords(-LEN, -LEN, LEN);
    pCubes_[6].SetColors(RED, BLACK, BLACK, WHITE, BLUE, BLACK);
    pCubes_[6].Init(program);
    pCubes_[7].SetCenterCoords(0.0f, -LEN, LEN);
    pCubes_[7].SetColors(RED, BLACK, BLACK, WHITE, BLACK, BLACK);
    pCubes_[7].Init(program);
    pCubes_[8].SetCenterCoords(LEN, -LEN, LEN);
    pCubes_[8].SetColors(RED, BLACK, BLACK, WHITE, BLACK, GREEN);
    pCubes_[8].Init(program);
    pCubes_[9].SetCenterCoords(-LEN, LEN, 0.0f);
    pCubes_[9].SetColors(BLACK, BLACK, YELLOW, BLACK, BLUE, BLACK);
    pCubes_[9].Init(program);
    pCubes_[10].SetCenterCoords(0.0f, LEN, 0.0f);
    pCubes_[10].SetColors(BLACK, BLACK, YELLOW, BLACK, BLACK, BLACK);
    pCubes_[10].Init(program);
    pCubes_[11].SetCenterCoords(LEN, LEN, 0.0f);
    pCubes_[11].SetColors(BLACK, BLACK, YELLOW, BLACK, BLACK, GREEN);
    pCubes_[11].Init(program);
    pCubes_[12].SetCenterCoords(-LEN, 0.0f, 0.0f);
    pCubes_[12].SetColors(BLACK, BLACK, BLACK, BLACK, BLUE, BLACK);
    pCubes_[12].Init(program);
    pCubes_[13].SetCenterCoords(0.0f, 0.0f, 0.0f);
    pCubes_[13].SetColors(BLACK, BLACK, BLACK, BLACK, BLACK, BLACK);
    pCubes_[13].Init(program);
    pCubes_[14].SetCenterCoords(LEN, 0.0f, 0.0f);
    pCubes_[14].SetColors(BLACK, BLACK, BLACK, BLACK, BLACK, GREEN);
    pCubes_[14].Init(program);
    pCubes_[15].SetCenterCoords(-LEN, -LEN, 0.0f);
    pCubes_[15].SetColors(BLACK, BLACK, BLACK, WHITE, BLUE, BLACK);
    pCubes_[15].Init(program);
    pCubes_[16].SetCenterCoords(0.0f, -LEN, 0.0f);
    pCubes_[16].SetColors(BLACK, BLACK, BLACK, WHITE, BLACK, BLACK);
    pCubes_[16].Init(program);
    pCubes_[17].SetCenterCoords(LEN, -LEN, 0.0f);
    pCubes_[17].SetColors(BLACK, BLACK, BLACK, WHITE, BLACK, GREEN);
    pCubes_[17].Init(program);
    pCubes_[18].SetCenterCoords(-LEN, LEN, -LEN);
    pCubes_[18].SetColors(BLACK, ORANGE, YELLOW, BLACK, BLUE, BLACK);
    pCubes_[18].Init(program);
    pCubes_[19].SetCenterCoords(0.0f, LEN, -LEN);
    pCubes_[19].SetColors(BLACK, ORANGE, YELLOW, BLACK, BLACK, BLACK);
    pCubes_[19].Init(program);
    pCubes_[20].SetCenterCoords(LEN, LEN, -LEN);
    pCubes_[20].SetColors(BLACK, ORANGE, YELLOW, BLACK, BLACK, GREEN);
    pCubes_[20].Init(program);
    pCubes_[21].SetCenterCoords(-LEN, 0.0f, -LEN);
    pCubes_[21].SetColors(BLACK, ORANGE, BLACK, BLACK, BLUE, BLACK);
    pCubes_[21].Init(program);
    pCubes_[22].SetCenterCoords(0.0f, 0.0f, -LEN);
    pCubes_[22].SetColors(BLACK, ORANGE, BLACK, BLACK, BLACK, BLACK);
    pCubes_[22].Init(program);
    pCubes_[23].SetCenterCoords(LEN, 0.0f, -LEN);
    pCubes_[23].SetColors(BLACK, ORANGE, BLACK, BLACK, BLACK, GREEN);
    pCubes_[23].Init(program);
    pCubes_[24].SetCenterCoords(-LEN, -LEN, -LEN);
    pCubes_[24].SetColors(BLACK, ORANGE, BLACK, WHITE, BLUE, BLACK);
    pCubes_[24].Init(program);
    pCubes_[25].SetCenterCoords(0.0f, -LEN, -LEN);
    pCubes_[25].SetColors(BLACK, ORANGE, BLACK, WHITE, BLACK, BLACK);
    pCubes_[25].Init(program);
    pCubes_[26].SetCenterCoords(LEN, -LEN, -LEN);
    pCubes_[26].SetColors(BLACK, ORANGE, BLACK, WHITE, BLACK, GREEN);
    pCubes_[26].Init(program);

    for (int i = 0; i < 27; ++i)
    {
        cubeIds_[i] = i;
        pCubes_[i].MatrixInit();
    }
}

void MagicCube::Draw(void)
{
    for (int i = 0; i < 27; ++i)
    {
        pCubes_[i].Draw();
    }

    //cout << "[0] ==> " << cubeIds_[0] << "," << cubeIds_[1] << "," << cubeIds_[2] << endl;
    //cout << "[1] ==> " << cubeIds_[3] << "," << cubeIds_[4] << "," << cubeIds_[5] << endl;
    //cout << "[2] ==> " << cubeIds_[6] << "," << cubeIds_[7] << "," << cubeIds_[8] << endl;
    //cout << "[3] ==> " << cubeIds_[9] << "," << cubeIds_[10] << "," << cubeIds_[11] << endl;
    //cout << "[4] ==> " << cubeIds_[12] << "," << cubeIds_[13] << "," << cubeIds_[14] << endl;
    //cout << "[5] ==> " << cubeIds_[15] << "," << cubeIds_[16] << "," << cubeIds_[17] << endl;
    //cout << "[6] ==> " << cubeIds_[18] << "," << cubeIds_[19] << "," << cubeIds_[20] << endl;
    //cout << "[7] ==> " << cubeIds_[21] << "," << cubeIds_[22] << "," << cubeIds_[23] << endl;
    //cout << "[8] ==> " << cubeIds_[24] << "," << cubeIds_[25] << "," << cubeIds_[26] << endl;
}

bool MagicCube::CanMove(void)
{
    for (int i = 0; i < 27; ++i)
        if (true == pCubes_[i].IsRunning())
            return false;
    return true;
}
    
void MagicCube::SwithID_ClockWise(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2)
{
    int temp = cubeIds_[x0];
    cubeIds_[x0] = cubeIds_[z0];
    cubeIds_[z0] = cubeIds_[z2];
    cubeIds_[z2] = cubeIds_[x2];
    cubeIds_[x2] = temp;
    temp = cubeIds_[x1];
    cubeIds_[x1] = cubeIds_[y0];
    cubeIds_[y0] = cubeIds_[z1];
    cubeIds_[z1] = cubeIds_[y2];
    cubeIds_[y2] = temp;
}
    
void MagicCube::SwithID_Reverse(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2)
{
    int temp = cubeIds_[x0];
    cubeIds_[x0] = cubeIds_[z2];
    cubeIds_[z2] = temp; 
    temp = cubeIds_[x1];
    cubeIds_[x1] = cubeIds_[z1];
    cubeIds_[z1] = temp; 
    temp = cubeIds_[x2];
    cubeIds_[x2] = cubeIds_[z0];
    cubeIds_[z0] = temp; 
    temp = cubeIds_[y0];
    cubeIds_[y0] = cubeIds_[y2];
    cubeIds_[y2] = temp; 
}

void MagicCube::SwithID_AntiClockWise(int x0, int x1, int x2, int y0, int y1, int y2, int z0, int z1, int z2)
{
    int temp = cubeIds_[x0];
    cubeIds_[x0] = cubeIds_[x2];
    cubeIds_[x2] = cubeIds_[z2];
    cubeIds_[z2] = cubeIds_[z0];
    cubeIds_[z0] = temp;
    temp = cubeIds_[x1];
    cubeIds_[x1] = cubeIds_[y2];
    cubeIds_[y2] = cubeIds_[z1];
    cubeIds_[z1] = cubeIds_[y0];
    cubeIds_[y0] = temp;
}

// Move Functions
void MagicCube::Move_F1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(0, 1, 2, 3, 4, 5, 6, 7, 8);
    for (int i = 0; i < 9; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -90.0f);
}

void MagicCube::Move_F2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(0, 1, 2, 3, 4, 5, 6, 7, 8);
    for (int i = 0; i < 9; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -180.0f);
}

void MagicCube::Move_F3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(0, 1, 2, 3, 4, 5, 6, 7, 8);
    for (int i = 0; i < 9; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, 90.0f);
}

void MagicCube::Move_U1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(18, 19, 20, 9, 10, 11, 0, 1, 2);
    for (int i = 0; i < 27; i = i+9)
    {
        pCubes_[cubeIds_[i+0]].SetMove(0.0f, -90.0f, 0.0f);
        pCubes_[cubeIds_[i+1]].SetMove(0.0f, -90.0f, 0.0f);
        pCubes_[cubeIds_[i+2]].SetMove(0.0f, -90.0f, 0.0f);
    }
}

void MagicCube::Move_U2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(18, 19, 20, 9, 10, 11, 0, 1, 2);
    for (int i = 0; i < 27; i = i+9)
    {
        pCubes_[cubeIds_[i+0]].SetMove(0.0f, -180.0f, 0.0f);
        pCubes_[cubeIds_[i+1]].SetMove(0.0f, -180.0f, 0.0f);
        pCubes_[cubeIds_[i+2]].SetMove(0.0f, -180.0f, 0.0f);
    }
}

void MagicCube::Move_U3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(18, 19, 20, 9, 10, 11, 0, 1, 2);
    for (int i = 0; i < 27; i = i+9)
    {
        pCubes_[cubeIds_[i+0]].SetMove(0.0f, 90.0f, 0.0f);
        pCubes_[cubeIds_[i+1]].SetMove(0.0f, 90.0f, 0.0f);
        pCubes_[cubeIds_[i+2]].SetMove(0.0f, 90.0f, 0.0f);
    }
}

void MagicCube::Move_R1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 2; i < 27; i = i+3)
        pCubes_[cubeIds_[i]].SetMove(-90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_R2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 2; i < 27; i = i+3)
        pCubes_[cubeIds_[i]].SetMove(-180.0f, 0.0f, 0.0f);
}

void MagicCube::Move_R3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 2; i < 27; i = i+3)
        pCubes_[cubeIds_[i]].SetMove(90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_B1(void)
{
    cout << "Move_B1 get in." << endl;
    if (!CanMove()) return;
    SwithID_ClockWise(20, 19, 18, 23, 22, 21, 26, 25, 24);
    for (int i = 18; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, 90.0f);
}

void MagicCube::Move_B2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(20, 19, 18, 23, 22, 21, 26, 25, 24);
    for (int i = 18; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, 180.0f);
}

void MagicCube::Move_B3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(20, 19, 18, 23, 22, 21, 26, 25, 24);
    for (int i = 18; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -90.0f);
}

void MagicCube::Move_D1(void)
{
    cout << "Move_D1 get in." << endl;
    if (!CanMove()) return;
    SwithID_ClockWise(6, 7, 8, 15, 16, 17, 24, 25, 26);
    for (int i = 0; i < 27; i = i+9)
    {
        pCubes_[cubeIds_[i+6]].SetMove(0.0f, 90.0f, 0.0f);
        pCubes_[cubeIds_[i+7]].SetMove(0.0f, 90.0f, 0.0f);
        pCubes_[cubeIds_[i+8]].SetMove(0.0f, 90.0f, 0.0f);
    }
}

void MagicCube::Move_D2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(6, 7, 8, 15, 16, 17, 24, 25, 26);
    for (int i = 0; i < 27; i = i+9)
    {
        pCubes_[cubeIds_[i+6]].SetMove(0.0f, 180.0f, 0.0f);
        pCubes_[cubeIds_[i+7]].SetMove(0.0f, 180.0f, 0.0f);
        pCubes_[cubeIds_[i+8]].SetMove(0.0f, 180.0f, 0.0f);
    }
}

void MagicCube::Move_D3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(6, 7, 8, 15, 16, 17, 24, 25, 26);
    for (int i = 0; i < 27; i = i+9)
    {
        pCubes_[cubeIds_[i+6]].SetMove(0.0f, -90.0f, 0.0f);
        pCubes_[cubeIds_[i+7]].SetMove(0.0f, -90.0f, 0.0f);
        pCubes_[cubeIds_[i+8]].SetMove(0.0f, -90.0f, 0.0f);
    }
}

void MagicCube::Move_L1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(18, 9, 0, 21, 12, 3, 24, 15, 6);
    for (int i = 0; i < 27; i = i+3)
        pCubes_[cubeIds_[i]].SetMove(90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_L2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(18, 9, 0, 21, 12, 3, 24, 15, 6);
    for (int i = 0; i < 27; i = i+3)
        pCubes_[cubeIds_[i]].SetMove(180.0f, 0.0f, 0.0f);
}

void MagicCube::Move_L3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(18, 9, 0, 21, 12, 3, 24, 15, 6);
    for (int i = 0; i < 27; i = i+3)
        pCubes_[cubeIds_[i]].SetMove(-90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_X1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(0, 9, 18, 3, 12, 21, 6, 15, 24);
    SwithID_ClockWise(1, 10, 19, 4, 13, 22, 7, 16, 25);
    SwithID_ClockWise(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 0; i < 27; i++)
        pCubes_[cubeIds_[i]].SetMove(-90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_X2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(0, 9, 18, 3, 12, 21, 6, 15, 24);
    SwithID_Reverse(1, 10, 19, 4, 13, 22, 7, 16, 25);
    SwithID_Reverse(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 0; i < 27; i++)
        pCubes_[cubeIds_[i]].SetMove(-180.0f, 0.0f, 0.0f);
}

void MagicCube::Move_X3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(0, 9, 18, 3, 12, 21, 6, 15, 24);
    SwithID_AntiClockWise(1, 10, 19, 4, 13, 22, 7, 16, 25);
    SwithID_AntiClockWise(2, 11, 20, 5, 14, 23, 8, 17, 26);
    for (int i = 0; i < 27; i++)
        pCubes_[cubeIds_[i]].SetMove(90.0f, 0.0f, 0.0f);
}

void MagicCube::Move_Y1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(18, 19, 20, 9, 10, 11, 0, 1, 2);
    SwithID_ClockWise(21, 22, 23, 12, 13, 14, 3, 4, 5);
    SwithID_ClockWise(24, 25, 26, 15, 16, 17, 6, 7, 8);
    for (int i = 0; i < 27; i++)
    {
        pCubes_[cubeIds_[i]].SetMove(0.0f, -90.0f, 0.0f);
    }
}

void MagicCube::Move_Y2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(18, 19, 20, 9, 10, 11, 0, 1, 2);
    SwithID_Reverse(21, 22, 23, 12, 13, 14, 3, 4, 5);
    SwithID_Reverse(24, 25, 26, 15, 16, 17, 6, 7, 8);
    for (int i = 0; i < 27; i++)
    {
        pCubes_[cubeIds_[i]].SetMove(0.0f, -180.0f, 0.0f);
    }
}

void MagicCube::Move_Y3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(18, 19, 20, 9, 10, 11, 0, 1, 2);
    SwithID_AntiClockWise(21, 22, 23, 12, 13, 14, 3, 4, 5);
    SwithID_AntiClockWise(24, 25, 26, 15, 16, 17, 6, 7, 8);
    for (int i = 0; i < 27; i++)
    {
        pCubes_[cubeIds_[i]].SetMove(0.0f, 90.0f, 0.0f);
    }
}

void MagicCube::Move_Z1(void)
{
    if (!CanMove()) return;
    SwithID_ClockWise(0, 1, 2, 3, 4, 5, 6, 7, 8);
    SwithID_ClockWise(9, 10, 11, 12, 13, 14, 15, 16, 17);
    SwithID_ClockWise(18, 19, 20, 21, 22, 23, 24, 25, 26);
    for (int i = 0; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -90.0f);
}

void MagicCube::Move_Z2(void)
{
    if (!CanMove()) return;
    SwithID_Reverse(0, 1, 2, 3, 4, 5, 6, 7, 8);
    SwithID_Reverse(9, 10, 11, 12, 13, 14, 15, 16, 17);
    SwithID_Reverse(18, 19, 20, 21, 22, 23, 24, 25, 26);
    for (int i = 0; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, -180.0f);
}

void MagicCube::Move_Z3(void)
{
    if (!CanMove()) return;
    SwithID_AntiClockWise(0, 1, 2, 3, 4, 5, 6, 7, 8);
    SwithID_AntiClockWise(9, 10, 11, 12, 13, 14, 15, 16, 17);
    SwithID_AntiClockWise(18, 19, 20, 21, 22, 23, 24, 25, 26);
    for (int i = 0; i < 27; ++i)
        pCubes_[cubeIds_[i]].SetMove(0.0f, 0.0f, 90.0f);
}

