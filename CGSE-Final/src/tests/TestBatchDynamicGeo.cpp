#include "TestBatchDynamicGeo.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <array>

struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec4 Color;
	float TexID;
};

namespace test {


	TestBatchDynamicGeo::TestBatchDynamicGeo() : m_Translation0(0,0,0), m_TranslationA(0.0, 0, 0), m_TranslationB(0,0,0),
		m_Proj(glm::perspective(35.0f, 1.0f, 0.1f, 100.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{

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

		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, 8 * layout.GetStride() * 1000, GL_DYNAMIC_DRAW);

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
	TestBatchDynamicGeo::~TestBatchDynamicGeo()
	{
	}
	void TestBatchDynamicGeo::OnUpdate(float deltaTime)
	{
	}

	static std::array<Vertex, 4> CreateQuad(glm::vec3 position, float textureID) {

		float size = 1.0f;

		Vertex v0;
		v0.Position = position;
		v0.TexCoords = {0.0f, 0.0f};
		v0.Color = {0.18f, 0.6f, 0.9f, 1.0f};
		v0.TexID = textureID;

		Vertex v1;
		v1.Position = {position.x + size, position.y, position.z};
		v1.TexCoords = { 1.0f,	0.0f };
		v1.Color = { 0.18f, 0.6f, 0.9f, 1.0f };
		v1.TexID = textureID;

		Vertex v2;
		v2.Position = { position.x + size, position.y + size, position.z };;
		v2.TexCoords = { 1.0f,	1.0f };
		v2.Color = { 0.18f, 0.6f, 0.9f, 1.0f };
		v2.TexID = textureID;

		Vertex v3;
		v3.Position = { position.x, position.y + size, position.z };;
		v3.TexCoords = { 0.0f,	1.0f };
		v3.Color = { 0.18f, 0.6f, 0.9f, 1.0f };
		v3.TexID = textureID;

		return { v0,v1,v2,v3 };
	}

	void TestBatchDynamicGeo::OnRender()
	{
		Renderer renderer;

		//Set dynamic vertex Buffer

		auto q0 = CreateQuad(m_TranslationA, 0.0f);
		auto q1 = CreateQuad(m_TranslationB, 1.0f);

		Vertex positions[8];
		memcpy(positions, q0.data(), q0.size() * sizeof(Vertex));
		memcpy(positions + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

		m_VertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation0);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);



	}

	//H-IAMGUI TODO: Delete later if possible ################## 
	void TestBatchDynamicGeo::OnImGuiRender()
	{
		ImGui::SliderFloat3("Base Translation", &m_Translation0.x, -3.0f, 3.0f);
		ImGui::SliderFloat3("Translation 1", &m_TranslationA.x, -3.0f, 3.0f);
		ImGui::SliderFloat3("Translation 2", &m_TranslationB.x, -3.0f, 3.0f);
		ImGui::Text("Application avarger %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}