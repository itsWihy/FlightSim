#include "../../include/FlightSimulatorHopefully/Camera.h"

Camera::Camera(const int width, const int height, const glm::vec3 position, const float FOVdegrees, const float nearPlane, const float farPlane)
    : Position(position), width(width), height(height), FOVdegrees(FOVdegrees), nearPlane(nearPlane), farPlane(farPlane) {
}

void Camera::updateCameraMatrix(const Shader &shader) const {
    const auto view = glm::lookAt(Position, Position + Orientation, Up);
    const auto projection = glm::perspective(glm::radians(FOVdegrees), static_cast<float>(width / height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow *window) {
    Position += speed * Orientation;
    speed += acceleration;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        speed = 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        speed = -0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        speed = 0;
    }
}
