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
		glm::mat4 GetView();
	};
}