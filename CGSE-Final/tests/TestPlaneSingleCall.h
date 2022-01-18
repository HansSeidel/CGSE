#pragma once

#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "primitves/Plane.h"
#include "Texture.h"

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
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<extension::primitves::Plane> m_Plane;
		std::unique_ptr<Texture> m_Texture;


		glm::vec3 m_ViewTranslation;
		glm::mat4 m_Proj;
		

	};
}