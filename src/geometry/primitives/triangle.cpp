#include "triangle.h"

using namespace XE;

glm::vec3 Triangle::Vertices[3] =
{
	glm::vec3(-0.5f, -0.5f, 0.0f), //left
	glm::vec3( 0.5f, -0.5f, 0.0f), //right
	glm::vec3( 0.0f,  0.5f, 0.0f) //top
};

glm::vec2 Triangle::TextureCoord[3] =
{
	glm::vec2(0.0f, 0.0f),  // left  
	glm::vec2(1.0f, 0.0f),  // right
	glm::vec2(0.5f, 1.0f)   // top
};

glm::vec3 Triangle::Normals[3] =
{
	glm::vec3(0.0f, 0.0f, -1.0f),
	glm::vec3(0.0f, 0.0f, -1.0f),
	glm::vec3(0.0f, 0.0f, -1.0f)
};

Triangle::Triangle(bool withPositions, bool withTextureCoordinates, bool withNormals) 
	: Renderable(withPositions, withTextureCoordinates, withNormals)
{
	initializeData();
}

void XE::Triangle::render()
{
	if (!Initialized)
	{
		return;
	}

	glBindVertexArray(Vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void XE::Triangle::initializeData()
{
	if (Initialized)
	{
		return;
	}

	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);

	const int numVertices = 3;
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

	Vbo.uploadDataToGPU(GL_STATIC_DRAW);
	setVertexAttributesPointers(numVertices);
	Initialized = true;
}
