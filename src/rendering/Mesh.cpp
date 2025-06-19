#include "../../include/FlightSimulatorHopefully/Mesh.h"

void Mesh::draw(const Shader &shader, const Camera &camera, const glm::vec3& position, const glm::vec3& rotation ) const {
    shader.activateShaders();
    VAO1.bind();

    //apply offset:
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    if (rotation.x != 0)
        model = glm::rotate(model, glm::radians(rotation.x), {1, 0, 0});

    if (rotation.y != 0)
        model = glm::rotate(model, glm::radians(rotation.y), {0, 1, 0});

    if (rotation.z != 0)
        model = glm::rotate(model, glm::radians(rotation.z), {0, 0, 1});

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));

    camera.updateCameraMatrix(shader);
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}
