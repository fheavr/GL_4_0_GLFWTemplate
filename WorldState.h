#ifndef WORLD_STATE_H
#define WORLD_STATE_H

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

#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Lighting state
struct LightInfo
{
    glm::vec4 Position;
    glm::vec3 La;       // ambient light
    glm::vec3 Ld;       // diffuse light
    glm::vec3 Ls;       // specular light

    // some default initialization parameters
    LightInfo() 
        : Position(10, 6, 4, 0), 
          La(0.5, 0.5, 0.5),
          Ld(0.5, 0.5, 0.5),
          Ls(0.5, 0.5, 0.5) {}
};

// Material and Color state
struct MaterialInfo
{
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    float Shininess;

    // some default initialization parameters
    MaterialInfo() 
        : Ka(0.5, 0.5, 0.5),
          Kd(0.5, 0.5, 0.5),
          Ks(0.5, 0.5, 0.5),
          Shininess(0.5f) {}
};

class WorldState
{
public:
    WorldState();
    ~WorldState();

    // store and set current active shaders
    void useProgram(unsigned int i);
    void setProgram(unsigned int i, GLuint program);

    // send transform matrices, lights, materials to the GPU
    void loadTransforms();                          // load global matrices
    void loadTransforms(glm::mat4 MV);              // load custom MV matrix, use global P
    void loadTransforms(glm::mat4 MV, glm::mat4 P); // load custom matrices
    void loadLights();                              // load all lights
    void loadLight(unsigned int i);                 // load specific light
    void loadMaterials();                           // load all materials
    void loadMaterial(unsigned int i);              // load specific material

    //default initialized to the identity matrix
    glm::mat4 modelview;
    glm::mat4 projection;

    std::vector<LightInfo>    lights;
    std::vector<MaterialInfo> materials;
    std::vector<GLuint>       shaders;

private:
    unsigned int currentProgram;

};

#endif // WORLD_STATE_H