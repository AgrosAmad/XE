#version 440 core

struct Matrices
{
    mat4 ProjectionMatrix;
    mat4 ModelMatrix;
};

uniform Matrices matrices;

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;

out vec2 texCoords;

void main()
{
    mat4 MVP = matrices.ProjectionMatrix * matrices.ModelMatrix;
    gl_Position = MVP * vec4(vertexPosition, 0.0f, 1.0f);
    texCoords = vertexTexCoord;
}