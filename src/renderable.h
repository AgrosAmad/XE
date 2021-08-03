#pragma once

// STL
#include <memory>
#include <string>
#include <map>

// XE
#include <entity.h>
#include <vertexBufferObject.h>
#include <managers/shaderProgramManager.h>
#include <managers/textureManager.h>

namespace XE
{
	/*
	* Material properties, value of -1 means it does not apply
	* to this object
	*/
	struct MaterialSamplers
	{
		glm::vec3 Color = glm::vec3(0.f,0.f,0.f);
		int Diffuse     = -1;
		int Specular    = -1;
		int Emission    = -1;
		float Shininess = 1.f;
		bool Active     = false;
	};

	// Provides an easy way to handle drawable entities (objs, geometry)
	class Renderable : public Entity
	{
	public:
		// Atributte positions
		static const int POSITION_ATTRIBUTE_INDEX           = 0;
		static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1; 
		static const int NORMAL_ATTRIBUTE_INDEX             = 2;

		// Constructor, sets inner parameters
		Renderable(bool withPositions, bool withTextureCoordinates, bool withNormals);

		// Destructor, frees data
		virtual ~Renderable();

		// Standard methods of renderables
		virtual void render() {};
		virtual void renderPoints() const {};
		virtual void update() {};
		virtual void deleteMesh();

		// Checks if renderable has certain attributes
		bool hasPositions();
		bool hasTextureCoordinates();
		bool hasNormals();

		// Gets byte size of one vertex (depending on attributes)
		int getVertexByteSize();

		// Sets render mode of drawing (material properties or just plain color)
		void setMaterialInfo();

		// Changes shader in charge of drawing
		void setShader(const std::string& name);

		// Sets diffuse material by texture name
		void setDiffuse(const std::string& name);

		// Sets specular material by texture name
		void setSpecular(const std::string& name);

		// Sets emission material by texture name
		void setEmission(const std::string& name);

	protected:

		// Initialize vertex data 
		virtual void initializeData() {};

		// For managing renderable and its attributes
		bool HasPositions = true;
		bool HasTextureCoordinates = true;
		bool HasNormals = false;
		bool Initialized = false;

		// Material properties/color
		MaterialSamplers MaterialProp;

		// OpenGL data
		GLuint Vao = 0;
		VertexBufferObject Vbo;

		// Sets vertex attribute pointers in standard way
		void setVertexAttributesPointers(int numVertices);

		// Name of the program responsible for drawing this object
		std::string ShaderName;
	};
}
