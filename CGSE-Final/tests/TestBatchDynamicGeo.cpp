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


	TestBatchDynamicGeo::TestBatchDynamicGeo() : m_Translation0(-1.5,0,-1), m_TranslationA(0, 0, 0), m_TranslationB(2,0,0),
		m_Proj(glm::perspective(35.0f, 1.0f, 0.1f, 100.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		const size_t maxQuadCount = 500;
		const size_t maxVertexCount = maxQuadCount * 4;
		const size_t maxIndexCount = maxQuadCount * 6;

		unsigned int indices[maxIndexCount];
		unsigned int offset = 0;
		for (size_t i = 0; i < maxIndexCount;i += 6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(4);
		layout.Push<float>(1);

		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, maxVertexCount * layout.GetStride(), GL_DYNAMIC_DRAW);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 0);


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

	static Vertex* CreateQuad(Vertex* target, glm::vec3 position, float textureID) {

		float size = 1.0f;

		target->Position = position;
		target->TexCoords = {0.0f, 0.0f};
		target->Color = {0.18f, 0.6f, 0.9f, 1.0f};
		target->TexID = textureID;
		target++;

		target->Position = {position.x + size, position.y, position.z};
		target->TexCoords = { 1.0f,	0.0f };
		target->Color = { 0.18f, 0.6f, 0.9f, 1.0f };
		target->TexID = textureID;
		target++;

		target->Position = { position.x + size, position.y + size, position.z };;
		target->TexCoords = { 1.0f,	1.0f };
		target->Color = { 0.18f, 0.6f, 0.9f, 1.0f };
		target->TexID = textureID;
		target++;

		target->Position = { position.x, position.y + size, position.z };;
		target->TexCoords = { 0.0f,	1.0f };
		target->Color = { 0.18f, 0.6f, 0.9f, 1.0f };
		target->TexID = textureID;
		target++;

		return target;
	}

	void TestBatchDynamicGeo::OnRender()
	{
		Renderer renderer;
		m_IndexBuffer->ClearCount();
		//Set dynamic vertex Buffer
		std::array<Vertex, 200> vertices;
		Vertex* buffer = vertices.data();
		for (int y = 0; y < 5; y++) {
			for (int x = -3; x < 2; x++) {
				buffer = CreateQuad(buffer, glm::vec3(x, y, -3),(x + y) % 2);
				m_IndexBuffer->AddCount(6);
			}
		}

		buffer = CreateQuad(buffer, m_TranslationA, 0.0f);
		buffer = CreateQuad(buffer, m_TranslationB, 1.0f);
		m_IndexBuffer->AddCount(12);

		
		m_VertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation0);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);

		m_IndexBuffer->ReloadBufferDynamic();
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