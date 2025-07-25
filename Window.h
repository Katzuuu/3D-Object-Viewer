# pragma once

#include <iostream>
#include <string.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    GLfloat winWidth, winHeight;
    GLint bufferWidth, bufferHeight;

    GLFWwindow* window;

    bool keys[1024];
    GLfloat lastX, lastY;
    GLfloat xChange, yChange;
    bool mouseFirstMoved;
public:
    Window();
    Window(GLint winWidth, GLint winHeight);
    ~Window();
    void Initialize();
    GLfloat GetBufferWidth() const { return bufferWidth; };
    GLfloat GetBufferHeight() const { return bufferHeight; };
    bool GetShouldClose() const { return glfwWindowShouldClose(window); };
    const bool *GetKeys() const { return keys; };
    GLfloat GetXChange();
    GLfloat GetYChange();
    void SwapBuffers() const { glfwSwapBuffers(window); };
    void PollEvents() const { glfwPollEvents(); };
private:
    static void HandleKeys(GLFWwindow *window, int key, int code, int action, int mode);
    static void HandleMouse(GLFWwindow *window, double xPos, double yPos);
    void CreateCallbacks() const;
};
