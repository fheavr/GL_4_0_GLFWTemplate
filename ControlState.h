/* Copyright (c) Russell Gillette
 * December 2013
 */

#ifndef CONTROL_STATE_H
#define CONTROL_STATE_H

#include "WorldState.h"

/* due to GLFW/glut/most windowing systems being c based it is infeasible to store 
 * all the control state within a class and pass member function pointers (the c 
 * interface does not allow it) the solution, as only one instance is needed and 
 * the callbacks need to to be static, is to encapsulate a number of
 * static functions within a namespace. Yes it is gross. Live with it. :)
 */
#define DEGREES_PER_SECOND 100
#define DEPTH_PER_SECOND 3

class ControlState
{
public:
    float viewTheta;
    float viewPhi;
    float viewDepth;

    // the current state of arrow keys, updated by the
    bool arrL;
    bool arrR;
    bool arrU;
    bool arrD;

    // the current mouse position, updated by the mousePose_callback function
    int mouseX;
    int mouseY;
    bool mouseBtnL;
    bool mouseBtnC;
    bool mouseBtnR;

    // the current dimensions of the window
    int height;
    int width;

    // window that this control state is for
    GLFWwindow* window;
    WorldState* w;

    ControlState()
        : viewTheta(0),
          viewPhi(0),
          viewDepth(1),
          arrL(0), arrR(0),
          arrU(0), arrD(0),
          mouseX(0), mouseY(0),
          mouseBtnL(0), mouseBtnC(0),
          mouseBtnR(0),
          window(NULL), w(NULL)
    {}

    ~ControlState();
    int init(WorldState &w);

    int deltaArrLR();
    int deltaArrUD();
    void updateView(float dTheta, float dPhi, float dDepth);
};
extern ControlState c_state;

/* GLFW callback funtions */
static void error_callback(int error, const char* desc);
static void reshape_callback(GLFWwindow* win, int w, int h);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
static void mouseBtn_callback(GLFWwindow* win, int button, int action, int mod);
static void mousePos_callback(GLFWwindow* win, double x, double y);

#endif // CONTROL_STATE_H