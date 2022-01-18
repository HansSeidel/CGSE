#include "Renderer.h"
#include "imgui/imgui.h"

#include "Renderer.h"

#include "TestPlaneSingleCall.h"


namespace test {

	TestPlaneSingleCall::TestPlaneSingleCall() : m_Proj(glm::perspective(35.0f, 1.0f, 0.1f, 100.0f)), m_ViewTranslation(glm::vec3(0, 0, 0))
	{
		
		glm::vec3 position = { 0.0,0.0,0.0 };
		m_Plane = std::make_unique<extension::primitves::Plane>(position, 10.0f, 10.0f);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		//m_Plane->SetPlaneColor({ 0.2f,0.2f,0.7f,1.0f });
		m_Plane->BindTextureSlot(1.0f);
		m_Plane->SetupSingleCall();
		
		//Texture base;
		//m_Texture = std::make_unique<Texture>("res/textures/brown_rock_19_78_diffuse.jpg");
		//base.Bind();
		//m_Texture->Bind(1);
		m_Texture1 = std::make_unique<Texture>("res/textures/brown_rock_19_78_diffuse.jpg");
		m_Texture2 = std::make_unique<Texture>("res/textures/light_fine_wood_pbr_18_13_diffuse.jpg");
		m_Texture1->Bind();
		m_Texture2->Bind(1);

		int sampler[8];
		for (int i = 0; i < 8; i++)
			sampler[i] = i;
		m_Shader->setUniform1iv("u_TextureArr", 8, sampler);
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

		glm::mat4 view = glm::translate(glm::mat4(1.0f), m_ViewTranslation);
		glm::mat4 mvp = m_Proj * view;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);
		m_Plane->DrawSingleCall(renderer, *m_Shader);



	}

	//H-IAMGUI TODO: Delete later if possible ################## 
	void TestPlaneSingleCall::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation 1", &m_ViewTranslation.x, -3.0f, 3.0f);
		ImGui::Text("Application avarger %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}