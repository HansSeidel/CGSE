#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"



namespace extension {
	class PlayerController {
	public:
		PlayerController();
		~PlayerController();
		void ProcessInput(GLFWwindow* window, float deltaTaime);
		static void Framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void UpdateFront(glm::vec3 front);
		glm::mat4 GetView();

	private:
		glm::vec3 m_CameraFront;
		glm::vec3 m_CameraPos;
		glm::vec3 m_CameraUp;

	};
}