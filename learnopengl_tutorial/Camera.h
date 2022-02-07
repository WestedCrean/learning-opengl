#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


enum Direction { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
    public:
    // the program ID
    float Zoom;
    glm::mat4 view;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float lastFrame;

    float yaw;
    float pitch;
    // constructor 
    Camera(glm::vec3 position, float pitch, float yaw);
    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboard(Direction direction, float deltaTime);
    void ProcessMouseMovement(float offsetX, float offsetY);
    void ProcessMouseScroll(float offsetY);
};