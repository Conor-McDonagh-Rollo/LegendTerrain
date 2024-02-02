#include "../include/Mesh.h"
/*
Mesh::Mesh(const char* path, glm::vec3 pos)
{
    // Use Assimp to load the model
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        // Handle errors
        return;
    }

    processNode(scene->mRootNode, scene);

}

void Mesh::draw()
{
}

void Mesh::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // Temporary containers for the data
    std::vector<Vertex> tempVertices;
    std::vector<unsigned int> tempIndices;
    std::vector<_Texture> tempTextures;

    // Walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;

        // Positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        // Normals
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        // Texture Coordinates
        if (mesh->mTextureCoords[0]) { // Does the mesh contain texture coordinates?
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        tempVertices.push_back(vertex);
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            tempIndices.push_back(face.mIndices[j]);
    }

    //////////////////////////////////////////////////////////////
    ////////////// BAD CODE AHEAD ////////////////////////////////
    //////////////////////////////////////////////////////////////

    std::vector<float> flattenedVertices;
    flattenedVertices.reserve(tempVertices.size() * 8); // 3 for position, 3 for normal, 2 for texCoords

    for (const Vertex& vertex : tempVertices) {
        // Position
        flattenedVertices.push_back(vertex.Position.x);
        flattenedVertices.push_back(vertex.Position.y);
        flattenedVertices.push_back(vertex.Position.z);
        // Normal
        flattenedVertices.push_back(vertex.Normal.x);
        flattenedVertices.push_back(vertex.Normal.y);
        flattenedVertices.push_back(vertex.Normal.z);
        // Texture Coordinates
        flattenedVertices.push_back(vertex.TexCoords.x);
        flattenedVertices.push_back(vertex.TexCoords.y);
    }

    unsigned int* flattenedIndices = tempIndices.data();
    size_t indicesSize = tempIndices.size() * sizeof(unsigned int);

    // Call the generate function from Textured_Object
    generate(
        VAO,               // GLuint for Vertex Array Object
        VBO,               // GLuint for Vertex Buffer Object
        EBO,               // GLuint for Element Buffer Object
        VBO_Tex,           // GLuint for Texture Buffer Object (if used for texture data)
        flattenedVertices.size() * sizeof(float), // Size of vertex data
        flattenedVertices.data(),                // Pointer to vertex data
        0,                 // Size of texture data (0 if not using VBO for textures)
        nullptr,           // Pointer to texture data (nullptr if not using VBO for textures)
        indicesSize,       // Size of index data
        flattenedIndices,  // Pointer to index data
        tempIndices.size(),// Number of indices
        flattenedVertices.size() / 8 // Number of vertices (divide by number of elements per vertex)
    );
}
*/