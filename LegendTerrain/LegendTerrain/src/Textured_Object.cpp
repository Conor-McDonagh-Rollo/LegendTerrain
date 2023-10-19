#include "../include/Textured_Object.h"

void Textured_Object::generate(GLuint& _VAO, 
							   GLuint& _VBO,
							   GLuint& _EBO,
							   GLuint& _VBO_Tex,
							   float*  _vertices,
							   float*  _tec_coords,
							   float*  _indices)
{
	

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &_VBO_Tex);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Tex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_tec_coords), _tec_coords, GL_STATIC_DRAW);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // position attribute
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1); // texture coordinate attribute
	glBindBuffer(GL_ARRAY_BUFFER, _VBO_Tex);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindVertexArray(0);

}

void Textured_Object::draw()
{
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
