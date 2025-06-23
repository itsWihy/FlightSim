#include "../../include/FlightSimulatorHopefully/rendering/VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::linkAttribute(const VBO& VBO, const GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) const {
    VBO.bind();

    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);

    VBO.unbind();
}

void VAO::bind() const {
    glBindVertexArray(ID);
}

void VAO::unbind() const {
    glBindVertexArray(0);
}

void VAO::deleteVAO() const {
    glDeleteVertexArrays(1, &ID);
}
