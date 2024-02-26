#include "../include/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : vertexCount(vertices.size()), indexCount(indices.size()), texture(nullptr), shader(nullptr) {
    // Generate and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind the Vertex Buffer Object (VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Generate and bind the Element Buffer Object (EBO)
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set up the vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    // Unbind VAO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::SetPosition(const glm::vec3& _position)
{
    position = _position;
    UpdateTransformationMatrix();
}

void Mesh::SetRotation(const glm::vec3& _rotation)
{
    rotation = _rotation;
    UpdateTransformationMatrix();
}

void Mesh::SetScale(const glm::vec3& _scale)
{
    scale = _scale;
    UpdateTransformationMatrix();
}

void Mesh::SetTexture(std::shared_ptr<Texture> texture) {
    this->texture = texture;
}

void Mesh::SetShader(std::shared_ptr<Shader> shader) {
    this->shader = shader;
}

void Mesh::Draw() {
    if (!shader || !texture) {
        // Shader or texture not set, handle the error
        return;
    }

    glUseProgram(shader->GetProgramID());

    shader->SetUniform("model", transformationMatrix);

    texture->Bind(); // Assuming you have a Bind method in the Texture class

    // Draw the mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
