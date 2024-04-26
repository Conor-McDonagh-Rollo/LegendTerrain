#ifndef TEXTURED_OBJECT_H
#define TEXTURED_OBJECT_H

#include <glm/glm/glm.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include <vector>
#include "GameObject.h"
#include "Shader.h"
#include "Texture.h"

class Textured_Object : public GameObject
{
public:
	Textured_Object() { };

	void generate(GLuint& _VAO,
				  GLuint& _VBO,
				  GLuint& _EBO,
				  GLuint& _VBO_Tex,
				  size_t _verticiesSize,
				  float* _verticies,
				  size_t _tec_coordsSize,
				  float* _tec_coords,
				  size_t _indicesSize,
				  unsigned int* _indices,
				  int amountOfIndicies,
				  int numOfVert);

	void render() override;
	void move(float x = 0.f, float y = 0.f, float z = 0.f)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}
	void rotate(float angleDeltaX = 0.0f,
				float angleDeltaY = 0.0f, 
				float angleDeltaZ = 0.0f)
	{
		rotationAngle.x += angleDeltaX;
		rotationAngle.y += angleDeltaY;
		rotationAngle.z += angleDeltaZ;

		// Normalize the angles to [0, 360)
		while (rotationAngle.x >= 360.0f) rotationAngle.x -= 360.0f;
		while (rotationAngle.y >= 360.0f) rotationAngle.y -= 360.0f;
		while (rotationAngle.z >= 360.0f) rotationAngle.z -= 360.0f;

		while (rotationAngle.x < 0.0f) rotationAngle.x += 360.0f;
		while (rotationAngle.y < 0.0f) rotationAngle.y += 360.0f;
		while (rotationAngle.z < 0.0f) rotationAngle.z += 360.0f;
	}

	void rebindVBO()
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexCount, m_vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void setShader(Shader& shader)
	{
		currentShader = &shader;
	}

protected:

	glm::vec3 rotationAngle = { 0,0,0 };

	void updateModelMatrix()
	{
		model = glm::mat4(1.0f); // Start with an identity matrix
		glm::vec3 newPosition = glm::vec3(position.x, position.y, position.z); // New position
		model = glm::translate(model, newPosition);

		// Rotation around the X, Y, and Z axes
		//model = glm::rotate(model, glm::radians(rotationAngle.x), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotationAngle.y), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotationAngle.z), glm::vec3(0.0f, 0.0f, 1.0f));

		currentShader->setMat4("model", model);
	}

	GLuint VAO = 0, VBO = 0, EBO = 0, VBO_Tex = 0;
	Texture* texture = nullptr;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);

	float* m_vertices = nullptr;
	float* m_texCoords = nullptr;
	unsigned int* m_indices = nullptr;
	GLuint index = 0;
	int indexCount = 6;
	int vertexCount = 4;
	int texCoordCount = 0;

	Shader* currentShader = nullptr;

};

#endif