#ifndef EBO_H
#define EBO_H

#include <vector>
#include <glad/glad.h>

class EBO {
public:
    GLuint ID {};

    EBO(const std::vector<GLuint>& indices);

    void bind() const;
    void unbind() const;
    void deleteEBO() const;
};

#endif //EBO_H
