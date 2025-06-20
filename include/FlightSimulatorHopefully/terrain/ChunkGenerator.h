//
// Created by Wihy on 6/18/25.
//

#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H
#include "../rendering/Mesh.h"
#include "FractalNoise.h"

//Takes the fractal noise thing
//generates vertices and indices.
// displays?

class ChunkGenerator {
    Mesh chunkMesh;

public:
    explicit ChunkGenerator();

    void drawChunk(const Shader& shader, const Camera& camera) const;
};

#endif //CHUNKGENERATOR_H
