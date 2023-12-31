#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm/ext/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Position
{
    float x, y, z;
};

class Shader
{
public:
    // the program ID
    unsigned int ID = NULL;
    // constructor reads and builds the shader
    Shader(const char* vertexPath = "assets/shaders/vertex.glsl", const char* fragmentPath = "assets/shaders/fragment.glsl");
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec4(const std::string& name, float v1, float v2, float v3, float v4) const;
    void setMat4(const std::string& name, glm::mat4 &model) const;
};

#endif
