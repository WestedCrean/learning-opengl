#define GLFW_INCLUDE_NONE
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

Camera::Camera(glm::vec3 position, float pitch = 0.0f, float yaw = 270.0f) {
    this->Position = position;
    this->Front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->Up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->yaw = yaw;
    this->pitch = pitch;
    this->Zoom = 45.0f;

    this->lastFrame = 0.0f;
};

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Direction direction, float deltaTime) {
    float cameraSpeed = 2.5f * deltaTime;

    if (direction == Direction::FORWARD) {
        Position = Position + cameraSpeed * Front;
    }
    if (direction == Direction::BACKWARD) {
        Position = Position - cameraSpeed * Front;
    }
    if (direction == Direction::LEFT) {
        Position = Position - glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
    }
    if (direction == Direction::RIGHT) {
        Position = Position + glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
    }

    //std::cout << "Camera position: " << Position.x << " , " << Position.y << " , " << Position.z << std::endl;
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
    Front = glm::normalize(direction);

    // std::cout << "New pitch, yaw : " << pitch << ", " << yaw << std::endl;
}

void Camera::ProcessMouseScroll(float offsetY) {
    Zoom -= (float)offsetY;
    if (Zoom < 20.0f)
        Zoom = 20.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
    // std::cout << "New zoom: " << zoom << std::endl;
}
