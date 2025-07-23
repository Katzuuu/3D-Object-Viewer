#include "Texture.h"

Texture::Texture(): textureID(0), uniformTexture(0), width(0), height(0), bitDepth(0) {}

void Texture::createTexture(const std::string &pathname) {
    if (pathname.empty())
        throw std::invalid_argument("Texture pathname cannot be empty");

    unsigned char *imgData = stbi_load(pathname.c_str(), &width, &height, &bitDepth, 0);
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
}

GLuint Texture::GetTextureID() const {
    return uniformTexture;
}


Texture::~Texture() {
    clearTexture();
}

