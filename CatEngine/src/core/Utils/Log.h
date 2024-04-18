#pragma once

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;ASSERT(GLLog(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLog(const char* function, const char* file, int line);

class Log {
private:
	bool m_SingleUse;
	bool m_IsCalled;
public:
	static void LogString(const char* str0);
	static void LogFloat1(const char* des0, const float v0);
	static void LogFloat2(const char* des0, const float v0, const char* des1, const float v1);


};