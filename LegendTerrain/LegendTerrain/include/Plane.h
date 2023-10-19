#ifndef PLANE_H
#define PLANE_H

#include <glm/glm/glm.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"

class Plane
{
public:
	Plane(Position pos = {0,0,0}, const char* tex_path = "assets/defaults/default_texture.jpg");

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

private:

	float rotationAngle = 0.0f; // Initialized to no rotation

	void updateModelMatrix()
	{
		model = glm::mat4(1.0f); // Start with an identity matrix
		glm::vec3 newPosition = glm::vec3(position.x, position.y, position.z); // New position
		model = glm::translate(model, newPosition);

		// Add this line to incorporate rotation around the Y-axis
		model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		myShader.setMat4("model", model);
	}

	GLuint VAO, VBO, EBO, VBO_Tex;
	Texture* texture = nullptr;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);

	float* m_vertices = nullptr;
	GLuint index;

	Shader myShader;
};

#endif