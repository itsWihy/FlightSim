//
// Created by Wihy on 6/9/25.
//

#ifndef MESH_H
#define MESH_H

#include "VAO.h"
#include "EBO.h"
#include "../Camera.h"


class Mesh {
    int indicesSize;

public:
    VAO VAO1{};

    Mesh()=default;

    template<typename T, typename U>
    Mesh(const T& vertices, const U& indices) : indicesSize(indices.size()) {
            VAO1.bind();

            const VBO VBO{vertices};
            const EBO EBO{indices};

            VAO1.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *) nullptr);
            VAO1.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *) (3 * sizeof(float)));

            VAO1.unbind();
            VBO.unbind();
            EBO.unbind();
    }

    void draw(const Shader &shader, const Camera &camera, const glm::vec3& positionOffset, const glm::vec3& rotationOffset ) const;
};

#endif //MESH_H
