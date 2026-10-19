#pragma once

#include "net/minecraft/world/level/levelgen/feature/LargeFeature.h"
#include "types.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class BlockPos;
class ChunkPos;
class StructureFeatureSavedData;
class StructureStart;

class StructureFeature : public LargeFeature {
public:
    StructureFeature();
    ~StructureFeature() override;
    void addFeature(Level*, int, int, int, int, ChunkPrimer*) override;
    virtual std::wstring getFeatureName() = 0;
    virtual bool postProcess(Level*, Random&, ChunkPos*);
    virtual bool isIntersection(int, int);
    virtual bool isInsideFeature(const BlockPos&);
    virtual BlockPos* getNearestGeneratedFeature(Level*, const BlockPos&, bool) = 0;
    virtual std::vector<BlockPos>* getGuesstimatedFeaturePositions();
    virtual void restoreSavedData(Level*);
    virtual void saveFeature(int, int, StructureStart*);
    virtual bool isFeatureChunk(int, int, bool) = 0;
    virtual StructureStart* createStructureStart(int, int) = 0;

    StructureStart* getStructureAt(const BlockPos&);
    bool isInsideBoundingFeature(Level*, const BlockPos&);
    static BlockPos* findNearestFeaturePositionBySpacing(Level*, StructureFeature*, const BlockPos&,
                                                         int spacing, int separation, int salt, bool linear,
                                                         int maxRadius, bool skipKnown);

    std::shared_ptr<StructureFeatureSavedData> m_savedData;
    std::unordered_map<long long, StructureStart*> m_starts;
};

ASSERT_SIZEOF(StructureFeature, 0x68)
