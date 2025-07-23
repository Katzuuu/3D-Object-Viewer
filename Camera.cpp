#include "Camera.h"

#include <iostream>
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 initialPosition, glm::vec3 initialWorldUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat initialMoveSpeed, GLfloat initialTurnSpeed)
    : position(initialPosition), front(glm::vec3(0.0f, 0.0f, -1.0f)), worldUp(initialWorldUp),
        moveSpeed(initialMoveSpeed), turnSpeed(initialTurnSpeed), pitch(initialPitch), yaw(initialYaw) {
    Update();
}

void Camera::Update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::KeyControl(const bool *keys, const GLdouble deltaTime) {
    const float velocity = moveSpeed * static_cast<float>(deltaTime);

    if (keys[GLFW_KEY_W]) {
        position += front * velocity;
    }
    if (keys[GLFW_KEY_A]) {
        position -= right * velocity;
    }
    if (keys[GLFW_KEY_S]) {
        position -= front * velocity;
    }
    if (keys[GLFW_KEY_D]) {
        position += right * velocity;
    }
}

void Camera::MouseControl(const GLfloat xChange, const GLfloat yChange) {
    yaw += turnSpeed * xChange;
    pitch += turnSpeed * -yChange;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    Update();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

Camera::~Camera() {}

