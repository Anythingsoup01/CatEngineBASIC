#include "TestTexture2D.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ImGui/imgui.h>

namespace test {
	TestTexture2D::TestTexture2D()
        : m_TranslationA(0, 0,0), m_TranslationB(0, 0, 0), m_Proj(glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
	{


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
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO = std::make_unique<VertexArray>();
        m_VAO->AddBuffer(vb, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(unsigned int) * 6);
        m_IndexBuffer->Bind();

        m_Shader = std::make_unique<Shader>("res/shaders/None.catshader");

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 1.0, 1.0, 1.0, 1.0);

        m_Texture = std::make_unique<Texture>("res/textures/Pig.png");
        m_Shader->SetUniform1i("u_Texture", 0);

        m_Shader->Unbind();
        m_VAO->Unbind();
        m_IndexBuffer->Unbind();
	}
	TestTexture2D::~TestTexture2D()
	{
        
	}
	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        glm::vec3 color = glm::vec3(1.0f);

        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Shader->SetUniform4f("u_Color", color.r, color.g, color.b, 1.0);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Shader->SetUniform4f("u_Color", color.r, color.g, color.b, 1.0);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
	}
	void TestTexture2D::OnImGuiRender()
	{
        ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, -200.0f, 200.0f);
        ImGui::SliderFloat3("TranslationB", & m_TranslationB.x, -200.0f, 200.0f);

	}
}