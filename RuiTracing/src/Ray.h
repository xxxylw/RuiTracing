#pragma once

#include <glm/glm.hpp>


class Ray
{
public:
	Ray() = default;

	Ray(const glm::vec3& origin, const glm::vec3& direction);
	const glm::vec3& origin() const { return m_Orig; }
	glm::vec3 at(float t) const;
	const glm::vec3& direction() const { return m_Dir; }

private:
	glm::vec3 m_Orig;
	glm::vec3 m_Dir;
};