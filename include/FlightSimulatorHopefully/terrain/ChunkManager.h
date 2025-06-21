//
// Created by Wihy on 6/10/25.
//

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include <map>
#include <unordered_map>

#include "Chunk.h"
#include "../Camera.h"
#include "FractalNoise.h"

struct ChunkCoords {
    int x;
    int z;

    bool operator==(const ChunkCoords &chunk_coords) const {
        return chunk_coords.x == x && chunk_coords.z == z;
    }
};

struct ChunkCoordsHasher {
    std::size_t operator()(const ChunkCoords &chunkCoords) const {
        return chunkCoords.x + chunkCoords.z * INT16_MAX;
    }
};

class ChunkManager {
private:
    static Mesh generateChunkFromCoords(int chunkX, int chunkZ);

    constexpr static int CHUNK_LENGTH = 8;

    //All generated chunks
    std::unordered_map<ChunkCoords, Mesh, ChunkCoordsHasher> cachedChunks;

public:
    void renderNearChunks(const Shader &shader, const Camera &camera);
};

#endif //CHUNKMANAGER_H
