#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();

    GLuint GetProgramID() const;

private:
    GLuint programID;

    GLuint LoadShader(GLenum type, const std::string& path);
};

