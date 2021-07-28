#pragma once

// XE
#include <renderable.h>
#include <iostream>

// GLM
#include <glm/glm.hpp>

namespace XE
{
	// Quad static mesh of unit size
	class Quad : public Renderable
	{

	public:

		Quad(bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true);

		void render() const override;
		
		static glm::vec3 Vertices[4]; // Array of mesh vertices
		static glm::vec2 TextureCoord[4]; // Array of texture coordinates
		static glm::vec3 Normals[4]; // Array of normal vectors 

	private:
		void initializeData() override;
	};
} // namespace XE
