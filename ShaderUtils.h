/* Copyright (c) Russell Gillette
 * December 2013
 */

#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

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

void buildShader(GLenum target, char *file, GLuint &shader);
GLuint buildProgram(int num_stages, GLuint *shaders);

#endif