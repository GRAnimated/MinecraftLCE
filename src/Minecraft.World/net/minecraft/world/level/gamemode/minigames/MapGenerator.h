#pragma once

#include "net/minecraft/world/Random.h"
#include <vector>

class Level;
class AABB;
class GenerationWriteTask;

class MapGenerator {
public:
    MapGenerator(Random random);

    virtual ~MapGenerator();
    virtual void StartGeneration(Level* level) = 0;
    virtual const AABB* GetSpawnArea() const = 0;
    virtual void CleanUp(Level* level) = 0;
    virtual const AABB* GetLayerBB(unsigned int layer) = 0;
    virtual unsigned int GetNumberOfLayers() = 0;
    virtual void GetLayerExtents(unsigned int layer, float*, float*) = 0;
    virtual int GetBlockCountOnLayer(unsigned int layer);

    Random m_random;
    std::vector<GenerationWriteTask*> m_genTasks;
};
