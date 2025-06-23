//
// Created by Wihy on 6/10/25.
//

// has list of chunks
// generateChunks near world location.
// automatically deletes chunks not in view.

#include "../../include/FlightSimulatorHopefully/terrain/ChunkManager.h"

#include <numeric>
#include <ranges>


void ChunkManager::renderNearChunks(const Shader &shader, const Camera &camera) {
    constexpr int margin = 3;

    const ChunkCoords cameraCoords{static_cast<int>(std::floor(camera.Position.x / 8.0f)), static_cast<int>(std::floor(camera.Position.z / 8.0f))};

    const double yaw = atan2(camera.Orientation.x, camera.Orientation.z);

    const auto cosY = static_cast<float>(std::cos(yaw));
    const auto sinY = static_cast<float>(std::sin(yaw));

    const auto rotateToCameraSpace = glm::mat2(
        glm::vec2(cosY, sinY),
        glm::vec2(-sinY, cosY)
    );

    const auto tanHalfFov = std::tan(camera.FOVdegrees * degToRad / 2.0);

    const auto farLengthInChunkCoords = static_cast<int>(std::ceil(camera.farPlane / 8.0));

    const int minX = cameraCoords.x - farLengthInChunkCoords;
    const int maxX = cameraCoords.x + farLengthInChunkCoords;
    const int minZ = cameraCoords.z - farLengthInChunkCoords;
    const int maxZ = cameraCoords.z + farLengthInChunkCoords;

    std::vector<Mesh> viewableChunks;
    viewableChunks.reserve((maxX - minX + 1) * (maxZ - minZ + 1));

    for (int z = minZ; z <= maxZ; z++) {
        for (int x = minX; x <= maxX; x++) {
            const ChunkCoords worldCoords{x, z};

            glm::vec2 relativeChunkPoseFromCamera(
                static_cast<float>(x - cameraCoords.x),
                static_cast<float>(z - cameraCoords.z)
            );

            const glm::vec2 cameraSpace = rotateToCameraSpace * relativeChunkPoseFromCamera;

            const float camX = cameraSpace.x;
            const float camZ = cameraSpace.y;

            if (camZ < 0.0f) continue;
            if (std::abs(camX) > camZ * tanHalfFov + margin) continue;

            if (!cachedChunks.contains(worldCoords))
                cachedChunks.try_emplace(worldCoords, generateChunkFromCoords(x, z));

            viewableChunks.push_back(cachedChunks[worldCoords]);
        }
    }

    for (const auto &chunk: viewableChunks) {
        chunk.draw(shader, camera, {0, -10, 0}, {});
    }

    viewableChunks.clear();
}


Mesh ChunkManager::generateChunkFromCoords(const int chunkX, const int chunkZ) {
    constexpr int squareLength{CHUNK_LENGTH + 1};
    constexpr float noiseScalar{0.1f};

    std::array<Vertex, 81> vertices{};

    const int worldX = chunkX * 8;
    const int worldZ = chunkZ * 8;

    for (int i = 0; i < std::ssize(vertices); ++i) {
        const int verticesX = i / squareLength;
        const int verticesZ = i % squareLength;

        const float height = fractalNoise(noiseScalar * (verticesX + worldX), noiseScalar * (verticesZ + worldZ));

        vertices[i] = {
            {worldX + verticesX, 10 * height, worldZ + verticesZ}, {0.3 * height, 0.5 * height, 0.1 * height}
        };
    }

    return Mesh{vertices, indicesPrecomputed};
}

//Here so can be reused if changing the chunk size
std::array<GLuint, 432> computeIndices(const int squareLength) {
    std::array<GLuint, 432> indices{};

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

    std::cout << "-----------------------------INDICIES-----------------" << std::endl;
    for (const auto indicy: indices) {
        std::cout << indicy << ", ";
    }
    std::cout << "----------------------------------------------------" << std::endl;

    return indices;
}
