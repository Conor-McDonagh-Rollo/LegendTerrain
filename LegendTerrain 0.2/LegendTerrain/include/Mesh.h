
#pragma once

#include <vector>
#include <memory>
#include "Shader.h"
#include "Texture.h"
#include "Types.h"
#include <glm/glm/gtc/matrix_transform.hpp>

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void SetPosition(const glm::vec3& _position);
    void SetRotation(const glm::vec3& _rotation); 
    void SetScale(const glm::vec3& _scale);

    void SetTexture(std::shared_ptr<Texture> texture);
    void SetShader(std::shared_ptr<Shader> shader);

    void Draw();

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transformationMatrix;

    GLuint VAO = 0, VBO = 0, EBO = 0;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Shader> shader;
    GLsizei vertexCount, indexCount;

    void UpdateTransformationMatrix() {
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0));
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0));
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0, 1));
        glm::mat4 rot = rotX * rotY * rotZ;
        glm::mat4 scl = glm::scale(glm::mat4(1.0f), scale);

        transformationMatrix = trans * rot * scl;
    }
};

