#version 440 core

struct MVP
{
    mat4 ModelMatrix;
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;

out vec2 TexCoords;
out vec3 Normal;

uniform MVP mvp;

void main()
{
    mat4 M = mvp.ProjectionMatrix * mvp.ViewMatrix * mvp.ModelMatrix;
    gl_Position = M * vec4(vertexPosition, 1.0);
    TexCoords = vertexTexCoord;
    Normal = vertexNormal;
}