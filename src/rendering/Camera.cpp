#include "../../include/FlightSimulatorHopefully/Camera.h"

Camera::Camera(const int width, const int height, const glm::vec3 position) {
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

void Camera::updateCameraMatrix(float FOVdegrees, float nearPlane, float farPlane, const Shader &shader) const {
    const auto view = glm::lookAt(Position, Position + Orientation, Up);
    const auto projection = glm::perspective(glm::radians(FOVdegrees), static_cast<float>(width / height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow *window) {
    speed += acceleration;
    Position += speed * Orientation;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        acceleration = 0.01f;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        acceleration = -0.01f;
    }
}
