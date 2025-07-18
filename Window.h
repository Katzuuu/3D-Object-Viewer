# pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    GLfloat winWidth, winHeight;
    GLint bufferWidth, bufferHeight;
    GLFWwindow* window;
public:
    Window();
    Window(GLint winWidth, GLint winHeight);
    ~Window();
    void Initialize();
    GLfloat GetBufferWidth() const { return bufferWidth; };
    GLfloat GetBufferHeight() const { return bufferHeight; };
    bool GetShouldClose() const { return glfwWindowShouldClose(window); };
    void SwapBuffers() const { glfwSwapBuffers(window); };
    void PollEvents() const { glfwPollEvents(); };
};
