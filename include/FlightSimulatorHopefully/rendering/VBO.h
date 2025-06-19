#ifndef VBO_H
#define VBO_H
#include <vector>
#include <glad/glad.h>
#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

class VBO {
public:
    GLuint ID {};

    template<typename T>
    explicit VBO(const T& vertices) {
        glGenBuffers(1, &ID);

        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, std::ssize(vertices) * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    void bind() const;
    void unbind() const;
    void deleteVBO() const;
};

#endif //VBO_H
