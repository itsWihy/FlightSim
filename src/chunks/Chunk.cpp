//
// Created by Wihy on 6/10/25.
//

//16 by 16
// has 16^2 meshes.
//hide / show / delete abilities.

#include "../../include/FlightSimulatorHopefully/chunk/Chunk.h"


Chunk::Chunk(const glm::vec3 &chunkPosition, const std::vector<Vertex> &vertices, std::vector<GLuint> &indices)
    : chunkPosition(chunkPosition) {
    for (int i = 0; i < 8; i+=2) {
        for (int j = 0; j < 8; j+=2) {
            faces[8 * i + j]= {vertices, indices, {i, -3, j}, {90, 0, 0}};
        }
    }
}

void Chunk::renderChunk(const Shader &shader, const Camera &camera) const {
    for (auto face: faces) {
        face.draw(shader, camera);
    }
}
