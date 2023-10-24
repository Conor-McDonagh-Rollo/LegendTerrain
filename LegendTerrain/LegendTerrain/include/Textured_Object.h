#ifndef TEXTURED_OBJECT_H
#define TEXTURED_OBJECT_H

#include <glm/glm/glm.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"

class Textured_Object 
{
public:
	Textured_Object() {};

	void generate(GLuint& _VAO,
				  GLuint& _VBO,
				  GLuint& _EBO,
				  GLuint& _VBO_Tex,
				  size_t _verticiesSize,
				  float* _verticies,
				  size_t _tec_coordsSize,
				  float* _tec_coords,
				  size_t _indicesSize,
				  unsigned int* _indices);

	void draw();
	void move(float x = 0.f, float y = 0.f, float z = 0.f)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}
	void rotate(float angleDelta)
	{
		rotationAngle += angleDelta;
		while (rotationAngle >= 360.0f) rotationAngle -= 360.0f; // Normalize to [0, 360)
		while (rotationAngle < 0.0f) rotationAngle += 360.0f;
	}

protected:

	float rotationAngle = 0.0f; // Initialized to no rotation

	void updateModelMatrix()
	{
		model = glm::mat4(1.0f); // Start with an identity matrix
		glm::vec3 newPosition = glm::vec3(position.x, position.y, position.z); // New position
		model = glm::translate(model, newPosition);

		// Rotation around the Y-Axis (temporary)
		model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		myShader.setMat4("model", model);
	}

	GLuint VAO = 0, VBO = 0, EBO = 0, VBO_Tex = 0;
	Texture* texture = nullptr;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);

	float* m_vertices = nullptr;
	GLuint index = 0;

	Shader myShader;

};

#endif