#ifndef MESH_H
#define MESH_H
/*
#include "Textured_Object.h"
#include <glm/glm/glm.hpp>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    glm::vec3 Position;  // Position
    glm::vec3 Normal;    // Normal
    glm::vec2 TexCoords; // Texture Coordinates
};

struct _Texture {
    unsigned int id;
    std::string type;
    aiString path;
};

class Mesh : public Textured_Object {
public:
    Mesh(const char* path, glm::vec3 pos);
    void draw() override;

private:
    Assimp::Importer importer;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<_Texture> textures;

    void processNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < scene->mRootNode->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[scene->mRootNode->mMeshes[i]];
            processMesh(mesh, scene);
        }

        // Process children nodes
        for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; i++) {
            processNode(scene->mRootNode->mChildren[i], scene);
        }
    }

    void processMesh(aiMesh* mesh, const aiScene* scene);
};
*/
#endif