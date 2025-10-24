#include "Renderer.h"

#include "Walnut/Random.h"

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;
		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}

void Renderer::Render()
{
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			glm::vec2 coord = { (float)x / m_FinalImage->GetWidth(),(float)y / m_FinalImage->GetHeight() };
			coord = coord * 2.0f - 1.0f; // -1 -> 1
			m_ImageData[x + y * m_FinalImage->GetWidth()] = PerPixel(coord);
		}
	}

	m_FinalImage->SetData(m_ImageData);
}

uint32_t Renderer::PerPixel(glm::vec2 coord)
{
	/* 其实这里就是用coords的坐标表示ray了，没有引入camera和vitrual viewport的概念 */
	glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
	glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
	glm::vec3 sphereCenter(0, 0, 0);
	float radius = 0.5f;

	glm::vec3 oc = sphereCenter - rayOrigin;
	float a = glm::dot(rayDirection, rayDirection);
	float h = glm::dot(rayDirection, oc);
	float c = glm::dot(oc, oc) - radius * radius;
	
	float discriminant = h * h - a * c;
	if (discriminant < 0)
	{
		return 0xff000000;
	}

	auto t = (h - glm::sqrt(discriminant) / a);
	if (t < 0.0f)
		return 0xff000000;
	glm::vec3 N = glm::normalize((rayOrigin + t * rayDirection) - sphereCenter);
	glm::vec3 color = 0.5f * (N + glm::vec3(1.0f));

	uint8_t r = static_cast<uint8_t>(color.r * 255.0f);
	uint8_t g = static_cast<uint8_t>(color.g * 255.0f);
	uint8_t b = static_cast<uint8_t>(color.b * 255.0f);

	uint32_t result = (0xff << 24) | (b << 16) | (g << 8) | r;
	return result;
}

