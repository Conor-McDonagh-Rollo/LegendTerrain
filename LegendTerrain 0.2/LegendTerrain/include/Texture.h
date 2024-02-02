#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture {
public:
    Texture(const std::string& imagePath);
    ~Texture();

    void Bind() const;

private:
    GLuint textureID;
};

