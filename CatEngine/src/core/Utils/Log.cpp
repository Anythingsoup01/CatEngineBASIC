#include "Log.h"

#include <glad/glad.h>

#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLog(const char* function, const char* file, int line) 
{
    if (GLenum error = glGetError()) {
        if (GLenum error = GL_INVALID_ENUM) {
            std::cout << "[OpenGL Error] (Invalid Enum): " << function << " " << file << " (" << line << ")" << std::endl;
            return false;
        }
        else if (GLenum error = GL_INVALID_VALUE) {
            std::cout << "[OpenGL Error] (Invalid Value): " << function << " " << file << " (" << line << ")" << std::endl;
            return false;
        }
        else if (GLenum error = GL_INVALID_OPERATION) {
            std::cout << "[OpenGL Error] (Invalid Operation): " << function << " " << file << " (" << line << ")" << std::endl;
            return false;
        }
        else if (GLenum error = GL_STACK_OVERFLOW) {
            std::cout << "[OpenGL Error] (Stack Overflow): " << function << " " << file << " (" << line << ")" << std::endl;
            return false;
        }
        else if (GLenum error = GL_INVALID_FRAMEBUFFER_OPERATION) {
            std::cout << "[OpenGL Error] (Invalid Framebuffer Operation): " << function << " " << file << " (" << line << ")" << std::endl;
            return false;
        }
        else if (GLenum error = GL_CONTEXT_LOST) {
            std::cout << "[OpenGL Error] (Context Lost): " << function << " " << file << " (" << line << ")" << std::endl;
            return false;
        }
    }
    return true;
}


void Log::LogString(const char* str0)
{    
        std::cout << str0 << std::endl;
}

void Log::LogFloat1(const char* des0, const float v0)
{
    std::cout << des0 << v0 << std::endl;
}

void Log::LogFloat2(const char* des0, const float v0, const char* des1, const float v1)
{
    std::cout << des0 << v0 << ", " << des1 << v1 << std::endl;
}