#include "../include/Plane.h"

Plane::Plane(Position pos, const char* tex_path)
{
	myShader = Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
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

	move(pos.x, pos.y, pos.z);
}

void Plane::draw()
{
	// Calculate Model Matrix based on the updated position
	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, position); // assuming position is of type glm::vec3
	updateModelMatrix();

	// Set Model Matrix as a uniform in the shader
	myShader.use();
	myShader.setMat4("model", model);

	// Temporary: Set the View and Projection matrices
	glm::mat4 view = glm::mat4(1.0f); // Identity for now. Later, this will be based on camera position/orientation
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // 45-degree FOV, 4:3 aspect ratio, near clip 0.1, far clip 100
	myShader.setMat4("view", view);
	myShader.setMat4("projection", projection);

	GLint modelLoc = glGetUniformLocation(myShader.ID, "model");
	std::cout << "Model uniform location: " << modelLoc << std::endl;

	// Bind and Draw as usual
	texture->bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
