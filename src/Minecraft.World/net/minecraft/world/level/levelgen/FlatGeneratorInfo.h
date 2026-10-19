#pragma once

#include "net/minecraft/world/level/levelgen/FlatLayerInfo.h"
#include <vector>

class SuperflatConfig;
class LargeCaveFeature;
class CanyonFeature;
class StructureFeature;
class OceanMonumentFeature;
class LakeFeature;

class FlatGeneratorInfo {
public:
    FlatGeneratorInfo(SuperflatConfig*);
    ~FlatGeneratorInfo();
    LargeCaveFeature* getCaves();
    CanyonFeature* getCanyons();
    bool hasVillage();
    StructureFeature* getVillage(int);
    bool hasBiomeSpecific();
    StructureFeature* getBiomeSpecific();
    bool hasMineshaft();
    StructureFeature* getMineshaft();
    bool hasStronghold();
    StructureFeature* getStronghold();
    bool hasOceanMonument();
    OceanMonumentFeature* getOceanMonument();
    bool hasWoodlandMansion();
    bool hasDecorations();
    bool hasDungeons();
    LakeFeature* getLakes();
    LakeFeature* getLavaLakes();
    void getLayers(const BlockState**);
    void getLayers(std::vector<FlatLayerInfo>&);

private:
    char m_storage[0x20];
};

static_assert(sizeof(FlatGeneratorInfo) == 0x20, "FlatGeneratorInfo ABI");
