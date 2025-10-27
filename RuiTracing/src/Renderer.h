#pragma once

#include "Walnut/Image.h"

#include "memory"
#include <glm/glm.hpp>
#include "Camera.h"
#include "Ray.h"

class Renderer
{
public:
	Renderer(Camera camera);
	~Renderer();

	void OnResize(uint32_t width, uint32_t height);
	Camera& GetCamera();
	void Render();

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }

private:
	float HitSphere(const glm::vec3& center, double radius, const Ray& r);
	glm::vec4 PerPixel(glm::vec2 coord);
	glm::vec4 RayColor(Ray& ray);

private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;
	Camera m_Camera;
};