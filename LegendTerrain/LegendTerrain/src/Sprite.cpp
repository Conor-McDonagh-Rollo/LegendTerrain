#include "../include/Sprite.h"

Sprite::Sprite(glm::vec3 pos, const char* tex_path)
{
	myShader = Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	texture = new Texture();
	texture->set(tex_path);

	float vertices[] = {
		// Positions
		 0.5f,  0.5f, 0.0f,     // Top right
		 0.5f, -0.5f, 0.0f,     // Bottom right
		-0.5f, -0.5f, 0.0f,     // Bottom left
		-0.5f,  0.5f, 0.0f      // Top left
	};
	m_vertices = vertices;

	float tec_coords[] = {
		// Texture Coordinates
		1.0f, 1.0f,     // Top right
		1.0f, 0.0f,     // Bottom right
		0.0f, 0.0f,     // Bottom left
		0.0f, 1.0f      // Top left
	};

	// Indices for the square
	unsigned int indices[] = {
		0, 1, 3,   // First triangle
		1, 2, 3    // Second triangle
	};

	generate(VAO, VBO, EBO, VBO_Tex,
		sizeof(vertices), vertices, sizeof(tec_coords), tec_coords,
		sizeof(indices), indices, 6, 4);

	move(pos.x, pos.y, pos.z);
}
