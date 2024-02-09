#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture {
public:
    Texture() {};
    ~Texture();

    void Set(const std::string& imagePath);
    void Bind() const;

private:
    GLuint textureID = NULL;
};

