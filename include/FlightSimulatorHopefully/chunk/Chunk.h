//
// Created by Wihy on 6/10/25.
//

#ifndef CHUNK_H
#define CHUNK_H
#include <map>

#include "../Mesh.h"

//World is divided into 8 by 8 chunks. Where (0,0) is 0,0, (1,1) is 8,8, and so on.

class Chunk {
    std::array<Mesh, 64> faces;
    const glm::vec3 chunkPosition {};

public:
    Chunk(const glm::vec3& chunkPosition, const std::vector<Vertex> &vertices, std::vector<GLuint> &indices);
    void renderChunk(const Shader& shader, const Camera& camera) const;
};

#endif //CHUNK_H
