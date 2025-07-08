#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIN_W 800
#define WIN_H 600

GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float increment = 0.0005f;

std::string readShader(const std::string& pathname) {
    if (pathname.empty())
        throw std::invalid_argument("File pathname is empty!");

    std::ifstream file(pathname, std::ios::in | std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open the file: " + pathname);

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void createTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // generate VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // unbinding VBO & VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void addShader(GLuint program, const std::string& pathname, GLenum shaderType) {
    std::string shaderSource = readShader(pathname);
    const char* shaderCode = shaderSource.c_str();

    GLuint shader = glCreateShader(shaderType);
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

void compileShader() {
    shader = glCreateProgram();

    if(!shader)
        throw std::runtime_error("Failed to create a program!");

    addShader(shader, "src/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
    addShader(shader, "src/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);

    glLinkProgram(shader);

    GLint result;
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if(!result) {
        char infoLog[512];
        glGetProgramInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Program linking failed:\n") + infoLog);
    }

    glValidateProgram(shader);

    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if(!result) {
        char infoLog[512];
        glGetProgramInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Program is not valid:\n") + infoLog);
    }

    uniformModel = glGetUniformLocation(shader, "model");
    
}

int main(void) {

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if(!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(WIN_W, WIN_H, "3D Object Viewer", NULL, NULL);
    if(window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create a GLFW Window!");
    }
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GL_FALSE);
    glfwMakeContextCurrent(window);

    // initialization of GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
    glViewport(0, 0, WIN_W, WIN_H);

    createTriangle();
    compileShader();

    while(!glfwWindowShouldClose(window)) {
        triOffset += direction ? increment : increment * -1;
        if(abs(triOffset) >= triMaxOffset)
            direction = !direction;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(triOffset, triOffset * -1, 0.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}