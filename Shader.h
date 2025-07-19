#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

class Shader {
    GLuint shaderID, uniformProjection, uniformModel, uniformView;
public:
    Shader();
    ~Shader();

    std::string ReadFile(const std::string &pathname) const;
    void CreateFromFiles(const std::string &vertexPathname, const std::string &fragmentPathname);
    GLuint GetProjectionLocation() const;
    GLuint GetModelLocation() const;
    GLuint GetViewLocation() const;
    void UseShader() const;
    void ClearShader();
private:
    void CompileShader(const char *vertexCode, const char *fragmentCode);
    void AddShader(const GLuint program, const char *shaderCode, const GLenum shaderType) const;
};
