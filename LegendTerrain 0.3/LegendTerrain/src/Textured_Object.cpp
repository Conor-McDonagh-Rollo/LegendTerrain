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
	vertexCount = _verticiesSize;
}

void Textured_Object::render()
{
	// Set Model Matrix as a uniform in the shader
	currentShader->use();

	updateModelMatrix();
	//GLint modelLoc = glGetUniformLocation(currentShader->ID, "model");

	// Bind and Draw as usual
	texture->bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
