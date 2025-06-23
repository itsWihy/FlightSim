#ifndef CAMERA_H
#define CAMERA_H
#include "rendering/Shader.h"

#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "YokeSystemInputs.h"

class Camera {
public:
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Position{};
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 1.0f);

    int width;
    int height;

    float FOVdegrees;
    float nearPlane;
    float farPlane;

    float speed = 0.0f;
    float acceleration = 0.0f;

    Camera(int width, int height, glm::vec3 position, float FOVdegrees, float nearPlane, float farPlane);

    void updateCameraMatrix(const Shader& shader) const;
    void inputs(GLFWwindow* window, const YokeSystem& yokeSystem);
};

#endif //CAMERA_H
