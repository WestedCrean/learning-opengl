#define GLFW_INCLUDE_NONE
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

Camera::Camera(glm::vec3 position, float pitch = 0.0f, float yaw = 270.0f) {
    // glm::mat4 view;
    // glm::vec3 cameraPos;
    // glm::vec3 cameraFront;
    // glm::vec3 cameraUp;
    // 
    // float lastX;
    // float lastY;
    // bool firstMouse;
    // 
    // float yaw;
    // float pitch;
    // float fov;
    this->cameraPos = position;
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    this->yaw = yaw;
    this->pitch = pitch;
    this->Zoom = 45.0f;

    this->lastFrame = 0.0f;
};

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ProcessKeyboard(Direction direction, float deltaTime) {
    float cameraSpeed = 2.5f * deltaTime;

    if (direction == Direction::FORWARD) {
        cameraPos = cameraPos + cameraSpeed * cameraFront;
    }
    if (direction == Direction::BACKWARD) {
        cameraPos = cameraPos - cameraSpeed * cameraFront;
    }
    if (direction == Direction::LEFT) {
        cameraPos = cameraPos - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (direction == Direction::RIGHT) {
        cameraPos = cameraPos + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    // std::cout << "New camera pos: " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
}

void Camera::ProcessMouseMovement(float offsetX, float offsetY) {
    float sensitivity = 0.1f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    yaw = glm::mod(yaw, 360.0f); // clamp yaw

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    // std::cout << "New pitch, yaw : " << pitch << ", " << yaw << std::endl;
}

void Camera::ProcessMouseScroll(float offsetY) {
    Zoom -= (float)offsetY;
    if (Zoom < 20.0f)
        Zoom = 20.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
    // std::cout << "New zoom: " << Zoom << std::endl;
}
