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

//H-IAMGUI TODO: Delete later if possible ################## 
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
//H-IAMGUI TODO: Delete later if possible ################## 
//H-Tests: #################################################
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestColorBatch.h"
#include "tests/TestTextureBatch.h"
//H-Tests: #################################################

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
        
        // Allow Blending (Blending includes transparency)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Renderer renderer;

        //H-IAMGUI TODO: Delete later if possible ################## 
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
        //H-IAMGUI TODO: Delete later if possible ################## 

        //H-Tests: #################################################
        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexure2D>("Texture Move");
        testMenu->RegisterTest<test::TestColorBatch>("BatchRendering Colors");
        testMenu->RegisterTest<test::TestTextureBatch>("Batch Rendering Texture");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();


            //H-IAMGUI TODO: Delete later if possible ################## 
            ImGui_ImplGlfwGL3_NewFrame();
            //H-Tests: #################################################
            if (currentTest) {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if(currentTest != testMenu && ImGui::Button("<-")) {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }
            //H-Tests: #################################################
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            //H-IAMGUI TODO: Delete later if possible ################## 

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    delete currentTest;
    if (currentTest != testMenu)
        delete testMenu;
    }

    //H-IAMGUI TODO: Delete later if possible ################## 
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext(); 
    //H-IAMGUI TODO: Delete later if possible ################## 
    glfwTerminate();
    return 0;
}