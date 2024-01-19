#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture
{
public:
	Texture() {} // Can initialize it without actually setting it
	void set(const char* path); // Load from file and generate the texture
	void bind() {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	inline unsigned int getTextureID() { return texture; }

private:
	GLuint texture = NULL;
};

#endif