
#include<glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Buffers/VertexArray.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/VertexBufferLayout.h"
#include "Buffers/IndexBuffer.h"
#include "Shader/Shader.h"
#include "Textures/Texture.h"
#include "Utils/Log.h"
#include "Renderer/Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

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
    window = glfwCreateWindow(640, 480, "Pig!", NULL, NULL);
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


    float positions[]{
        -50.0f, -50.0f, 0.0f, 0.0f, // 0
         50.0f, -50.0f, 1.0f, 0.0f, // 1
        -50.0f,  50.0f, 0.0f, 1.0f, // 2
         50.0f,  50.0f, 1.0f, 1.0f  // 3
    };

    unsigned int indices[]{
        0, 1, 2,
        1, 3, 2
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, sizeof(unsigned int) * 6);
    ib.Bind();

    glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 translationA = glm::vec3(0, 0, 0);
    glm::vec3 translationB = glm::vec3(0, 0, 0);

    Shader shader("res/shaders/None.catshader");
    shader.Bind();
    glm::vec3 color = glm::vec3(1.0f);
    shader.SetUniform4f("u_Color", color.r, color.g, color.b, 1.0);
    
    

    Texture texture("res/textures/Pig.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    shader.Unbind();
    vb.Unbind();
    ib.Unbind();
    /* Loop until the user closes the window */
     Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
   
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* Render here */
        renderer.Clear();








        ImGui::Begin("First Pig");
        ImGui::Text("Move the First Pig!");
        ImGui::SliderFloat3("Translation A", &translationA.x, 0, 480);
        ImGui::ColorEdit3("Color", &color.r);
        ImGui::End();

        ImGui::Begin("Second Pig");
        ImGui::Text("Move the Second Pig!");
        ImGui::SliderFloat3("Translation B", &translationB.x, 0, 480);
        ImGui::ColorEdit3("Color", &color.r);
        ImGui::End();

        

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = proj * view * model;
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            shader.SetUniform4f("u_Color", color.r, color.g, color.b, 1.0);
            renderer.Draw(va, ib, shader);
        }
        
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvp = proj * view * model;
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            shader.SetUniform4f("u_Color", color.r, color.g, color.b, 1.0);
            renderer.Draw(va, ib, shader);
        }
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}