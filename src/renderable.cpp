#include "renderable.h"

using namespace XE;

Renderable::Renderable(bool withPositions, bool withTextureCoordinates, bool withNormals) : Entity()
{
	HasPositions = withPositions;
	HasTextureCoordinates = withTextureCoordinates;
	HasNormals = withNormals;
}

Renderable::~Renderable()
{
	deleteMesh();
}

void Renderable::deleteMesh()
{
	if (!Initialized)
	{
		return;
	}

	glDeleteVertexArrays(1, &Vao);
	Vbo.deleteVBO();

	Initialized = false;
}

bool Renderable::hasPositions()
{
	return HasPositions;
}

bool Renderable::hasTextureCoordinates()
{
	return HasTextureCoordinates;
}

bool Renderable::hasNormals()
{
	return HasNormals;
}

int Renderable::getVertexByteSize()
{
	int size = 0;
	size += HasPositions ? sizeof(glm::vec3) : 0;
	size += HasTextureCoordinates ? sizeof(glm::vec2) : 0;
	size += HasNormals ? sizeof(glm::vec3) : 0;

	return size;
}

void XE::Renderable::setMaterialInfo()
{
	// Gets program that draws this renderable
	auto& program = ShaderProgramManager::getInstance().getShaderProgram(ShaderName);

	// Set up material properties, color and bool
	program["material.Color"] = MaterialProp.Color;
	program["material.Diffuse"] = MaterialProp.Diffuse;
	program["material.Specular"] = MaterialProp.Specular;
	program["material.Emission"] = MaterialProp.Emission;
	program["material.Shininess"] = MaterialProp.Shininess;
	program["material.Active"] = MaterialProp.Active;

	// Also setup model matrix
	program["mvp.ModelMatrix"] = getModelMatrix();
}

void XE::Renderable::setShader(const std::string& name)
{
	ShaderName = name;
}

void XE::Renderable::setDiffuse(const std::string& name)
{
	int tempUnit = TextureManager::getInstance().getTexture(name).getTextureUnit();
	MaterialProp.Diffuse = tempUnit;
}

void XE::Renderable::setSpecular(const std::string& name)
{
	int tempUnit = TextureManager::getInstance().getTexture(name).getTextureUnit();
	MaterialProp.Specular = tempUnit;
}

void XE::Renderable::setEmission(const std::string& name)
{
	int tempUnit = TextureManager::getInstance().getTexture(name).getTextureUnit();
	MaterialProp.Emission = tempUnit;
}

void Renderable::setVertexAttributesPointers(int numVertices)
{
	uint64_t offset = 0;
	if (HasPositions)
	{
		glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);
		glVertexAttribPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

		offset += sizeof(glm::vec3) * numVertices;
	}

	if (HasTextureCoordinates)
	{
		glEnableVertexAttribArray(TEXTURE_COORDINATE_ATTRIBUTE_INDEX);
		glVertexAttribPointer(TEXTURE_COORDINATE_ATTRIBUTE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(offset));

		offset += sizeof(glm::vec2) * numVertices;
	}

	if (HasNormals)
	{
		glEnableVertexAttribArray(NORMAL_ATTRIBUTE_INDEX);
		glVertexAttribPointer(NORMAL_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

		offset += sizeof(glm::vec3) * numVertices;
	}
}
