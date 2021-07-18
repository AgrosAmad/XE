#pragma once

// GLM
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
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
		virtual void Translate(const glm::vec3& t);
		virtual void Scale(const glm::vec3& s);
		virtual void Scale(const float& s);
		virtual void Rotate(const glm::vec3& euler);
		virtual void SetViewDir(const glm::vec3& dir);
		virtual void SetOrientation(const glm::quat& q);

		virtual glm::vec3 GetCenter();
		virtual glm::vec3 GetScale();
		virtual glm::vec3 GetEuler();
		virtual glm::vec3 GetViewDir();
		virtual glm::vec3 GetUpVector();
		virtual glm::quat GetOrientation();

	protected:
		glm::vec3 Center; 
		glm::vec3 Scaling; // Vector with scale factors
		glm::vec3 Euler; // Euler angles for orientation 
	};
}
