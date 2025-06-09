//
// Created by Wihy on 6/9/25.
//

#include "../../include/FlightSimulatorHopefully/rendering/EBO.h"

#include <glad/glad.h>

EBO::EBO(const GLuint* indices, const GLsizeiptr size) {
    glGenBuffers(1, &ID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::deleteEBO() const {
    glDeleteBuffers(1, &ID);
}
