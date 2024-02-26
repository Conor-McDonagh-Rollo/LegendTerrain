#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();

    void SetUniform(const std::string& name, int value) {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    }

    void SetUniform(const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }

    void SetUniform(const std::string& name, const glm::vec3& value) {
        glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
    }

    void SetUniform(const std::string& name, const glm::mat4& value) {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    GLuint GetProgramID() const;

private:
    GLuint programID;

    GLuint LoadShader(GLenum type, const std::string& path);
};

