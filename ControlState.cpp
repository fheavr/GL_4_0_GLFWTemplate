/* Copyright (c) Russell Gillette
 * December 2013
 */

#include "ControlState.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

namespace ControlState
{

int ControlState_init(WorldState &w)
{
    c_state.w = &w;

    /* As of right now we only have one window */
    c_state.window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    if (!c_state.window)
    {
        glfwTerminate();
        fputs("failed to initialize window", stderr);
        return 1; // error
    }
    glfwMakeContextCurrent(c_state.window);

    // bind all callbacks
    glfwSetKeyCallback(c_state.window, key_callback);
    glfwSetFramebufferSizeCallback(c_state.window, reshape_callback);
    glfwSetCursorPosCallback(c_state.window, mousePos_callback);
    glfwSetMouseButtonCallback(c_state.window, mouseBtn_callback);

    return 0;
}

int ControlState_destroy()
{
    glfwDestroyWindow(c_state.window);

    return 0;
}

/*****************************************************************************
 * Passive Callback functions
 *****************************************************************************/
// error callback for GLFW
static void error_callback(int error, const char* desc)
{
    fputs(desc, stderr);
}

// callback when window is resized
void reshape_callback( GLFWwindow* window, int w, int h )
{
    c_state.height = h;
    c_state.width  = w;

    glViewport( 0, 0, (GLint)w, (GLint)h );
}

/*****************************************************************************
 * Active Callback functions
 *****************************************************************************/
// callback when a key is pressed
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    /* key code goes here */

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

// callback when a mouse button is pressed
static void mouseBtn_callback(GLFWwindow* win, int button, int action, int mod)
{
    /* TODO: any controls relative to pressing the mouse buttons goes here */

    if (button == GLFW_MOUSE_BUTTON_LEFT)
        c_state.mouseBtnL = (action == GLFW_PRESS) ? 1 : 0;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        c_state.mouseBtnR = (action == GLFW_PRESS) ? 1 : 0;
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        c_state.mouseBtnC = (action == GLFW_PRESS) ? 1 : 0;
}

// callback when the mouse is moved. This will be called
// ALOT keep it as light as possible!!
static void mousePos_callback(GLFWwindow* win, double x, double y)
{
    // screen Y coords are inverted.
    y = c_state.height - y;

    // currently used to update camera angles if mouse pressed
    if (c_state.mouseBtnL)
    {
        // Calculate change from last known mouse positon.
        int dx = x - c_state.mouseX;
        int dy = y - c_state.mouseY;
    
        // Update viewing angles.
        c_state.viewTheta = int(c_state.viewTheta + 360 + float(dx) / 2) % 360;
        c_state.viewPhi   = std::min(90.0f, std::max(-90.0f, c_state.viewPhi - dy));
    }

    c_state.mouseX = x;
    c_state.mouseY = y;
}


} // namespace ControlState