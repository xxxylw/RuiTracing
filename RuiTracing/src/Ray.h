#pragma once

#include <glm/glm.hpp>

struct Ray
{
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
public:
	glm::vec3 at(float t) const { return Origin + t * Direction; }
};