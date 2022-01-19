#pragma once

#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "primitves/Cube.h"
#include "Texture.h"

#include <memory>
namespace test {

	class TestCubeSingleCall : public Test {
	public:
		TestCubeSingleCall();
		~TestCubeSingleCall();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		//H-IAMGUI TODO: Delete later if possible ################## 
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<extension::primitves::Cube> m_Cube;
		std::unique_ptr<Texture> m_Texture1;
		std::unique_ptr<Texture> m_Texture2;


		glm::vec3 m_ViewTranslation;
		glm::mat4 m_Proj;


	};
}