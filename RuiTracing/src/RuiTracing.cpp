#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Random.h"
#include"Walnut/Timer.h"

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
		: m_Renderer(Camera(glm::vec3(0, 0, 1), 100.0f))
	{
		Instrumentor::Get().BeginSession("Profile");
	}

	~ExampleLayer()
	{
		Instrumentor::Get().EndSession();
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

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		m_Renderer.GetCamera().Update(m_ViewportWidth);

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
		m_Renderer.Render();
		
		m_LastRenderTime = timer.ElapsedMillis();
	}
private:
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	float m_LastRenderTime = 0.0f;
	Renderer m_Renderer;
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