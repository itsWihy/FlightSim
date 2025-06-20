#include "../../include/FlightSimulatorHopefully/rendering/Mesh.h"

void Mesh::draw(const Shader &shader, const Camera &camera, const glm::vec3& positionOffset, const glm::vec3& rotationOffset) const {
    shader.activateShaders();
    VAO1.bind();

    //apply offset:
    glm::mat4 model = glm::translate(glm::mat4(1.0f), positionOffset);

    if (rotationOffset.x != 0)
        model = glm::rotate(model, glm::radians(rotationOffset.x), {1, 0, 0});

    if (rotationOffset.y != 0)
        model = glm::rotate(model, glm::radians(rotationOffset.y), {0, 1, 0});

    if (rotationOffset.z != 0)
        model = glm::rotate(model, glm::radians(rotationOffset.z), {0, 0, 1});

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));

    camera.updateCameraMatrix(shader);
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}
