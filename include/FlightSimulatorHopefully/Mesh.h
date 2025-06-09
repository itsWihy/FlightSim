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
    glm::vec3 position {};
    glm::vec3 rotation {};

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    VAO VAO1;

    Mesh(const std::vector<Vertex> &vertices, std::vector<GLuint> &indices, glm::vec3 position={}, glm::vec3 rotation={});

    void draw(Shader &shader, Camera &camera);
};

#endif //MESH_H
