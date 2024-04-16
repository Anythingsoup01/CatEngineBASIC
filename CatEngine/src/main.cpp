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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwSwapInterval(1);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 720, "Pig!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    gladLoadGL();

    std::cout << glGetString(GL_VERSION) << std::endl;


    float positions[]{
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f, // 1
        -0.5f,  0.5f, 0.0f, 1.0f, // 2
         0.5f,  0.5f, 1.0f, 1.0f  // 3
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

    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 1.0f, - 1.0f);

    Shader shader("res/shaders/None.catshader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 1.0, 1.0, 1.0, 1.0);
    shader.SetUniformMat4f("u_MVP", proj);

    Texture texture("res/textures/Pig.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);



    shader.Unbind();
    vb.Unbind();
    ib.Unbind();
    /* Loop until the user closes the window */
    Renderer renderer;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        renderer.Draw(va, ib, shader);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}