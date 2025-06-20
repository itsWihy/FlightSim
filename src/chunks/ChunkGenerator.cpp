//
// Created by Wihy on 6/20/25.
//

#include "../../include/FlightSimulatorHopefully/terrain/ChunkGenerator.h"

Mesh generateMesh();

ChunkGenerator::ChunkGenerator() : chunkMesh(generateMesh()) {
}

void ChunkGenerator::drawChunk(const Shader &shader, const Camera &camera) const {
    chunkMesh.draw(shader, camera, {0, -1, 15}, {0, 0, 0});
}

Mesh generateMesh() {
    constexpr float noiseScalar = 0.1f;

    constexpr int squareLength = 8;

    std::array<Vertex, squareLength*squareLength> vertices{};
    std::array<GLuint, 330> indices{};

    for (int i = 0; i < ssize(vertices); ++i) {
        const int x = i / squareLength;
        const int z = i % squareLength;

        const float height = fractalNoise(noiseScalar * x, noiseScalar * z);

        vertices[i] = {{x, 1.9 * height, z}, {0.3 * height, 0.5 * height, 0.1 * height}};
    }

    int currentSquare = 0;

    for (int index = 0; index < ssize(indices); index +=6) {
        if (index + 5 > ssize(indices)) break;

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
