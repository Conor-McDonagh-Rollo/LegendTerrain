#pragma once

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <vector>
#include <memory>
#include "Shader.h"
#include "Texture.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
    // Add other vertex attributes as needed
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void SetTexture(std::shared_ptr<Texture> texture);
    void SetShader(std::shared_ptr<Shader> shader);

    void Draw();

private:
    GLuint VAO, VBO, EBO;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Shader> shader;
    GLsizei vertexCount, indexCount;
};

