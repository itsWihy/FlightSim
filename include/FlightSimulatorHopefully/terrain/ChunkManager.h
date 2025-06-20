//
// Created by Wihy on 6/10/25.
//

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include <map>

#include "Chunk.h"
#include "../Camera.h"
#include "FractalNoise.h"

class ChunkManager {
private:
    constexpr static int CHUNK_LENGTH = 8;

    std::vector<Chunk> currentChunks;

    Mesh generateChunkFromCoords(int chunkX, int chunkZ);

public:
    void renderNearChunks(const Shader &shader, const Camera &camera);
};

#endif //CHUNKMANAGER_H
