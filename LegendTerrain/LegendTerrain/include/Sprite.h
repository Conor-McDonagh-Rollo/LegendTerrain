#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm/glm.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"

struct Position
{
	float x, y, z;
};

class Sprite
{
public:
	Sprite(const char* tex_path);

	void draw();
	void move(float x = 0.f, float y = 0.f, float z = 0.f)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}

private:

	void updateModelMatrix()
	{
		glm::vec3 newPosition = glm::vec3(position.x, position.y, position.z); // New position
		model = glm::translate(model, newPosition);

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