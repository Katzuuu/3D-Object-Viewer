#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    glm::vec3 position, front, up{}, right{}, worldUp;
    GLfloat moveSpeed, turnSpeed, pitch, yaw;
public:
    Camera(glm::vec3 initialPosition, glm::vec3 initialWorldUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat initialMoveSpeed, GLfloat initialTurnSpeed);
    ~Camera();
    void Update();
    void KeyControl(const bool *keys);
    glm::mat4 GetViewMatrix() const;
};
