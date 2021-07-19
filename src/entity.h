#pragma once

// GLM
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

// STL
#include <string>
#include <vector>

namespace XE
{
	/*
	* Provides an easy way to handle entities (light/objects/cameras)
	*/
	class Entity
	{
	public:
		/*
		* Constructor, initializes internal structures
		*/
		Entity(glm::vec3 center = glm::vec3(0.f),
			   glm::vec3 scaling = glm::vec3(1.f),
			   glm::vec3 euler = glm::vec3(0.f));

		/*
		* Misc. functions for positioning entity in space
		*/
		virtual void translate(const glm::vec3& t);
		virtual void scale(const glm::vec3& s);
		virtual void scale(const float& s);
		virtual void rotate(const glm::vec3& euler);
		virtual void setViewDir(const glm::vec3& dir);
		virtual void setOrientation(const glm::quat& q);

		virtual glm::vec3 getCenter();
		virtual glm::vec3 getScale();
		virtual glm::vec3 getEuler();
		virtual glm::vec3 getViewDir();
		virtual glm::vec3 getUpVector();
		virtual glm::quat getOrientation();

	protected:
		glm::vec3 Center; 
		glm::vec3 Scaling; // Vector with scale factors
		glm::vec3 Euler; // Euler angles for orientation 
	};
}
