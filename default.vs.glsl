#version 400

// Copyright (c) Russell Gillette
// December 2013

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

uniform vec3 color;
out vec3 LightIntensity;

struct LightInfo
{
    vec4 Position;
    vec3 La;       // ambient light
    vec3 Ld;       // diffuse light
    vec3 Ls;       // specular light
};
uniform LightInfo Light;

struct MaterialInfo
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;
};
uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;      // we keep a MV matrix without the translation component to apply to vectors
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;               // ModelViewProjection Matrix

void main()
{
    vec3 tnorm     = normalize( NormalMatrix * Normal );
    vec4 eyeCoords = ModelViewMatrix * vec4(Position, 1.0);
    vec3 s         = normalize( vec3(Light.Position - eyeCoords) ); // incident vector
    vec3 v         = normalize( -eyeCoords.xyz );                   // vector towards viewer
    vec3 r         = reflect( -s, tnorm );                          // reflected vector
    vec3 ambient   = Light.La * Material.Ka;
    float sDotN    = max( dot(s, tnorm), 0.0 );
    vec3 diffuse   = Light.Ld * Material.Kd * sDotN;
    vec3 spec      = vec3(0.0);
    if (sDotN > 0.0)
        spec = Light.Ls * Material.Ks *
               pow( max( dot(r,v), 0.0 ), Material.Shininess );
    LightIntensity = ambient + diffuse + spec;
    gl_Position = MVP * vec4(Position, 1.0);
}