#pragma once

#include <string>
#include <glad/glad.h>
#include "stb_image.h"
#include <stdexcept>

class Texture {
    GLuint textureID, uniformTexture;
    int width, height, bitDepth;
public:
    Texture();
    ~Texture();
    void createTexture(const std::string &pathname);
    GLuint GetTextureID() const;
    void useTexture() const;
    void clearTexture();
};
