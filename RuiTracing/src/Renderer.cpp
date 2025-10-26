#include "Renderer.h"

namespace Utils {
	static uint32_t ConvertToRGBA(const glm::vec4& color)
	{
		uint8_t r = (uint8_t)(color.r * 255.0f);
		uint8_t g = (uint8_t)(color.g * 255.0f);
		uint8_t b = (uint8_t)(color.b * 255.0f);
		uint8_t a = (uint8_t)(color.a * 255.0f);

		uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
		return result;
	}
}

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

			glm::vec4 color = PerPixel(coord);
			color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
			m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(color);
		}
	}

	m_FinalImage->SetData(m_ImageData);
}

glm::vec4 Renderer::PerPixel(glm::vec2 coord)
{
	/* 其实这里就是用coords的坐标表示ray了，没有引入camera和vitrual viewport的概念 */
	glm::vec3 rayOrigin(0.0f, 0.0f, 1.0f);
	glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
	glm::vec3 sphereCenter(0, 0, 0);
	float radius = 0.5f;

	//Light
	glm::vec3 lightDir = glm::normalize(glm::vec3(-1, -1, -1));

	glm::vec3 oc = sphereCenter - rayOrigin;
	float a = glm::dot(rayDirection, rayDirection);
	float h = glm::dot(rayDirection, oc);
	float c = glm::dot(oc, oc) - radius * radius;
	
	float discriminant = h * h - a * c;
	if (discriminant < 0.0f)
	{
		return glm::vec4(0, 0, 0, 1);
	}

	auto t = (h - glm::sqrt(discriminant) / a);
	glm::vec3 hitPoint = rayOrigin + rayDirection * t;
	if (t < 0.0f)
		return glm::vec4(0, 0, 0, 1);
	glm::vec3 N = glm::normalize((hitPoint) - sphereCenter);
	float lightIntensity = glm::max(glm::dot(N, -lightDir), 0.0f);

	glm::vec3 sphereColor(1, 0, 1);
	sphereColor *= lightIntensity;

	return glm::vec4(sphereColor, 1.0f);
}

