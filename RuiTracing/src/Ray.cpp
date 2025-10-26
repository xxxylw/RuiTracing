#include "Ray.h"
Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
	: m_Orig(origin), m_Dir(direction)
{

}

glm::vec3 Ray::at(float t) const
{
	return m_Orig + t * m_Dir;
}

