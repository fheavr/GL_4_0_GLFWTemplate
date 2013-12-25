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

WorldState *w_state;
RenderState *r_state[2];

void display()
{
    /* limit framerate to 60 fps */
    double curr = 0;
    if (curr = glfwGetTime() < 1/60)
        return;

    // Clear the buffer we will draw into.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup camera projection.
    w_state->projection = glm::perspective(50.0f, float(c_state.width) / float(c_state.height), 0.1f, 40.0f);

    // Setup camera position/orientation.
    w_state->modelview = glm::lookAt(
        c_state.viewDepth * glm::vec3(0.0f, 2.5f, 10.0f), // eye
                            glm::vec3(0.0f, 0.0f,  0.0f), // centre
                            glm::vec3(0.0f, 1.0f,  0.0f)  // up
    );

    c_state.updateView(
        c_state.deltaArrLR() * DEGREES_PER_SECOND * curr,
        0,
        c_state.deltaArrUD() * DEPTH_PER_SECOND * curr );

    w_state->modelview = glm::rotate(w_state->modelview, c_state.viewPhi, glm::vec3(1, 0, 0));
    w_state->modelview = glm::rotate(w_state->modelview, c_state.viewTheta, glm::vec3(0, 1, 0));

    /* Draw Code goes here */

    glfwSwapBuffers(c_state.window);
    glfwPollEvents();
    glfwSetTime(0.0);
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
     * STATE SETUP
     *********************************************/
    // must be setup before glew so that a valid openGL
    // context exists (created with the window)

    w_state = new WorldState();
    c_state.init(*w_state);

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
    w_state->setProgram(0, shaderProgram);
    w_state->useProgram(0);

    // setup the transform matrices and uniform variables
    w_state->loadTransforms();
    w_state->loadLights();
    w_state->loadMaterials();

    /*********************************************
     * RENDER LOOP
     *********************************************/
    glfwSetTime(0.0);
    while (!glfwWindowShouldClose(c_state.window))
        display();

    /*********************************************
     * CLEAN UP
     *********************************************/
    glfwTerminate();

    exit(EXIT_SUCCESS);
}