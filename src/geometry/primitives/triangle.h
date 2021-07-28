#pragma once

// XE
#include <renderable.h>
#include <iostream>

// GLM
#include <glm/glm.hpp>

namespace XE
{
	// Triangle static mesh of unit size
	class Triangle : public Renderable
	{
	public:
		Triangle(bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true);

		void render() const override;

		static glm::vec3 Vertices[3]; // Array of mesh vertices
		static glm::vec2 TextureCoord[3]; // Array of texture coordinates
		static glm::vec3 Normals[3]; // Array of normal vectors

	private:
		void initializeData() override;
	};
} // namespace XE
