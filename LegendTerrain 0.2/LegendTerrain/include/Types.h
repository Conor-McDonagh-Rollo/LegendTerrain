#pragma once
#include <glm/glm/glm.hpp>

struct Vertex {
    Vertex(float _x, float _y, float _z)
    {
        position.x = _x;
        position.y = _y;
        position.z = _z;
    }
    glm::vec3 position;
    glm::vec2 texCoord;
};