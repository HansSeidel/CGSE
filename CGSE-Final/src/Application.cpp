#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "primitves/Plane.h"
//H-PlayerController
#include "PlayerController.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Final Project", NULL, NULL);
    

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Setting up dynamic resizing */
    glfwSetFramebufferSizeCallback(window, extension::PlayerController::Framebuffer_size_callback);
    //H-Initialise PlayerController and assigne callback function
    //glfwSetKeyCallback(window, extension::PlayerController::KeyBoardCallBack);
    
    glfwSwapInterval(1);

    /* H-Initialize glew Init*/
    glewInit();

    //H- Initialize PlayerController. Shell only be instanced once.
    extension::PlayerController playerController = extension::PlayerController();
    //extension::PlayerController::SetPlayerController(playerController);

    std::cout << glGetString(GL_VERSION) << std::endl;
    glm::mat4 m_Proj(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));

    // Allow Blending (Blending includes transparency)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    Renderer renderer;

    glm::vec3 position = { 0.0,-2.0, 0.0 };
    extension::primitves::Plane m_Plane(position, 10.0f, 10.0f);

    Shader m_Shader("res/shaders/Basic.shader");
    m_Shader.Bind();
    m_Plane.SetPlaneColor({ 0.2f,0.2f,0.7f,1.0f });
    m_Plane.SetupSingleCall();

    Texture m_Texture1("");
    Texture m_Texture2("res/textures/light_fine_wood_pbr_18_13_diffuse.jpg");
    m_Texture1.Bind();
    m_Texture2.Bind(1);

    int sampler[8];
    for (int i = 0; i < 8; i++)
        sampler[i] = i;
    m_Shader.setUniform1iv("u_TextureArr", 8, sampler);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        playerController.ProcessInput(window,deltaTime);
        glm::mat4 view = playerController.GetView();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 mvp = m_Proj * view * model;
        m_Shader.Bind();
        m_Shader.setUniformMat4f("u_MVP", mvp);
        m_Plane.DrawSingleCall(renderer, m_Shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}