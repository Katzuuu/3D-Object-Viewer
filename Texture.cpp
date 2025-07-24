#include "Texture.h"

#include <utility>

Texture::Texture(std::string  fileName) : filename(std::move(fileName)){};

void Texture::loadTexture() {
    if (filename.empty())
        throw std::invalid_argument("Texture filename cannot be empty");

    unsigned char *imgData = stbi_load(filename.c_str(), &width, &height, &bitDepth, 0);
    if (imgData == nullptr)
        throw std::runtime_error("Failed to load image");

    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    uniformTexture = glGetUniformLocation(textureID, "texture");

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(imgData);
}

void Texture::useTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::clearTexture() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
    uniformTexture = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    filename = "";
}

GLuint Texture::GetTextureID() const {
    return uniformTexture;
}


Texture::~Texture() {
    clearTexture();
}

