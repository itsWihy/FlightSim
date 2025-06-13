#include "../../include/FlightSimulatorHopefully/Mesh.h"

Mesh::Mesh() : vertices({}), indices({}) {
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices)
    : vertices(vertices), indices(indices) {
    VAO1.bind();

    const VBO VBO(vertices);
    const EBO EBO(indices);

    VAO1.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *) 0);
    VAO1.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *) (3 * sizeof(float)));

    VAO1.unbind();
    VBO.unbind();
    EBO.unbind();
}

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
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
