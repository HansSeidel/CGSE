#include "Renderer.h"
#include "imgui/imgui.h"

#include "Renderer.h"

#include "TestPlaneSingleCall.h"


namespace test {

	TestPlaneSingleCall::TestPlaneSingleCall() : m_Proj(glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -1.0f, 1.0f)), m_ViewTranslation(glm::vec3(0, 0, 0))
	{
		glm::vec3 position = { 0.0,0.0,0.0 };
		m_Plane = std::make_unique<extension::primitves::Plane>(position, 10.0f, 10.0f);
		
		m_Va = std::make_unique<VertexArray>();
		m_Vb = std::make_unique<VertexBuffer>();
		m_Ib = std::make_unique<IndexBuffer>();
		m_Shader = std::make_unique<Shader>();
		m_Plane->SetPlaneColor({ 0.2f,0.2f,0.7f,1.0f });
		m_Plane->SetupSingleCall(*m_Vb, *m_Va, *m_Ib, *m_Shader);
	}
	TestPlaneSingleCall::~TestPlaneSingleCall()
	{
	}
	void TestPlaneSingleCall::OnUpdate(float deltaTime)
	{
	}
	void TestPlaneSingleCall::OnRender()
	{
		Renderer renderer;


		{
			glm::mat4 view = glm::translate(glm::mat4(1.0f), m_ViewTranslation);
			glm::mat4 mvp = m_Proj * view;
			m_Plane->DrawSingleCall(renderer,*m_Va,*m_Ib,*m_Shader);
		}



	}

	//H-IAMGUI TODO: Delete later if possible ################## 
	void TestPlaneSingleCall::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation 1", &m_ViewTranslation.x, -3.0f, 3.0f);
		ImGui::Text("Application avarger %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}