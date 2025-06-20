//
// Created by Wihy on 6/10/25.
//

#ifndef CHUNK_H
#define CHUNK_H
#include <map>

#include "../rendering/Mesh.h"

//World is divided into 8 by 8 chunks. Where (0,0) is 0,0, (1,1) is 8,8, and so on.

class Chunk {
private:
    std::array<glm::vec3, 64> facePositions;

    const Mesh& chunkMesh;
    const glm::vec3 rotation = {90, 0, 0};

    const glm::vec2 chunkPosition {};

public:
    Chunk(const glm::vec2& chunkPosition, const Mesh& chunkMesh);

    void renderChunk(const Shader& shader, const Camera& camera) const;
};

#endif //CHUNK_H
