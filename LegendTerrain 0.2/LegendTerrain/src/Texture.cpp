#include "../include/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"

void Texture::Set(const std::string& imagePath) {

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // Flip the texture vertically when loading
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = GL_RGBA;
        if (nrChannels == 3) format = GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        // Handle texture loading error
    }

    stbi_image_free(data);

    Bind();
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, textureID);
}