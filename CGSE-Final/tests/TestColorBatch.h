#pragma once

#include "Test.h"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <memory>

namespace test {

	class TestColorBatch : public Test {
	public:
		TestColorBatch();
		~TestColorBatch();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		//H-IAMGUI TODO: Delete later if possible ################## 
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;

		glm::vec3 m_TranslationA;
		glm::mat4 m_Proj, m_View;

	};
}