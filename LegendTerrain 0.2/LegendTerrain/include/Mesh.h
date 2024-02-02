#pragma once

#include <vector>
#include <memory>
#include "Shader.h"
#include "Texture.h"
#include "Types.h"

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

