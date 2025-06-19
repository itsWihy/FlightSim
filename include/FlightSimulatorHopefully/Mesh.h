//
// Created by Wihy on 6/9/25.
//

#ifndef MESH_H
#define MESH_H

#include"rendering/VAO.h"
#include"rendering/EBO.h"
#include"Camera.h"


class Mesh {
    const int indicesSize;

public:
    VAO VAO1;

    template<typename T, typename U>
    explicit Mesh(const T& vertices, const U& indices) : indicesSize(indices.size()) {
            VAO1.bind();

            const VBO VBO{vertices};
            const EBO EBO{indices};

            VAO1.linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *) nullptr);
            VAO1.linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *) (3 * sizeof(float)));

            VAO1.unbind();
            VBO.unbind();
            EBO.unbind();
    }

    void draw(const Shader &shader, const Camera &camera, const glm::vec3& position, const glm::vec3& rotation ) const;
};

#endif //MESH_H
