#pragma once
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct ShaderSource {
    std::string VertexSource;
    std::string FragmentSource;
};


class Shader
{
private:
    std::string m_Filepath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformCacheLocation;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms

    /* Float Uniforms*/
    void SetUniform1f(const std::string& name, float v0);
    void SetUniform2f(const std::string& name, float v0, float v1);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    void SetUniform4v(const std::string& name, glm::mat4 color);
    
    /* Int Uniforms*/
    void SetUniform1i(const std::string& name, int v0);
    void SetUniform2i(const std::string& name, int v0, int v1);
    void SetUniform3i(const std::string& name, int v0, int v1, int v2);
    void SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3);

    /* Matrix Uniforms*/
    void SetUniformMat2f(const std::string& name, glm::mat2& matrix);
    void SetUniformMat3f(const std::string& name, glm::mat3& matrix);
    void SetUniformMat4f(const std::string& name, glm::mat4& matrix);

private:
    ShaderSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    unsigned int GetUniformLocation(const std::string& name);

};

