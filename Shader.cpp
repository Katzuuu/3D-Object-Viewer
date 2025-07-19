#include "Shader.h"

Shader::Shader() {
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

std::string Shader::ReadFile(const std::string &pathname) const {
    if (pathname.empty())
        throw std::invalid_argument("File pathname is empty!");

    std::ifstream file(pathname, std::ios::in | std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open the file: " + pathname);

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::CreateFromFiles(const std::string &vertexPathname, const std::string &fragmentPathname) {
    if (vertexPathname.empty() || fragmentPathname.empty())
        throw std::invalid_argument("File pathname is empty!");

    const std::string vertexSource = ReadFile(vertexPathname);
    const char* vertexCode = vertexSource.c_str();

    const std::string fragmentSource = ReadFile(fragmentPathname);
    const char* fragmentCode = fragmentSource.c_str();

    CompileShader(vertexCode, fragmentCode);
}

void Shader::CompileShader(const char *vertexCode, const char *fragmentCode) {
    shaderID = glCreateProgram();

    if(shaderID == 0)
        throw std::runtime_error("Failed to create a program!");

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    glLinkProgram(shaderID);

    GLint result;
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if(!result) {
        char infoLog[512];
        glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Program linking failed:\n") + infoLog);
    }

    glValidateProgram(shaderID);

    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if(!result) {
        char infoLog[512];
        glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Program is not valid:\n") + infoLog);
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
}

void Shader::AddShader(const GLuint program, const char *shaderCode, const GLenum shaderType) const {
    const GLint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Shader compilation failed:\n") + infoLog);
    }

    glAttachShader(program, shader);
    glDeleteShader(shader);
}

GLuint Shader::GetModelLocation() const {
    return uniformModel;
}

GLuint Shader::GetProjectionLocation() const {
    return uniformProjection;
}

GLuint Shader::GetViewLocation() const {
    return uniformView;
}

void Shader::UseShader() const {
    glUseProgram(shaderID);
}

void Shader::ClearShader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;
}

Shader::~Shader() {
    ClearShader();
}


