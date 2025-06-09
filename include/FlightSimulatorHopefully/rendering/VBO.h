#ifndef VBO_H
#define VBO_H
#include <glad/glad.h>

class VBO {
public:
    GLuint ID {};

    VBO(const GLfloat* vertices, GLsizeiptr size);

    void bind() const;
    void unbind() const;
    void deleteVBO() const;
};

#endif //VBO_H
