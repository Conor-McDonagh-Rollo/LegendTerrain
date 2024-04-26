#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

class Texture
{
public:
	Texture() {} // Can initialize it without actually setting it
	Texture* set(std::string name, const char* path); // Load from file and generate the texture
	void bind() {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	inline unsigned int getTextureID() { return texture; }

	static std::map<std::string, Texture*> textureMap;

private:
	GLuint texture = NULL;
};

#endif