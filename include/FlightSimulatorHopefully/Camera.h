#ifndef CAMERA_H
#define CAMERA_H
#include "rendering/Shader.h"

#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    glm::vec3 Position{};
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    int width;
    int height;

    float speed = 0.0f;
    float acceleration = 0.0f;

    Camera(int width, int height, glm::vec3 position);

    void updateCameraMatrix(float FOVdegrees, float nearPlane, float farPlane, const Shader& shader) const;
    void inputs(GLFWwindow* window);
};

#endif //CAMERA_H
