#include <iostream>
#include <random>
using namespace std;

#include "vgl.h"
#include "vapp.h"
#include "vmath.h"

#include "LoadShaders.h"

#include "magic_cube.hpp"


BEGIN_APP_DECLARATION(MagicCubeExample)
    // Override functions from base class
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);
    void OnKey(int key, int scancode, int action, int mods);

    // Member variables
    GLuint cube_prog;
    MagicCube * pMagicCube;

    // Key Press
    bool bKeyOn = false;
    GLuint preKey = GLFW_KEY_UNKNOWN;

    void RandomShuffle(void);

END_APP_DECLARATION()

DEFINE_APP(MagicCubeExample, "Magic Cube Example")

void MagicCubeExample::Initialize(const char * title)
{
    base::Initialize(title);
    
    static ShaderInfo shader_info[] =
    {
        { GL_VERTEX_SHADER, "../shaders/cube.vs.glsl" },
        { GL_FRAGMENT_SHADER, "../shaders/cube.fs.glsl" },
        { GL_NONE, NULL }
    };

    cube_prog = LoadShaders(shader_info);

    glUseProgram(cube_prog);

    pMagicCube = new MagicCube();
    pMagicCube->Init(cube_prog);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void MagicCubeExample::Display(bool auto_redraw)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup
    glEnable(GL_CULL_FACE);
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);
    
    glUseProgram(cube_prog);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode(GL_FRONT, GL_FILL);
    
    pMagicCube->Draw();

    base::Display();
}

void MagicCubeExample::Finalize(void)
{
    glUseProgram(0);
    glDeleteProgram(cube_prog);

    delete pMagicCube;
}

void MagicCubeExample::Resize(int width, int height)
{
    glViewport( 0, 0, width, height);
}

void MagicCubeExample::OnKey(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_F:
                bKeyOn = true;
                preKey = GLFW_KEY_F;
                return;
            case GLFW_KEY_U:
                bKeyOn = true;
                preKey = GLFW_KEY_U;
                return;
            case GLFW_KEY_R:
                bKeyOn = true;
                preKey = GLFW_KEY_R;
                return;
            case GLFW_KEY_B:
                bKeyOn = true;
                preKey = GLFW_KEY_B;
                return;
            case GLFW_KEY_D:
                bKeyOn = true;
                preKey = GLFW_KEY_D;
                return;
            case GLFW_KEY_L:
                bKeyOn = true;
                preKey = GLFW_KEY_L;
                return;
            case GLFW_KEY_X:
                bKeyOn = true;
                preKey = GLFW_KEY_X;
                return;
            case GLFW_KEY_Y:
                bKeyOn = true;
                preKey = GLFW_KEY_Y;
                return;
            case GLFW_KEY_Z:
                bKeyOn = true;
                preKey = GLFW_KEY_Z;
                return;
            case GLFW_KEY_1:
                if (true == bKeyOn)
                {
                    if (preKey == GLFW_KEY_F)
                        pMagicCube->Move_F1();
                    else if (preKey == GLFW_KEY_U)
                        pMagicCube->Move_U1();
                    else if (preKey == GLFW_KEY_R)
                        pMagicCube->Move_R1();
                    else if (preKey == GLFW_KEY_B)
                        pMagicCube->Move_B1();
                    else if (preKey == GLFW_KEY_D)
                        pMagicCube->Move_D1();
                    else if (preKey == GLFW_KEY_L)
                        pMagicCube->Move_L1();
                    else if (preKey == GLFW_KEY_X)
                        pMagicCube->Move_X1();
                    else if (preKey == GLFW_KEY_Y)
                        pMagicCube->Move_Y1();
                    else if (preKey == GLFW_KEY_Z)
                        pMagicCube->Move_Z1();
                    bKeyOn = false;
                    preKey = GLFW_KEY_UNKNOWN;
                }
                return;
            case GLFW_KEY_2:
                if (true == bKeyOn)
                {
                    if (preKey == GLFW_KEY_F)
                        pMagicCube->Move_F2();
                    else if (preKey == GLFW_KEY_U)
                        pMagicCube->Move_U2();
                    else if (preKey == GLFW_KEY_R)
                        pMagicCube->Move_R2();
                    else if (preKey == GLFW_KEY_B)
                        pMagicCube->Move_B2();
                    else if (preKey == GLFW_KEY_D)
                        pMagicCube->Move_D2();
                    else if (preKey == GLFW_KEY_L)
                        pMagicCube->Move_L2();
                    else if (preKey == GLFW_KEY_X)
                        pMagicCube->Move_X2();
                    else if (preKey == GLFW_KEY_Y)
                        pMagicCube->Move_Y2();
                    else if (preKey == GLFW_KEY_Z)
                        pMagicCube->Move_Z2();
                    bKeyOn = false;
                    preKey = GLFW_KEY_UNKNOWN;
                }
                return;
            case GLFW_KEY_3:
                if (true == bKeyOn)
                {
                    if (preKey == GLFW_KEY_F)
                        pMagicCube->Move_F3();
                    else if (preKey == GLFW_KEY_U)
                        pMagicCube->Move_U3();
                    else if (preKey == GLFW_KEY_R)
                        pMagicCube->Move_R3();
                    else if (preKey == GLFW_KEY_B)
                        pMagicCube->Move_B3();
                    else if (preKey == GLFW_KEY_D)
                        pMagicCube->Move_D3();
                    else if (preKey == GLFW_KEY_L)
                        pMagicCube->Move_L3();
                    else if (preKey == GLFW_KEY_X)
                        pMagicCube->Move_X3();
                    else if (preKey == GLFW_KEY_Y)
                        pMagicCube->Move_Y3();
                    else if (preKey == GLFW_KEY_Z)
                        pMagicCube->Move_Z3();
                    bKeyOn = false;
                    preKey = GLFW_KEY_UNKNOWN;
                }
                return;
            case GLFW_KEY_0:
                RandomShuffle();
                return;
            default:
                return;
        }
    }

    base::OnKey(key, scancode, action, mods);
}

void MagicCubeExample::RandomShuffle(void)
{
    default_random_engine e0, e1;
    e0.seed(10);
    e1.seed(10);
    uniform_int_distribution<unsigned> u0(0, 8);
    uniform_int_distribution<unsigned> u1(0, 2);

    for (int i = 0; i < 20; ++i)
    {
        int t0 = u0(e0);
        int t1 = u1(e1);
        cout << "step" << i << ": " << t0 << " " << t1 << endl;
        switch (t0)
        {
            case 0:
                if (t1 == 0)
                    pMagicCube->Move_F1();
                else if (t1 == 1) 
                    pMagicCube->Move_F2();
                else if (t1 == 2)
                    pMagicCube->Move_F3();
                break;
            case 1:
                if (t1 == 0)
                    pMagicCube->Move_U1();
                else if (t1 == 1) 
                    pMagicCube->Move_U2();
                else if (t1 == 2)
                    pMagicCube->Move_U3();
                break;
            case 2:
                if (t1 == 0)
                    pMagicCube->Move_R1();
                else if (t1 == 1) 
                    pMagicCube->Move_R2();
                else if (t1 == 2)
                    pMagicCube->Move_R3();
                break;
            case 3:
                if (t1 == 0)
                    pMagicCube->Move_B1();
                else if (t1 == 1) 
                    pMagicCube->Move_B2();
                else if (t1 == 2)
                    pMagicCube->Move_B3();
                break;
            case 4:
                if (t1 == 0)
                    pMagicCube->Move_D1();
                else if (t1 == 1) 
                    pMagicCube->Move_D2();
                else if (t1 == 2)
                    pMagicCube->Move_D3();
                break;
            case 5:
                if (t1 == 0)
                    pMagicCube->Move_L1();
                else if (t1 == 1) 
                    pMagicCube->Move_L2();
                else if (t1 == 2)
                    pMagicCube->Move_L3();
                break;
            case 6:
                if (t1 == 0)
                    pMagicCube->Move_X1();
                else if (t1 == 1) 
                    pMagicCube->Move_X2();
                else if (t1 == 2)
                    pMagicCube->Move_X3();
                break;
            case 7:
                if (t1 == 0)
                    pMagicCube->Move_Y1();
                else if (t1 == 1) 
                    pMagicCube->Move_Y2();
                else if (t1 == 2)
                    pMagicCube->Move_Y3();
                break;
            case 8:
                if (t1 == 0)
                    pMagicCube->Move_Z1();
                else if (t1 == 1) 
                    pMagicCube->Move_Z2();
                else if (t1 == 2)
                    pMagicCube->Move_Z3();
                break;
            default:
                break;
        }
        
        while (!pMagicCube->CanMove())
        {
            pMagicCube->Draw();
        }
    }
}

