//
// Created by Wihy on 6/9/25.
//

#include "../../include/FlightSimulatorHopefully/rendering/VBO.h"

#include <glad/glad.h>


VBO::VBO(const std::vector<Vertex>& vertices) {
    glGenBuffers(1, &ID);

    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, std::ssize(vertices) * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO() const {
    glDeleteBuffers(1, &ID);
}
