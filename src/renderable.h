#pragma once

// STL
#include <memory>
#include <string>
#include <map>

// XE
#include <entity.h>
#include <vertexBufferObject.h>

namespace XE
{
	class ShaderProgramManager;
	class TextureManager;

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
		virtual void render() const {};
		virtual void renderPoints() const {};
		virtual void update() {};
		virtual void deleteMesh();

		// Checks if renderable has certain attributes
		bool hasPositions();
		bool hasTextureCoordinates();
		bool hasNormals();

		// Gets byte size of one vertex (depending on attributes)
		int getVertexByteSize();

	protected:

		// Initialize vertex data 
		virtual void initializeData() {};

		// For managing renderable and its attributes
		bool HasPositions = true;
		bool HasTextureCoordinates = true;
		bool HasNormals = false;
		bool Initialized = false;

		// OpenGL data
		GLuint Vao = 0;
		VertexBufferObject Vbo;

		// Sets vertex attribute pointers in standard way
		void setVertexAttributesPointers(int numVertices);
	};
}
