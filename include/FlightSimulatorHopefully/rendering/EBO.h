#ifndef EBO_H
#define EBO_H

#include <vector>
#include <glad/glad.h>

class EBO {
public:
    GLuint ID {};

    template<typename T>
    explicit EBO(const T& indices) {
        glGenBuffers(1, &ID);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, std::ssize(indices) * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    void bind() const;
    void unbind() const;
    void deleteEBO() const;
};

#endif //EBO_H
