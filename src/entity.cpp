#include "entity.h"

XE::Entity::Entity(glm::vec3 center, glm::vec3 scaling, glm::vec3 euler)
{
	Center = center;
	Scaling = scaling;
	Euler = euler;
}

glm::mat4 XE::Entity::getModelMatrix()
{
	return	glm::translate(glm::mat4(1.0f), Center) *
		glm::scale(glm::mat4(1.0f), Scaling) *
		//glm::translate(glm::mat4(1.0f), Center) *
		glm::mat4_cast(getOrientation());//*
			//glm::translate(glm::mat4(1.0f), -Center);
}

void XE::Entity::translate(const glm::vec3& t)
{
	Center = t;
}

void XE::Entity::scale(const glm::vec3& s)
{
	Scaling = s;
}

void XE::Entity::scale(const float& s)
{
	Scaling = glm::vec3(s);
}

void XE::Entity::rotate(const glm::vec3& euler)
{
	Euler = euler;
}

void XE::Entity::setViewDir(const glm::vec3& dir)
{
	Euler.x = asin(dir.y);
	Euler.y = atan2(-dir.x, -dir.z);
}

void XE::Entity::setOrientation(const glm::quat& q)
{
	Euler = glm::vec3(glm::pitch(q), glm::yaw(q), glm::roll(q));
}

glm::vec3 XE::Entity::getCenter()
{
	return Center;
}

glm::vec3 XE::Entity::getScale()
{
	return Scaling;
}

glm::vec3 XE::Entity::getEuler()
{
	return Euler;
}

glm::vec3 XE::Entity::getViewDir()
{
	return glm::quat(Euler) * glm::vec3(0, 0, -1);
}

glm::vec3 XE::Entity::getUpVector()
{
	return glm::quat(Euler) * glm::vec3(0, 1, 0);
}

glm::quat XE::Entity::getOrientation()
{
	return glm::quat(Euler);
}
