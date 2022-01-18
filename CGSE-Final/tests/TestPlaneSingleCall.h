#pragma once

#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "primitves/Plane.h"

#include <memory>
namespace test {

	class TestPlaneSingleCall : public Test {
	public:
		TestPlaneSingleCall();
		~TestPlaneSingleCall();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		//H-IAMGUI TODO: Delete later if possible ################## 
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_Va;
		std::unique_ptr<IndexBuffer> m_Ib;
		std::unique_ptr<VertexBuffer> m_Vb;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<extension::primitves::Plane> m_Plane;


		glm::vec3 m_ViewTranslation;
		glm::mat4 m_Proj;
		

	};
}