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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(950, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    /* H-Initialize glew Init*/
    glewInit();

    std::cout << glGetString(GL_VERSION) << std::endl;

    //H-This scope prevents an error i do not understand completly. It should also terminate the program when closing the render window.
    {
        /* H-Create a VertexBuffer */
        //H-Create Data-Array for an triangle
        float triangle[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };

        //H-Create an index-Buffer
        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        // Allow Blending (Blending includes transparency)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //H-Outsourced the VertexBuffer and call it here
        VertexBuffer vb(triangle, 4 * 4 * sizeof(float));

        //H-Outsourced Vertex Array Objext
        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        

        IndexBuffer ibo(indices, 6);

        //Creating mvp
        glm::mat4 proj = glm::ortho(-2.0f,2.0f,-1.5f,1.0f,-1.0f,1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(2, 1, 0));

        glm::mat4 mvp = proj * view * model;

        /* H-Reading in shaders */
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.setUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);

        Texture texture("res/textures/brown_rock_19_78_diffuse.jpg");
        texture.Bind();
        shader.setUniform1i("u_Texture", 0);
        shader.setUniformMat4f("u_MVP", mvp);



        float c_r = 0.0f;
        float increment = 0.05f;

        //Clearing all Buffers before starting with render loop.
        va.UnBind();
        shader.UnBind();
        vb.UnBind();
        ibo.UnBind();

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            //H-Use defined shaders
            shader.Bind();
            shader.setUniform4f("u_Color", c_r, 0.3f, 0.8f, 1.0f);

            /*H-Draw the vertex buffer*/
            renderer.Draw(va,ibo,shader);
            

            if (c_r >= 1.0f) {
                increment = -0.05f;
            }
            else if (c_r <= 0.0f) {
                increment = 0.05f;
            }
            c_r += increment;
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}