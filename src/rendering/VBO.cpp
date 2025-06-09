//
// Created by Wihy on 6/9/25.
//

#include "../../include/FlightSimulatorHopefully/rendering/VBO.h"

#include <glad/glad.h>

VBO::VBO(const GLfloat *vertices, const GLsizeiptr size) {
    glGenBuffers(1, &ID);

    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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
