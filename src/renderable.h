#pragma once

// STL
#include <memory>
#include <string>
#include <map>

// OpenGL
#include <GL/glew.h>

// XE
#include <entity.h>

namespace XE
{
	class ShaderProgramManager;
	class TextureManager;

	/*
	* Provides an easy way to handle drawable entities (objs, geometry)
	*/
	class Renderable : public Entity
	{
	public:
		/*
		* Constructor, sets inner parameters
		*/
		Renderable();

		/*
		* Standard methods of renderables
		*/
		virtual void Render();
		virtual void Update();
	};
}
