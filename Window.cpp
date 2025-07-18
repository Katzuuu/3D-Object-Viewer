#include "Window.h"

Window::Window(): bufferWidth(0), bufferHeight(0) {
    winWidth = 800;
    winHeight = 600;
    window = nullptr;
}

Window::Window(const GLint winWidth, GLint winHeight)
    : winWidth(winWidth), winHeight(winHeight), bufferWidth(0), bufferHeight(0) {
    window = nullptr;
}

void Window::Initialize() {
    if(!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(
        winWidth,
        winHeight,
        "3D Object Viewer",
        nullptr,
        nullptr
    );

    if(window == nullptr)
        throw std::runtime_error("Failed to create GLFW window");

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GL_FALSE);
    glfwMakeContextCurrent(window);

    // initialization of GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        throw std::runtime_error("Failed to initialize GLAD");

    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glViewport(0, 0, bufferWidth, bufferHeight);
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    if (window != nullptr) glfwDestroyWindow(window);
    glfwTerminate();
}
