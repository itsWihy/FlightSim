#ifndef EBO_H
#define EBO_H

#include <vector>
#include <glad/glad.h>

class EBO {
public:
    GLuint ID {};

    explicit EBO();

    template<typename T>
    explicit EBO(const T& indices);

    void bind() const;
    void unbind() const;
    void deleteEBO() const;
};

#endif //EBO_H
