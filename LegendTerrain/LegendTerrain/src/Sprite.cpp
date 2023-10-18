#include "../include/Sprite.h"

Sprite::Sprite(const char* tex_path)
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

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO_Tex);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Tex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tec_coords), tec_coords, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // position attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1); // texture coordinate attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Tex);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void Sprite::draw() {
	/*
	glBindVertexArray(VAO);

	myShader.use(); // useProgram
	texture->bind(); // bind the texture

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	*/

	// Calculate Model Matrix based on the updated position
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position); // assuming position is of type glm::vec3

	// Set Model Matrix as a uniform in the shader
	myShader.use();
	myShader.setMat4("model", model); // assuming you have a setMat4 function

	GLint modelLoc = glGetUniformLocation(myShader.ID, "model");
	std::cout << "Model uniform location: " << modelLoc << std::endl;

	// Bind and Draw as usual
	texture->bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
