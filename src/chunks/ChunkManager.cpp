//
// Created by Wihy on 6/10/25.
//

// has list of chunks
// generateChunks near world location.
// automatically deletes chunks not in view.

#include "../../include/FlightSimulatorHopefully/chunk/ChunkManager.h"

#include <numeric>

ChunkManager::ChunkManager(const Mesh& chunkMesh)
    : chunkMesh(chunkMesh) {
}


void ChunkManager::renderNearChunks(const Shader &shader, const Camera &camera) {
    constexpr int CHUNK_SIZE = 8;

    //The distance apart from both farthest points from one another
    const int cameraZInChunkCoords = static_cast<int>(camera.Position.z) / CHUNK_SIZE;
    const int cameraXInChunkCoords = static_cast<int>(camera.Position.x) / CHUNK_SIZE;

    const float tanRatio = glm::tan(glm::radians(camera.FOVdegrees / 2));

    for (int j = 0; j <= camera.farPlane / CHUNK_SIZE; ++j) {
        const float baseDistanceInChunkCoords = j * tanRatio + 2;

        const int baseZInChunkCoords = cameraZInChunkCoords + j / CHUNK_SIZE;

        const glm::vec2 pointAInChunkCoords = {(cameraXInChunkCoords - baseDistanceInChunkCoords ) / 2 , baseZInChunkCoords};
        const glm::vec2 pointBInChunkCoords = {(cameraXInChunkCoords + baseDistanceInChunkCoords ) / 2 , baseZInChunkCoords};

        for (auto i = static_cast<int>(pointAInChunkCoords.x); i < static_cast<int>(pointBInChunkCoords.x); i++) {
            currentChunks.push_back({{i, j + cameraZInChunkCoords}, chunkMesh});
        }
    }


    for (const auto &chunk: currentChunks) {
        chunk.renderChunk(shader, camera);
    }

    currentChunks.clear();
}
