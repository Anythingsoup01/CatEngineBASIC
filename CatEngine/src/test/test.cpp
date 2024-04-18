#include "test.h"
#include "ImGui/imgui.h"

#include "Utils/Log.h"
#include <glad/glad.h>
namespace test {
	TestMenu::TestMenu(Test*& currentTestPointer)
		:m_CurrentTest(currentTestPointer)
	{
	}
	void TestMenu::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests) 
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();

		}
	}
}