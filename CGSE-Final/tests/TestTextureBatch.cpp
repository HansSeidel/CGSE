#include "TestTextureBatch.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	TestTextureBatch::TestTextureBatch() : m_TranslationA(0.0, 0, 0), 
		m_Proj(glm::perspective(35.0f, 1.0f, 0.1f, 100.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{

		float positions[] = {
			-1.5f,		-0.5f,	-1.0f,	0.0,	0.0,	0.18f,0.6f,0.9f,1.0f,  0.0f,
			-0.5f,		-0.5f,	-1.0f,	1.0,	0.0,	0.18f,0.6f,0.9f,1.0f,  0.0f,
			-0.5f,		 0.5f,	-1.0f,	1.0,	1.0,	0.18f,0.6f,0.9f,1.0f,  0.0f,
			-1.5f,		 0.5f,	-1.0f,	0.0,	1.0,	0.18f,0.6f,0.9f,1.0f,  0.0f,

			 0.5f,		-0.5f,	-1.0f,	0.0,	0.0,	0.4f,0.4f,0.1f,1.0f,   1.0f,
			 1.5f,		-0.5f,	-1.0f,	1.0,	0.0,	0.4f,0.4f,0.1f,1.0f,   1.0f,
			 1.5f,		 0.5f,	-1.0f,	1.0,	1.0,	0.4f,0.4f,0.1f,1.0f,   1.0f,
			 0.5f,		 0.5f,	-1.0f,	0.0,	1.0,	0.4f,0.4f,0.1f,1.0f,   1.0f
		};
		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(4);
		layout.Push<float>(1);

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * layout.GetStride());

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);


		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();

		m_Texture1 = std::make_unique<Texture>("res/textures/brown_rock_19_78_diffuse.jpg");
		m_Texture2 = std::make_unique<Texture>("res/textures/light_fine_wood_pbr_18_13_diffuse.jpg"); 
		m_Texture1->Bind();
		m_Texture2->Bind(1);
		int samplers[2] = { 0, 1 };
		m_Shader->setUniform1iv("u_TextureArr", 2, samplers); 
	}
	TestTextureBatch::~TestTextureBatch()
	{
	}
	void TestTextureBatch::OnUpdate(float deltaTime)
	{
	}
	void TestTextureBatch::OnRender()
	{
		Renderer renderer;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);



	}

	//H-IAMGUI TODO: Delete later if possible ################## 
	void TestTextureBatch::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation 1", &m_TranslationA.x, -3.0f, 3.0f);
		ImGui::Text("Application avarger %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}