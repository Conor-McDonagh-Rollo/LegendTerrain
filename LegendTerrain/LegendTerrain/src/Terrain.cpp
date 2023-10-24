#include "../include/Terrain.h"

Terrain::Terrain(glm::vec3 pos, int detail)
{
    myShader = Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
    texture = new Texture();
    texture->set("assets/defaults/default_texture.jpg");

    int numVertices = (detail + 1) * (detail + 1);
    float* vertices = new float[numVertices * 3]; // 3 coordinates per vertex (x, y, z)
    float* texCoords = new float[numVertices * 2]; // 2 coordinates per vertex (u, v)

    // Calculate spacing between vertices
    float spacing = 1.0f / static_cast<float>(detail);

    int numIndices = detail * detail * 6;
    unsigned int* indices = new unsigned int[numIndices];

    int vertexIndex = 0;
    int texCoordIndex = 0;
    int index = 0;
    for (int i = 0; i <= detail; i++)
    {
        for (int j = 0; j <= detail; j++)
        {
            // Calculate the position of each vertex
            float x = static_cast<float>(j) * spacing - 0.5f;
            float z = static_cast<float>(i) * spacing - 0.5f;
            float y = 1;

            // Store the vertex coordinates
            vertices[vertexIndex++] = x;
            vertices[vertexIndex++] = y;
            vertices[vertexIndex++] = z;

            // Calculate the texture coordinates for each vertex
            float u = static_cast<float>(j) / detail;
            float v = static_cast<float>(i) / detail;

            texCoords[texCoordIndex++] = u;
            texCoords[texCoordIndex++] = v;

            // Generate indices if within bounds
            if (i < detail && j < detail)
            {
                int topLeft = i * (detail + 1) + j;
                int topRight = topLeft + 1;
                int bottomLeft = (i + 1) * (detail + 1) + j;
                int bottomRight = bottomLeft + 1;

                indices[index++] = topLeft;
                indices[index++] = bottomLeft;
                indices[index++] = topRight;

                indices[index++] = topRight;
                indices[index++] = bottomLeft;
                indices[index++] = bottomRight;
            }
        }
    }

    m_vertices = vertices;

    size_t verticesSize = numVertices * 3 * sizeof(float);
    size_t texCoordsSize = numVertices * 2 * sizeof(float);
    size_t indicesSize = numIndices * sizeof(unsigned int);

    generate(VAO, VBO, EBO, VBO_Tex,
        verticesSize, vertices, texCoordsSize, texCoords,
        indicesSize, indices);

    move(pos.x, pos.y, pos.z);
}
