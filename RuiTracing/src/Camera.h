#pragma once
#include <glm/glm.hpp>
#include <memory>

class Camera
{
public:
	Camera(glm::vec3 center, int image_width, float viewport_height=2.0f, double focal_length=1.0f, double aspect_ratio=16 / (double)9);
	void Update(int image_width);

public:
	float m_focal_length;
	float m_aspect_ratio;
	float m_image_width, m_image_height;

	float m_viewport_height, m_viewport_width;
	glm::vec3 m_center;

	glm::vec3 m_pixel_delta_u;
	glm::vec3 m_pixel_delta_v;
	glm::vec3 m_pixel00_loc;
};