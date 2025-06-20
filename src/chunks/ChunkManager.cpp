//
// Created by Wihy on 6/10/25.
//

// has list of chunks
// generateChunks near world location.
// automatically deletes chunks not in view.

#include "../../include/FlightSimulatorHopefully/terrain/ChunkManager.h"

#include <numeric>

void ChunkManager::renderNearChunks(const Shader &shader, const Camera &camera) {
    // //The distance apart from both farthest points from one another
    // const int cameraZInChunkCoords = static_cast<int>(camera.Position.z) / CHUNK_LENGTH;
    // const int cameraXInChunkCoords = static_cast<int>(camera.Position.x) / CHUNK_LENGTH;
    //
    // const float tanRatio = glm::tan(glm::radians(camera.FOVdegrees / 2));
    //
    // for (int j = 0; j <= camera.farPlane / CHUNK_LENGTH; ++j) {
    //     const float baseDistanceInChunkCoords = j * tanRatio + 2;
    //
    //     const int baseZInChunkCoords = cameraZInChunkCoords + j / CHUNK_LENGTH;
    //
    //     const glm::vec2 pointAInChunkCoords = {(cameraXInChunkCoords - baseDistanceInChunkCoords ) / 2 , baseZInChunkCoords};
    //     const glm::vec2 pointBInChunkCoords = {(cameraXInChunkCoords + baseDistanceInChunkCoords ) / 2 , baseZInChunkCoords};
    //
    //     for (auto i = static_cast<int>(pointAInChunkCoords.x); i < static_cast<int>(pointBInChunkCoords.x); i++) {
    //         // currentChunks.push_back({{i, j + cameraZInChunkCoords},
    //             // generateChunkMeshFromChunkCoords(i, j + cameraZInChunkCoords)});
    //
    //         generateChunkFromCoords(i, j + cameraZInChunkCoords).draw(shader, camera, {i * 8, -1, (j + cameraZInChunkCoords)*8}, {});
    //     }
    // }
    //
    // for (const auto &chunk: currentChunks) {
    //     chunk.renderChunk(shader, camera);
    // }
    //
    // // currentChunks.clear();

    //start with straight line.

    for (int z = camera.Position.z; z < camera.farPlane + camera.Position.z; z+=CHUNK_LENGTH) {
        generateChunkFromCoords(0, z/8).draw(shader, camera, {0, -10, 0}, {});
    }
}

//Coords in chunk based. Generates
Mesh ChunkManager::generateChunkFromCoords(const int chunkX, const int chunkZ) {
    constexpr int squareLength {CHUNK_LENGTH + 1} ;

    std::array<Vertex, 81> vertices{};
    std::array<GLuint, 432> indices{};

    for (int i = 0; i < std::ssize(vertices); ++i) {
        constexpr float noiseScalar {0.1f};

        const int verticesX = i / squareLength;
        const int verticesZ = i % squareLength;

        const float height = fractalNoise(noiseScalar * (verticesX + chunkX*8.0f), noiseScalar * (verticesZ + chunkZ*8.0f));

        vertices[i] = {{chunkX*8 + verticesX, 10 * height, chunkZ*8 + verticesZ}, {0.3 * height, 0.5 * height, 0.1 * height}};
    }

    int currentSquare = 0;

    for (int index = 0; index < ssize(indices); index +=6) {
        if ((currentSquare+1) % squareLength != 0) {
            indices[index] = currentSquare;
            indices[index + 1] = currentSquare + 1;
            indices[index + 2] = currentSquare + squareLength;

            indices[index + 3] = currentSquare + 1;
            indices[index + 4] = currentSquare + 1 + squareLength;
            indices[index + 5] = currentSquare + squareLength;
        }

        currentSquare++;
    }

    return Mesh{vertices, indices};
}

