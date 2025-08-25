#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"
#include "types.h"

class BlockPos;
class ChunkPos;
class StructureStart;

class StructureFeature : public LargeFeature {
public:
    virtual std::wstring getFeatureName();
    virtual bool postProcess(Level*, Random&, ChunkPos*);
    virtual bool isIntersection(int, int);
    virtual bool isInsideFeature(const BlockPos&);
    virtual BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool);
    virtual void getGuesstimatedFeaturePositions();
    virtual void restoreSavedData(Level*);
    virtual void saveFeature(int, int, StructureStart*);
    virtual bool isFeatureChunk(int, int, bool);
    virtual void createStructureStart(int, int);

    char filler[0x38];

    bool isInsideBoundingFeature(Level*, const BlockPos&);
};

ASSERT_SIZEOF(StructureFeature, 0x68)
