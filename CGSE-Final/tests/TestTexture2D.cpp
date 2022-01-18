#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	TestTexure2D::TestTexure2D() : m_TranslationA(1,1,0), m_TranslationB(-1,-1,0),
		m_Proj(glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		
		float positions[] = {
			-0.5f,		-0.5f,		0.0,	0.0,
			 0.5f,		-0.5f,		1.0,	0.0,
			 0.5f,		 0.5f,		1.0,	1.0,
			-0.5f,		 0.5f,		0.0,	1.0,
		};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		


		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * layout.GetStride());

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);


		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->setUniform4f("u_Color", 0.8f, 0.8f, 0.2f, 1.0f);

		m_Texture = std::make_unique<Texture>("res/textures/light_fine_wood_pbr_18_13_diffuse.jpg");

	}
	TestTexure2D::~TestTexure2D()
	{
	}
	void TestTexure2D::OnUpdate(float deltaTime)
	{
	}
	void TestTexure2D::OnRender()
	{
		Renderer renderer;

		m_Texture->Bind(); //H-Optional Slot


		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->setUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->setUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}



	}

	//H-IAMGUI TODO: Delete later if possible ################## 
	void TestTexure2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation 1", &m_TranslationA.x, -3.0f, 3.0f);
		ImGui::SliderFloat3("Translation 2", &m_TranslationB.x, -3.0f, 3.0f);
		ImGui::Text("Application avarger %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}