#include "../../include/FlightSimulatorHopefully/Camera.h"

Camera::Camera(const int width, const int height, const glm::vec3 position, const float FOVdegrees, const float nearPlane, const float farPlane)
    : Position(position), width(width), height(height), FOVdegrees(FOVdegrees), nearPlane(nearPlane), farPlane(farPlane) {
}

void Camera::updateCameraMatrix(const Shader &shader) const {
    const auto view = glm::lookAt(Position, Position + Orientation, Up);
    const auto projection = glm::perspective(glm::radians(FOVdegrees), static_cast<float>(width / height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow *window, const YokeSystem& yokeSystem) {
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }

    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed = 0.7f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		speed = 0.2f;
	}
	const float yawKeySpeedDeg = 2.0f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		// Yaw left: rotate Orientation around Up by +yawKeySpeedDeg
		float angleRad = glm::radians(yawKeySpeedDeg);
		glm::mat4 yawMat = glm::rotate(glm::mat4(1.0f), angleRad, Up);
		Orientation = glm::normalize(glm::vec3(yawMat * glm::vec4(Orientation, 0.0f)));
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		// Yaw right: rotate Orientation around Up by -yawKeySpeedDeg
		float angleRad = glm::radians(-yawKeySpeedDeg);
		glm::mat4 yawMat = glm::rotate(glm::mat4(1.0f), angleRad, Up);
		Orientation = glm::normalize(glm::vec3(yawMat * glm::vec4(Orientation, 0.0f)));
	}

    // Position += speed * Orientation;
    // speed += acceleration;
    //
    // Orientation.y += yokeSystem.getDataNormalized(AxisTypes::STEERING_PUSH_PULL) / 10.0;
    // Orientation.x -= yokeSystem.getDataNormalized(AxisTypes::STEERING_ROTATE) / 10.0;
    //
    // acceleration = yokeSystem.getDataNormalized(AxisTypes::WORKING_THRUST) / 100.0;
}
