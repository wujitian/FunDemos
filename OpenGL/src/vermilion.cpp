#include "vapp.h"

#include <iostream> 
#include <time.h>
#include <sys/time.h>

void VermilionApplication::window_size_callback(GLFWwindow* window, int width, int height)
{
    VermilionApplication* pThis = (VermilionApplication*)glfwGetWindowUserPointer(window);

    pThis->Resize(width, height);
}

void VermilionApplication::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    VermilionApplication* pThis = (VermilionApplication*)glfwGetWindowUserPointer(window);
    std::cout << "[Key Prss] Key:" << key << "(" << char(key) << ")" << " Press:" << action << " Mods:" << mods << std::endl;

    pThis->OnKey(key, scancode, action, mods);
}

void VermilionApplication::char_callback(GLFWwindow* window, unsigned int codepoint)
{
    VermilionApplication* pThis = (VermilionApplication*)glfwGetWindowUserPointer(window);

    pThis->OnChar(codepoint);
}

unsigned int VermilionApplication::app_time()
{
#ifdef _WIN32
    ULONGLONG currentTime = ::GetTickCount64();

    return (unsigned int)(currentTime - m_appStartTime);
#else
    struct timeval  currentTime;
    gettimeofday(&currentTime, nullptr);

    return (unsigned int)(1000000*(currentTime.tv_sec - m_appStartTime.tv_sec) 
            + (currentTime.tv_usec - m_appStartTime.tv_usec));
#endif
}

//void VermilionApplication::Initialize(const char * title)
//{
//#ifdef _WIN32
//    m_appStartTime = ::GetTickCount64();
//#else
//    gettimeofday(&m_appStartTime, nullptr);
//#endif
//
//    glfwInit();
//
//#ifdef _DEBUG
//    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
//#endif
//
//    m_pWindow = glfwCreateWindow(800, 600, title ? title : "OpenGL Application", nullptr, nullptr);
//    glfwSetWindowUserPointer(m_pWindow, this);
//    glfwSetWindowSizeCallback(m_pWindow, window_size_callback);
//    glfwSetKeyCallback(m_pWindow, key_callback);
//    glfwSetCharCallback(m_pWindow, char_callback);
//
//    glfwMakeContextCurrent(m_pWindow);
//
//    gl3wInit();
//
//    Resize(800, 600);
//
//#ifdef _DEBUG
//    if (glDebugMessageCallbackARB != NULL)
//        glDebugMessageCallbackARB(DebugOutputCallback, this);
//#endif
//}
