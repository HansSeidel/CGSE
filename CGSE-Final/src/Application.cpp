#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f
        };

        //H-Create an index-Buffer
        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };


        //H-Outsourced the VertexBuffer and call it here
        VertexBuffer vb(triangle, 4 * 2 * sizeof(float));

        //H-Outsourced Vertex Array Objext
        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        

        IndexBuffer ibo(indices, 6);


        /* H-Reading in shaders */
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.setUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);

        float c_r = 0.0f;
        float increment = 0.05f;

        //Clearing all Buffers before starting with render loop.
        va.UnBind();
        shader.UnBind();
        vb.UnBind();
        ibo.UnBind();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            //H-Use defined shaders
            shader.Bind();
            shader.setUniform4f("u_Color", c_r, 0.3f, 0.8f, 1.0f);

            //H-Buffer should be binded bevore each Drawcall because they could change or be unbinded.
            //In this case they have been cleared before entering the render loop.
            //Because the Vertex Array Object is connected with the GL_ARRAY_BUFFER, we do not need to bind the GL_ARRAY_BUFFER again.
            ibo.Bind();
            va.Bind();

            /*H-Draw the vertex buffer*/
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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