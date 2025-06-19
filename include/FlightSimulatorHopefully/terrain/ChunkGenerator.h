//
// Created by Wihy on 6/18/25.
//

#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H
#include "../Mesh.h"
#include "FractalNoise.h"

//Takes the fractal noise thing
//generates vertices and indices.
// displays?

class ChunkGenerator {
    Mesh chunkMesh;
    
    void generateMesh() {
        std::array<Vertex, 64> vertices{};

        for (int i = 0; i < 64; ++i) {
            const glm::vec3 position {i % 8, fractalNoise(i % 8, i / 8), i / 8};

            vertices[i] = Vertex(position, {1,1,1});
        }
    ////TODO: Use templates so arrays could also be passed in here. Just then complete this program.
        chunkMesh = {vertices, {}};

    }
};

#endif //CHUNKGENERATOR_H
