#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Sphere
{
	glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
	float Radius = 0.5f;

	glm::vec3 Albedo = { 0.5f, 0.8f, 0.3f };
};

struct Scene
{
	std::vector<Sphere> Spheres;
};