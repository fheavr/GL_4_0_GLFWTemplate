/* Copyright (c) Russell Gillette
 * December 2013
 */

#include "WorldState.h"

WorldState::WorldState()
{
    // make sure that the world can hold at least 5 of each object
    // before it needs to reallocate memory
    shaders.reserve(5);
    lights.reserve(5);
    materials.reserve(5);
}

WorldState::~WorldState()
{}

void WorldState::useProgram(unsigned int i)
{
    glUseProgram(shaders[i]);
    currentProgram = i;
}

void WorldState::setProgram(unsigned int i, GLuint program)
{
    while (shaders.size() <= i)
        shaders.push_back((GLuint)0);

    shaders[i] = program;
}

void WorldState::loadTransforms()
{
    // setup uniform variables
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"ModelViewMatrix"),1, GL_FALSE, glm::value_ptr(modelview));
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"MVP"), 1, GL_FALSE, glm::value_ptr(projection * modelview));

    /* the Normal Matrix is the inverse transpose of the upper left 3x3 modelview matrix
     * this is used to transform normals, as they do not transform the same way as
     * vertices. */
    glUniformMatrix3fv(glGetUniformLocation(shaders[currentProgram],"NormalMatrix"), 1, GL_TRUE, glm::value_ptr(glm::inverse(glm::mat3(modelview))));
}

void WorldState::loadTransforms(glm::mat4 MV)
{
    // setup uniform variables
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"ModelViewMatrix"),1, GL_FALSE, glm::value_ptr(MV));
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"MVP"), 1, GL_FALSE, glm::value_ptr(projection * MV));

    /* the Normal Matrix is the inverse transpose of the upper left 3x3 modelview matrix
     * this is used to transform normals, as they do not transform the same way as
     * vertices. */
    glUniformMatrix3fv(glGetUniformLocation(shaders[currentProgram],"NormalMatrix"), 1, GL_TRUE, glm::value_ptr(glm::inverse(glm::mat3(MV))));
}

void WorldState::loadTransforms(glm::mat4 MV, glm::mat4 P)
{
    // setup uniform variables
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"ModelViewMatrix"),1, GL_FALSE, glm::value_ptr(MV));
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(P));
    glUniformMatrix4fv(glGetUniformLocation(shaders[currentProgram],"MVP"), 1, GL_FALSE, glm::value_ptr(P * MV));

    /* the Normal Matrix is the inverse transpose of the upper left 3x3 modelview matrix
     * this is used to transform normals, as they do not transform the same way as
     * vertices. */
    glUniformMatrix3fv(glGetUniformLocation(shaders[currentProgram],"NormalMatrix"), 1, GL_TRUE, glm::value_ptr(glm::inverse(glm::mat3(MV))));
}

void WorldState::loadLight(unsigned int i)
{
    glUniform4fv(glGetUniformLocation(shaders[currentProgram], "Light.Position"), 1, glm::value_ptr(lights[i].Position));
    glUniform3fv(glGetUniformLocation(shaders[currentProgram], "Light.La"), 1, glm::value_ptr(lights[i].La));
    glUniform3fv(glGetUniformLocation(shaders[currentProgram], "Light.Ld"), 1, glm::value_ptr(lights[i].Ld));
    glUniform3fv(glGetUniformLocation(shaders[currentProgram], "Light.Ls"), 1, glm::value_ptr(lights[i].Ls));
}

void WorldState::loadLights()
{
    // TODO: each load light currently overwrites itself, need to fix shaders and loadLight(i)
    for (unsigned int i = 0; i < lights.size(); i++)
        loadLight(i);
}

void WorldState::loadMaterial(unsigned int i)
{
    glUniform3fv(glGetUniformLocation(shaders[currentProgram], "Material.Ka"), 1, glm::value_ptr(materials[i].Ka));
    glUniform3fv(glGetUniformLocation(shaders[currentProgram], "Material.Kd"), 1, glm::value_ptr(materials[i].Kd));
    glUniform3fv(glGetUniformLocation(shaders[currentProgram], "Material.Ks"), 1, glm::value_ptr(materials[i].Ks));
    glUniform1f(glGetUniformLocation(shaders[currentProgram], "Material.Shininess"), materials[i].Shininess);
}

void WorldState::loadMaterials()
{
    // TODO: each load material currently overwrites itself, need to fix shaders and loadMaterial(i)
    for (unsigned int i = 0; i < materials.size(); i++)
        loadMaterial(i);
}
