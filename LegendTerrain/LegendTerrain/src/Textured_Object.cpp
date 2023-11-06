#include "../include/Textured_Object.h"

void Textured_Object::generate(GLuint& _VAO, 
							   GLuint& _VBO,
							   GLuint& _EBO,
							   GLuint& _VBO_Tex,
							   size_t _verticiesSize,
							   float*  _vertices,
							   size_t _tec_coordsSize,
							   float*  _tec_coords,
							   size_t _indicesSize,
							   unsigned int*  _indices,
							   int amountOfIndicies,
							   int numOfVert)
{
	
	// Generate and bind the VAO
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// Generate, bind, and set buffer data for the vertex positions
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _verticiesSize, _vertices, GL_STATIC_DRAW);

	// Define the layout of the vertex data
	glEnableVertexAttribArray(0); // position attribute at location 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Generate, bind, and set buffer data for the texture coordinates
	glGenBuffers(1, &_VBO_Tex);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Tex);
	glBufferData(GL_ARRAY_BUFFER, _tec_coordsSize, _tec_coords, GL_STATIC_DRAW);

	// Define the layout of the texture coordinate data
	glEnableVertexAttribArray(1); // texture coordinate attribute at location 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// Generate, bind, and set buffer data for the indices
	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize, _indices, GL_STATIC_DRAW);

	// Unbind the VAO to prevent further modification.
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	indexCount = amountOfIndicies;
	vertexCount = numOfVert;
}

void Textured_Object::draw()
{
	updateModelMatrix();

	// Set Model Matrix as a uniform in the shader
	myShader.use();
	myShader.setMat4("model", model);

	// Temporary: Set the View and Projection matrices
	glm::mat4 view = glm::lookAt(
		// Camera position in World Space
		glm::vec3(0, 4, 1),
		// and looks at the origin
		glm::vec3(0, 0, 0),
		// Head is up (set to 0,-1,0 to look upside-down)
		glm::vec3(0, 1, 0)
	);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // 45-degree FOV, 4:3 aspect ratio, near clip 0.1, far clip 100
	myShader.setMat4("view", view);
	myShader.setMat4("projection", projection);

	

	GLint modelLoc = glGetUniformLocation(myShader.ID, "model");

	// Bind and Draw as usual
	texture->bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
