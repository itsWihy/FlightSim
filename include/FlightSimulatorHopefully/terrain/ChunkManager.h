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

    friend std::ostream& operator<<(std::ostream& os, const ChunkCoords& chunk_coords)   {
        return os << chunk_coords.x << " " << chunk_coords.z;
    }
};

struct ChunkCoordsHasher {
    std::size_t operator()(const ChunkCoords &chunkCoords) const {
        return chunkCoords.x + chunkCoords.z * INT16_MAX;
    }
};

class ChunkManager {
private:
    constexpr static std::array<GLuint, 432> indicesPrecomputed = {0, 1, 9, 1, 10, 9, 1, 2, 10, 2, 11, 10, 2, 3, 11, 3, 12, 11, 3, 4, 12, 4, 13, 12, 4, 5, 13, 5, 14, 13, 5, 6, 14, 6, 15, 14, 6, 7, 15, 7, 16, 15, 7, 8, 16, 8, 17, 16, 0, 0, 0, 0, 0, 0, 9, 10, 18, 10, 19, 18, 10, 11, 19, 11, 20, 19, 11, 12, 20, 12, 21, 20, 12, 13, 21, 13, 22, 21, 13, 14, 22, 14, 23, 22, 14, 15, 23, 15, 24, 23, 15, 16, 24, 16, 25, 24, 16, 17, 25, 17, 26, 25, 0, 0, 0, 0, 0, 0, 18, 19, 27, 19, 28, 27, 19, 20, 28, 20, 29, 28, 20, 21, 29, 21, 30, 29, 21, 22, 30, 22, 31, 30, 22, 23, 31, 23, 32, 31, 23, 24, 32, 24, 33, 32, 24, 25, 33, 25, 34, 33, 25, 26, 34, 26, 35, 34, 0, 0, 0, 0, 0, 0, 27, 28, 36, 28, 37, 36, 28, 29, 37, 29, 38, 37, 29, 30, 38, 30, 39, 38, 30, 31, 39, 31, 40, 39, 31, 32, 40, 32, 41, 40, 32, 33, 41, 33, 42, 41, 33, 34, 42, 34, 43, 42, 34, 35, 43, 35, 44, 43, 0, 0, 0, 0, 0, 0, 36, 37, 45, 37, 46, 45, 37, 38, 46, 38, 47, 46, 38, 39, 47, 39, 48, 47, 39, 40, 48, 40, 49, 48, 40, 41, 49, 41, 50, 49, 41, 42, 50, 42, 51, 50, 42, 43, 51, 43, 52, 51, 43, 44, 52, 44, 53, 52, 0, 0, 0, 0, 0, 0, 45, 46, 54, 46, 55, 54, 46, 47, 55, 47, 56, 55, 47, 48, 56, 48, 57, 56, 48, 49, 57, 49, 58, 57, 49, 50, 58, 50, 59, 58, 50, 51, 59, 51, 60, 59, 51, 52, 60, 52, 61, 60, 52, 53, 61, 53, 62, 61, 0, 0, 0, 0, 0, 0, 54, 55, 63, 55, 64, 63, 55, 56, 64, 56, 65, 64, 56, 57, 65, 57, 66, 65, 57, 58, 66, 58, 67, 66, 58, 59, 67, 59, 68, 67, 59, 60, 68, 60, 69, 68, 60, 61, 69, 61, 70, 69, 61, 62, 70, 62, 71, 70, 0, 0, 0, 0, 0, 0, 63, 64, 72, 64, 73, 72, 64, 65, 73, 65, 74, 73, 65, 66, 74, 66, 75, 74, 66, 67, 75, 67, 76, 75, 67, 68, 76, 68, 77, 76, 68, 69, 77, 69, 78, 77, 69, 70, 78, 70, 79, 78, 70, 71, 79, 71, 80, 79};
    static Mesh generateChunkFromCoords(int chunkX, int chunkZ);

    constexpr static int CHUNK_LENGTH = 8;

    //All generated chunks
    std::unordered_map<ChunkCoords, Mesh, ChunkCoordsHasher> cachedChunks;

public:
    constexpr static double degToRad = std::numbers::pi / 180;

    void renderNearChunks(const Shader &shader, const Camera &camera);
};

#endif //CHUNKMANAGER_H
