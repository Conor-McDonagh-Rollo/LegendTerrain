#include "../include/Plane.h"

Plane::Plane(glm::vec3 pos, const char* tex_path)
{
	texture = new Texture();
	texture->set(tex_path);

	float thickness = 0.1f; // define the thickness of the 3D plane
	float vertices[] = {
		// Front face
		 0.5f,  0.5f, thickness / 2,    // Top right
		 0.5f, -0.5f, thickness / 2,    // Bottom right
		-0.5f, -0.5f, thickness / 2,    // Bottom left
		-0.5f,  0.5f, thickness / 2,    // Top left

		// Back face
		 0.5f,  0.5f, -thickness / 2,   // Top right
		 0.5f, -0.5f, -thickness / 2,   // Bottom right
		-0.5f, -0.5f, -thickness / 2,   // Bottom left
		-0.5f,  0.5f, -thickness / 2    // Top left
	};
	m_vertices = vertices;

	float tec_coords[] = {
		// Texture Coordinates
		1.0f, 1.0f,     // Top right
		1.0f, 0.0f,     // Bottom right
		0.0f, 0.0f,     // Bottom left
		0.0f, 1.0f      // Top left
	};

	// Indices for the 3D plane
	unsigned int indices[] = {
		// Front face
		0, 1, 3,
		1, 2, 3,

		// Back face
		4, 5, 7,
		5, 6, 7,

		// Sides
		0, 1, 4,
		1, 4, 5,

		1, 2, 5,
		2, 5, 6,

		2, 3, 6,
		3, 6, 7,

		3, 0, 7,
		0, 4, 7
	};
	generate(VAO, VBO, EBO, VBO_Tex,
		sizeof(vertices), vertices, sizeof(tec_coords), tec_coords,
		sizeof(indices), indices, 6, 4);

	move(pos.x, pos.y, pos.z);
}
