#include "quad.h"

using namespace XE;

glm::vec3 Quad::Vertices[4] =
{
    glm::vec3(-1.0f,  1.0f, 0.0f), // Top-left point
    glm::vec3(-1.0f, -1.0f, 0.0f), // Bottom-left point
    glm::vec3( 1.0f,  1.0f, 0.0f), // Top-right point
    glm::vec3( 1.0f, -1.0f, 0.0f) // Bottom-right point
};

glm::vec2 Quad::TextureCoord[4] =
{
    glm::vec2(0.0f, 1.0f), // Top-left point
    glm::vec2(0.0f, 0.0f), // Bottom-left point
    glm::vec2(1.0f, 1.0f), // Top-right point
    glm::vec2(1.0f, 0.0f) // Bottom-right point
};

glm::vec3 Quad::Normals[4] =
{
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 0.0f, -1.0f),
    glm::vec3(0.0f, 0.0f, -1.0f)
};

Quad::Quad(bool withPositions, bool withTextureCoordinates, bool withNormals)
	: Renderable(withPositions, withTextureCoordinates, withNormals)
{
	initializeData();
}

void Quad::render() const
{
    if (!Initialized) 
    {
        return;
    }

    glBindVertexArray(Vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Quad::initializeData()
{
    if (Initialized) 
    {
        return;
    }

    glGenVertexArrays(1, &Vao);
    glBindVertexArray(Vao);

    const int numVertices = 4;
    int vertexByteSize = getVertexByteSize();
    Vbo.createVBO(vertexByteSize * numVertices);
    Vbo.bindVBO();

    if (HasPositions)
    {
        Vbo.addData(Vertices);
    }

    if (HasTextureCoordinates)
    {
        Vbo.addData(TextureCoord);
    }

    if (HasNormals)
    {
        Vbo.addData(Normals);
    }

    Vbo.uploadDataToGPU(GL_STATIC_DRAW);
    setVertexAttributesPointers(numVertices);
    Initialized = true;
}
