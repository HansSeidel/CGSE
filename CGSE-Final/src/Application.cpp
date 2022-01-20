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
#include "BatchGroup.h"
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//camera
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
glm::vec3 v_MouseFront;

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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    /* H - Initialize glew Init*/
    glewInit();
    /* H - Initialize PlayerController.Shell only be instanced once. */
    extension::PlayerController playerController = extension::PlayerController();
    /* H - Setting up projection martix */
    glm::mat4 m_Proj(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));
    
    // Allow Blending (Blending includes transparency)
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //SetBackgroundColor
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    //Initialising renderer
    Renderer renderer;

    //Drawing primitives
    float vertices[] = {
        -0.5f,-0.5f,-1.0f,
        0.5f,-0.5f,-1.0f,
        0.0f,0.5f,1.0f
    };
    unsigned int indicies[] = {
        0,1,2
    };

    //Initialising and setting up the Buffers
    VertexBuffer m_VBO(vertices,sizeof(vertices));
    VertexArray m_VAO = VertexArray();
    VertexBufferLayout layout;
    layout.Push<float>(3);
    //layout.Push<float>(2);
    //layout.Push<float>(4);
    //layout.Push<float>(1);
    m_VAO.AddBuffer(m_VBO, layout);

    //Initialising IndexBuffer
    IndexBuffer m_IBO(indicies, 3);

    //Initialising shader
    Shader m_Shader("res/shaders/Basic.shader");
    m_Shader.Bind();

    //Creating Textures
    Texture base("");

    Texture m_Texture2("res/textures/light_fine_wood_pbr_18_13_diffuse.jpg");

    int sampler[8];
    for (int i = 0; i < 8; i++)
        sampler[i] = i;
    m_Shader.setUniform1iv("u_TextureArr", 8, sampler);




    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        base.Bind();
        m_Texture2.Bind(1);

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //View matrix
        playerController.ProcessInput(window,deltaTime);
        glm::mat4 m_View = playerController.GetView();
        playerController.UpdateFront(glm::normalize(v_MouseFront));

        //ModelTranslation
        glm::mat4 m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        
        {
            m_Shader.Bind();
            m_Shader.setUniformMat4f("u_Model", m_Model);
            m_Shader.setUniformMat4f("u_View", m_View);
            m_Shader.setUniformMat4f("u_Projection", m_Proj);
            m_VBO.Bind();
            m_IBO.Bind();
            renderer.Draw(m_VAO, m_IBO, m_Shader);
            m_Shader.UnBind();
            m_VAO.UnBind();
            m_IBO.UnBind();
            m_VBO.UnBind();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    v_MouseFront = front;
}