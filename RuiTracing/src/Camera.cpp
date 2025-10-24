#include "Camera.h"


Camera::Camera(float focal_length, float viewport_height, float center, float width, float height)
	: m_focal_length(focal_length), m_viewport_height(viewport_height), m_center(center)
{
	m_viewport_width = m_viewport_height * (width / height);
	
	glm::vec3 m_pixel_delta_u = glm::vec3(m_viewport_width, 0.0f, 0.0f) / width;
}
