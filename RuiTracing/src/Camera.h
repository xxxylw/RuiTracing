#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(float focal_length, float viewport_height, float center, float width, float height);


public:
	float m_focal_length;
	float m_viewport_height, m_viewport_width;
	float m_center;

	glm::vec3 m_pixel_delta_u;
	glm::vec3 m_pixel_delta_v;
	glm::vec3 m_pixel00_loc;
};