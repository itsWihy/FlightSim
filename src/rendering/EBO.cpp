//
// Created by Wihy on 6/9/25.
//

#include "../../include/FlightSimulatorHopefully/rendering/EBO.h"

#include <vector>
#include <glad/glad.h>

template<typename T>
EBO::EBO(const T& indices) {
    glGenBuffers(1, &ID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, std::ssize(indices) * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

EBO::EBO() : EBO( std::vector<GLuint>{}) {
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
