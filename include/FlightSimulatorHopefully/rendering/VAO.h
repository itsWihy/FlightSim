//
// Created by Wihy on 6/9/25.
//

#ifndef VAO_H
#define VAO_H
#include <glad/glad.h>

#include "VBO.h"

class VAO {
public:
    GLuint ID {};

    VAO();

    void linkAttribute(const VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) const;
    void bind() const;
    void unbind() const;
    void deleteVAO() const;
};

#endif //VAO_H
