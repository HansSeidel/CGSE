#pragma once

#include "Test.h"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>
namespace test {

	class TestTextureBatch : public Test {
	public:
		TestTextureBatch();
		~TestTextureBatch();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		//H-IAMGUI TODO: Delete later if possible ################## 
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture1;
		std::unique_ptr<Texture> m_Texture2;

		glm::vec3 m_TranslationA;
		glm::mat4 m_Proj, m_View;

	};
}