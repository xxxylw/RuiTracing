#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Random.h"
#include"Walnut/Timer.h"

#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Renderer.h"

#include "Instramentor.h"
#define PROFILING 1
#if PROFILING
#define PROFILE_SOUPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SOUPE(__FUNCSIG__)
#else
#define PROFILE_FUNCTION()
#endif

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
public:
	ExampleLayer()
		: m_Camera(45.0f, 0.1f, 100.0f)
	{
		Instrumentor::Get().BeginSession("Profile");

		{
			Sphere sphere;
			sphere.Position = { -0.5f, 0.0f, 0.0f };
			sphere.Radius = 0.5f;
			sphere.Albedo = { 0.5f, 0.8f, 0.2f };
			m_Scene.Spheres.push_back(sphere);
		}

		{
			Sphere sphere;
			sphere.Position = { 0.5f, -1.0f, 0.7f };
			sphere.Radius = 0.75f;
			sphere.Albedo = { 0.2f, 0.5f, 0.8f };
			m_Scene.Spheres.push_back(sphere);
		}
	}

	~ExampleLayer()
	{
		Instrumentor::Get().EndSession();
	}

	virtual void OnUpdate(float ts) override
	{
		m_Camera.OnUpdate(ts);
	}

	virtual void OnUIRender() override
	{
		PROFILE_FUNCTION();

		ImGui::Begin("Settings");
		ImGui::Text("Last Render: %.3fms", m_LastRenderTime);
		if (ImGui::Button("Render"))
		{
			Render();
		}
		ImGui::End();

		ImGui::Begin("Scene");
		for (size_t i = 0; i < m_Scene.Spheres.size(); i++)
		{
			ImGui::PushID(i);

			ImGui::DragFloat3("Position", glm::value_ptr(m_Scene.Spheres[i].Position), 0.1f);
			ImGui::DragFloat("Radius", &m_Scene.Spheres[i].Radius, 0.1f);
			ImGui::ColorEdit3("Albedo", glm::value_ptr(m_Scene.Spheres[i].Albedo));
		
			ImGui::PopID();
		}
			ImGui::End();
		

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		/*ImGui::Text("Available: %.0f x %.0f", m_ViewportWidth, m_ViewportHeight);*/
		auto image = m_Renderer.GetFinalImage();
		if (image)
			ImGui::Image(
				image->GetDescriptorSet(), 
				{ (float)image->GetWidth(), 
				(float)image->GetHeight() }, 
				ImVec2(0, 1), 
				ImVec2(1, 0)
			);

		ImGui::End();
		ImGui::PopStyleVar();

		Render();
	}

	void Render()
	{
		PROFILE_FUNCTION();

		Timer timer;

		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Camera.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render(m_Scene, m_Camera);
		
		m_LastRenderTime = timer.ElapsedMillis();
	}
private:
	Renderer m_Renderer;
	Camera m_Camera;
	Scene m_Scene;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	
	float m_LastRenderTime = 0.0f;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Rui Tracing";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}