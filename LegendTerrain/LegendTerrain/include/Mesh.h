#ifndef MESH_H
#define MESH_H
/*
#include "Object.h"
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

struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
};

class Mesh : public Object {
public:
	Mesh(const char* path);
    void draw() override;

private:
    Assimp::Importer importer;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

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

    void processMesh(aiMesh* mesh, const aiScene* scene)
    {
        // Temporary containers for the data
        std::vector<Vertex> tempVertices;
        std::vector<unsigned int> tempIndices;
        std::vector<Texture> tempTextures;

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
    }
};
*/
#endif