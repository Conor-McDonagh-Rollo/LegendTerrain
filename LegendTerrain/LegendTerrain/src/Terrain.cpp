#include "../include/Terrain.h"

Terrain::Terrain(glm::vec3 pos, int detail)
{
    texture = new Texture();
    texture->set("assets/defaults/default_texture2.jpg");

    int numVertices = (detail + 1) * (detail + 1);
    float* vertices = new float[numVertices * 3]; // 3 coordinates per vertex (x, y, z)
    float* texCoords = new float[numVertices * 2]; // 2 coordinates per vertex (u, v)
    int numOfVert = numVertices * 3;

    // Calculate spacing between vertices
    float spacing = 1.0f / static_cast<float>(detail);

    int numIndices = detail * detail * 6;
    unsigned int* indices = new unsigned int[numIndices];

    int vertexIndex = 0;
    int texCoordIndex = 0;
    int _index = 0;
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

                indices[_index++] = topLeft;
                indices[_index++] = bottomLeft;
                indices[_index++] = topRight;
                        
                indices[_index++] = topRight;
                indices[_index++] = bottomLeft;
                indices[_index++] = bottomRight;
            }
        }
    }

    m_vertices = vertices;
    m_texCoords = texCoords;
    indexCount = _index;

    size_t verticesSize = numVertices * 3 * sizeof(float);
    size_t texCoordsSize = numVertices * 2 * sizeof(float);
    size_t indicesSize = numIndices * sizeof(unsigned int);

    generate(VAO, VBO, EBO, VBO_Tex,
        verticesSize, vertices, texCoordsSize, texCoords,
        indicesSize, indices, _index + 1, numOfVert);

    DisplaceVerticies();
    move(pos.x, pos.y, pos.z);
}

void Terrain::DisplaceVerticies()
{

    // Start at Y Coordinate and add 3 every time to keep within Y
    for (int i = 1; i < vertexCount; i += 3)
    {
        float y = perlin.noise2D(m_vertices[i - 2], m_vertices[i - 1]);
        m_vertices[i] = y;
    }

    rebindVBO();
}
