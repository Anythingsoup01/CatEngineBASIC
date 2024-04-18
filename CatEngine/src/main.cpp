
#include<glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "test/TestTexture2D.h"
#include "test/TestClearColor.h"
#include "test/test.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(400, 400, "Pig!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL();

    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Loop until the user closes the window */

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;
   

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
    

    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */



        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("FPS");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        if (currentTest) {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-")) {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        /* Render here */
      

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}