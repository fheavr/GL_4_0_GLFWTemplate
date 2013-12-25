/* Copyright (c) Russell Gillette
 * December 2013
 */

#pragma once
#ifndef RENDER_STATE_H
#define RENDER_STATE_H

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

class RenderState
{
public:
    RenderState(unsigned int num_bufs)
    {
        glGenVertexArrays(1, &m_vaoID);
        m_vboIDs = new GLuint[num_bufs];
        glGenBuffers(num_bufs, m_vboIDs);
        m_num_buffers = num_bufs;
    }
    ~RenderState()
    {
        glDeleteVertexArrays(1, &m_vaoID);
        glDeleteBuffers(m_num_buffers, m_vboIDs);
        delete [] m_vboIDs;
    }
    void bindVAO()
    {
        glBindVertexArray(m_vaoID);
    }
    GLuint getBuffer(unsigned int i)
    {
        return m_vboIDs[i];
    }

private:
    GLuint  m_vaoID;
    GLuint  m_num_buffers;
    GLuint *m_vboIDs;
};

#endif // RENDER_STATE_H