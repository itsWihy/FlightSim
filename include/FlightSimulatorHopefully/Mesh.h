//
// Created by Wihy on 6/9/25.
//

#ifndef MESH_H
#define MESH_H

#include"rendering/VAO.h"
#include"rendering/EBO.h"
#include"Camera.h"


class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    VAO VAO1;

    Mesh();
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);

    void draw(const Shader &shader, const Camera &camera, const glm::vec3& position, const glm::vec3& rotation ) const;
};

#endif //MESH_H
