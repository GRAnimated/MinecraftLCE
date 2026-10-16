#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/block/LogBlock.h"
#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"
#include <vector>

class BigTreeFeature : public AbstractTreeFeature {
public:
    class FoliageCoords : public BlockPos {
    public:
        FoliageCoords(const BlockPos&, int branchBase);
        int getBranchBase();

    private:
        int m_branchBase;
    };

    BigTreeFeature(bool update);
    ~BigTreeFeature() override;
    bool place(Level*, Random&, const BlockPos&) override;
    void init() override;

    void prepare();
    float treeShape(int height);
    int checkLine(const BlockPos&, const BlockPos&);
    void crossection(const BlockPos&, float radius, const BlockState*);
    float foliageShape(int height);
    void foliageCluster(const BlockPos&);
    void limb(const BlockPos&, const BlockPos&, Block*);
    int getSteps(const BlockPos&);
    LogBlock::LogAxis* getLogAxis(const BlockPos&, const BlockPos&);
    void makeFoliage();
    bool trimBranches(int height);
    void makeTrunk();
    void makeBranches();
    bool checkLocation();

private:
    Random m_random;                       // 0x28
    Level* m_level;                        // 0x40
    BlockPos m_origin;                     // 0x48
    int m_height;                          // 0x54
    int m_trunkHeight;                     // 0x58
    double m_heightAttenuation;            // 0x60
    double m_branchSlope;                  // 0x68
    double m_scaleWidth;                   // 0x70
    double m_leafDensity;                  // 0x78
    int m_trunkWidth;                      // 0x80
    int m_heightLimit;                     // 0x84
    int m_foliageHeight;                   // 0x88
    std::vector<FoliageCoords> m_foliage;  // 0x90
};

ASSERT_SIZEOF(BigTreeFeature::FoliageCoords, 0x10)
ASSERT_SIZEOF(BigTreeFeature, 0xa8)
