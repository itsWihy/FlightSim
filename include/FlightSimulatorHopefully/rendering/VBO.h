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

    explicit VBO(const std::vector<Vertex>& vertices);

    void bind() const;
    void unbind() const;
    void deleteVBO() const;
};

#endif //VBO_H
