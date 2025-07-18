#include "Window.h"

Window::Window()
    : winWidth(800), winHeight(600), bufferWidth(0),
        bufferHeight(0), window(nullptr), lastX(0),
        lastY(0), xChange(0), yChange(0), mouseFirstMoved(true) {
    memset(keys, false, sizeof(keys));
}

Window::Window(const GLint winWidth, GLint winHeight)
    : winWidth(winWidth), winHeight(winHeight),
        bufferWidth(0), bufferHeight(0), window(nullptr),
        lastX(0), lastY(0), xChange(0), yChange(0), mouseFirstMoved(true) {
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

void Window::HandleMouse(GLFWwindow *window, const double xPos, const double yPos) {
    Window *self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (self->mouseFirstMoved) {
        self->lastX = xPos;
        self->lastY = yPos;
        self->mouseFirstMoved = false;
    }

    self->xChange = xPos - self->lastX;
    self->yChange = yPos - self->lastY;
    self->lastX = xPos;
    self->lastY = yPos;

    std::cout << "xChange: " << self->xChange << "\n";
    std::cout << "yChange: " << self->yChange << "\n";
}

GLfloat Window::GetXChange() {
    const GLfloat theChange = xChange;
    xChange = 0;
    return theChange;
}

GLfloat Window::GetYChange() {
    const GLfloat theChange = yChange;
    yChange = 0;
    return theChange;
}

void Window::CreateCallbacks() const {
    glfwSetKeyCallback(window, HandleKeys);
    glfwSetCursorPosCallback(window, HandleMouse);
}

Window::~Window() {
    if (window != nullptr)
        glfwDestroyWindow(window);
    glfwTerminate();
}
