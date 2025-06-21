//
// Created by Wihy on 6/10/25.
//

// has list of chunks
// generateChunks near world location.
// automatically deletes chunks not in view.

#include "../../include/FlightSimulatorHopefully/terrain/ChunkManager.h"

#include <numeric>
#include <ranges>

//TODO: Use player position, not CMAERA POSITION!

void ChunkManager::renderNearChunks(const Shader &shader, const Camera &camera) {
    constexpr double degToRad = std::numbers::pi / 180;
    std::vector<Mesh> viewableChunks{};

    const ChunkCoords cameraCoords{static_cast<int>(camera.Position.x) / 8, static_cast<int>(camera.Position.z) / 8};
//TODO: Take into account camera yaw && camera height
    const auto farPlaneInChunkCoords = static_cast<int>(camera.farPlane) / 8;
    const auto tanRatio =  glm::tan(camera.FOVdegrees * degToRad / 2);

    for (auto z = farPlaneInChunkCoords + cameraCoords.z; z >= cameraCoords.z - 12; --z) {
        const auto baseLength = static_cast<int>((z + 8 - cameraCoords.z) * tanRatio);

        for (int x = -baseLength + cameraCoords.x; x < baseLength + cameraCoords.x; ++x) {
            const ChunkCoords coords{x, z};

            if (!cachedChunks.contains(coords))
                cachedChunks.try_emplace(coords, generateChunkFromCoords(x, z));

            viewableChunks.push_back(cachedChunks[coords]);
        }
    }

    for (const auto &chunk: viewableChunks) {
        chunk.draw(shader, camera, {0, -10, 0}, {});
    }

    viewableChunks.clear();
}

//Coords in chunk based. Generates
Mesh ChunkManager::generateChunkFromCoords(const int chunkX, const int chunkZ) {
    constexpr int squareLength{CHUNK_LENGTH + 1};

    std::array<Vertex, 81> vertices{};
    std::array<GLuint, 432> indices{};

    for (int i = 0; i < std::ssize(vertices); ++i) {
        constexpr float noiseScalar{0.1f};

        const int verticesX = i / squareLength;
        const int verticesZ = i % squareLength;

        const float height = fractalNoise(noiseScalar * (verticesX + chunkX * 8.0f), noiseScalar * (verticesZ + chunkZ * 8.0f));

        vertices[i] = {
            {chunkX * 8 + verticesX, 10 * height, chunkZ * 8 + verticesZ}, {0.3 * height, 0.5 * height, 0.1 * height}
        };
    }

    int currentSquare = 0;

    for (int index = 0; index < ssize(indices); index += 6) {
        if ((currentSquare + 1) % squareLength != 0) {
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
