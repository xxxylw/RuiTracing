#include "Camera.h"

Camera::Camera(glm::vec3 center, int image_width, float viewport_height, double focal_length, double aspect_ratio)
	: m_center(center), m_image_width(image_width), m_viewport_height(viewport_height), m_aspect_ratio(aspect_ratio), m_focal_length(focal_length)
{
	m_image_height = int(image_width / aspect_ratio);
	m_viewport_width = aspect_ratio * m_viewport_height;

	auto viewport_u = glm::vec3(m_viewport_width, 0, 0);
	auto viewport_v = glm::vec3(0, m_viewport_height, 0);

	m_pixel_delta_u = viewport_u / m_image_width;
	m_pixel_delta_v = viewport_v / m_image_height;

	auto viewport_upper_left = center - glm::vec3(0, 0, m_focal_length) - viewport_u / 2.0f - viewport_v / 2.0f;

	m_pixel00_loc = viewport_upper_left + 0.5f * (m_pixel_delta_u + m_pixel_delta_v);
}

void Camera::Update(int image_width)
{
	if (image_width == m_image_width)
		return;

	m_image_width = image_width;
	m_image_height = int(m_image_width / m_aspect_ratio);

	glm::vec3 viewport_u = glm::vec3(m_viewport_width, 0, 0);
	glm::vec3 viewport_v = glm::vec3(0, m_viewport_height, 0);

	m_pixel_delta_u = viewport_u / (float)m_image_width;
	m_pixel_delta_v = viewport_v / (float)m_image_height;

	auto viewport_upper_left = m_center - glm::vec3(0, 0, m_focal_length) - viewport_u / 2.0f - viewport_v / 2.0f;

	m_pixel00_loc = viewport_upper_left + 0.5f * (m_pixel_delta_u + m_pixel_delta_v);
}
