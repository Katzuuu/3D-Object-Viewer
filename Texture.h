#pragma once

#include <string>
#include <glad/glad.h>
#include "stb_image.h"
#include <stdexcept>

class Texture {
    GLuint textureID{}, uniformTexture{};
    int width{}, height{}, bitDepth{};
    std::string filename;
public:
    explicit Texture(std::string  fileName);
    ~Texture();
    void loadTexture();
    GLuint GetTextureID() const;
    void useTexture() const;
    void clearTexture();
};
