#ifndef EBO_H
#define EBO_H
#include <glad/glad.h>

class EBO {
public:
    GLuint ID {};

    EBO(const GLuint* indices, GLsizeiptr size);

    void bind() const;
    void unbind() const;
    void deleteEBO() const;
};

#endif //EBO_H
