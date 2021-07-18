#include "entity.h"

XE::Entity::Entity(glm::vec3 center, glm::vec3 scaling, glm::vec3 euler)
{
	Center = center;
	Scaling = scaling;
	Euler = euler;
}

void XE::Entity::Translate(const glm::vec3& t)
{
	Center = t;
}

void XE::Entity::Scale(const glm::vec3& s)
{
	Scaling = s;
}

void XE::Entity::Scale(const float& s)
{
	Scaling = glm::vec3(s);
}

void XE::Entity::Rotate(const glm::vec3& euler)
{
	Euler = euler;
}

void XE::Entity::SetViewDir(const glm::vec3& dir)
{
	Euler.x = asin(dir.y);
	Euler.y = atan2(-dir.x, -dir.z);
}

void XE::Entity::SetOrientation(const glm::quat& q)
{
	Euler = glm::vec3(glm::pitch(q), glm::yaw(q), glm::roll(q));
}

glm::vec3 XE::Entity::GetCenter()
{
	return Center;
}

glm::vec3 XE::Entity::GetScale()
{
	return Scaling;
}

glm::vec3 XE::Entity::GetEuler()
{
	return Euler;
}

glm::vec3 XE::Entity::GetViewDir()
{
	return glm::quat(Euler) * glm::vec3(0, 0, -1);
}

glm::vec3 XE::Entity::GetUpVector()
{
	return glm::quat(Euler) * glm::vec3(0, 1, 0);
}

glm::quat XE::Entity::GetOrientation()
{
	return glm::quat(Euler);
}
