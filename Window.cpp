#include "Window.h"

Window::Window(): bufferWidth(0), bufferHeight(0) {
    winWidth = 800;
    winHeight = 600;
    window = nullptr;
    memset(keys, false, sizeof(keys));
}

Window::Window(const GLint winWidth, GLint winHeight)
    : winWidth(winWidth), winHeight(winHeight), bufferWidth(0), bufferHeight(0) {
    window = nullptr;
    memset(keys, false, sizeof(keys));
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

    // handle key + mouse input
    CreateCallbacks();

    // initialization of GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        throw std::runtime_error("Failed to initialize GLAD");

    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glViewport(0, 0, bufferWidth, bufferHeight);
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window, this);
}

void Window::HandleKeys(GLFWwindow *window, int key, int code, int action, int mode) {
    Window *self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            self->keys[key] = true;
            std::cout << "Pressed " << key << "\n";
        } else if (action == GLFW_RELEASE) {
            self->keys[key] = false;
            std::cout << "Released " << key << "\n";
        }
    }
}

void Window::CreateCallbacks() const {
    glfwSetKeyCallback(window, HandleKeys);
}

Window::~Window() {
    if (window != nullptr) glfwDestroyWindow(window);
    glfwTerminate();
}
