//
// Created by Wihy on 6/10/25.
//

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H
#include <map>

#include "Chunk.h"
#include "../Camera.h"


// has list of chunks. vector.


//private: Generate Chunks in view.
//(hash)Map so no extra generation accidentally
// If chunk exists, but point is NOT in view, remove chunk from vector.
// TODO: Figure out how to know what is in view
// TODO: Figure out coordinate space system to properly use view knowledge in order to place chunks correctly

//public:
// has a renderNearChunks function
class ChunkManager {
    const Mesh& chunkMesh;
    std::vector<Chunk> currentChunks;

public:
    ChunkManager(const Mesh& chunkMesh);

    void renderNearChunks(const Shader &shader, const Camera &camera);
};

#endif //CHUNKMANAGER_H
