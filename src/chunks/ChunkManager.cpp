//
// Created by Wihy on 6/10/25.
//

// has list of chunks
// generateChunks near world location.
// automatically deletes chunks not in view.

#include "../../include/FlightSimulatorHopefully/chunk/ChunkManager.h"

ChunkManager::ChunkManager(const Mesh& chunkMesh)
    : chunkMesh(chunkMesh) {
}


void ChunkManager::renderNearChunks(Shader &shader, Camera &camera) {
    //The distance apart from both farthest points from one another
    int cameraZInChunkCoords = static_cast<int>(camera.Position.z) / 8;

    float longDistance = camera.farPlane * glm::tan(glm::radians(camera.FOVdegrees / 2));

    int zValueInChunkCoords = cameraZInChunkCoords + static_cast<int>(camera.farPlane) / 8;

    glm::vec2 pointAInChunkCoords = {(camera.Position.x - longDistance / 2) / 8, zValueInChunkCoords};
    glm::vec2 pointBInChunkCoords = {(camera.Position.x + longDistance / 2) / 8, zValueInChunkCoords};

    for (auto i = static_cast<int>(pointAInChunkCoords.x); i < static_cast<int>(pointBInChunkCoords.x); i++) {
        currentChunks.push_back({{i, 1 + cameraZInChunkCoords}, chunkMesh});
    }

    for (auto const &chunk: currentChunks) {
        chunk.renderChunk(shader, camera);
    }

    currentChunks.clear(); //todo: figure better w a y
}
