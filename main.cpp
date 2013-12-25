/* Copyright (c) Russell Gillette
 * December 2013
 */

#define GLFW_INCLUDE_GLU

#ifdef _WIN32
#  include "GL/glew.h"
#  include "GLFW/glfw3.h"
# elif __APPLE__
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#else
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif

#include <stdio.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderUtils.h"
#include "ControlState.h"
#include "WorldState.h"
#include "RenderState.h"

using namespace ControlState;
WorldState *w_state;
RenderState *r_state[2];

void display()
{
    /* program code goes here */
}

int main(int argc, char *argv[])
{
    GLenum err = 0;
    /*********************************************
     * GLFW SETUP
     *********************************************/
    err = glfwInit();
    if (!err)
    {
        fputs("Failed to load the GLFW library", stderr);
        exit(EXIT_FAILURE);
    }

    /*********************************************
     * GLEW SETUP
     *********************************************/
    err = glewInit();
    if (err != GLEW_OK)
    {
        fputs("Failed to initialize the GLEW library", stderr);
        exit(EXIT_FAILURE);
    }

    /*********************************************
     * STATE SETUP
     *********************************************/
    w_state = new WorldState();
    ControlState_init(*w_state);

    /*********************************************
     * SHADER SETUP
     *********************************************/
    // read default shaders from file
    GLuint shaderProgram = 0;
    GLuint shaders[2] = {0};

    buildShader(GL_VERTEX_SHADER, "default.vs.glsl", shaders[0]);
    buildShader(GL_FRAGMENT_SHADER, "default.fs.glsl", shaders[1]);

    // create default shader program
    shaderProgram = buildProgram(2, shaders);

    // bind shader program
    w_state->useProgram(shaderProgram);

    // setup the transform matrices and uniform variables
    w_state->loadTransforms();
    w_state->loadLights();
    w_state->loadMaterials();

    /*********************************************
     * RENDER LOOP
     *********************************************/
    while (!glfwWindowShouldClose(c_state.window))
        display();

    /*********************************************
     * CLEAN UP
     *********************************************/
    ControlState_destroy();
    glfwTerminate();

    exit(EXIT_SUCCESS);
}