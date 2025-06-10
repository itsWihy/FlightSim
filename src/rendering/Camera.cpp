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
