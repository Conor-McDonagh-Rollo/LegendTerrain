#include "../include/Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderPath);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Check for linking errors

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

GLuint Shader::GetProgramID() const {
    return programID;
}

GLuint Shader::LoadShader(GLenum type, const std::string& path) {
    std::ifstream shaderFile(path);
    if (!shaderFile.is_open()) {
        // Handle shader loading error
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    std::string shaderCode = shaderStream.str();
    const char* shaderSource = shaderCode.c_str();

    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);

    // Check for compilation errors

    return shaderID;
}
