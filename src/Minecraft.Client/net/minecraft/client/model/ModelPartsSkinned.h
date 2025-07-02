#pragma once

#include <vector>

#include "Minecraft.World/entity/model/ModelPart.h"

class ModelPartSkin : public ModelPart {};

class ModelPartsSkinned {
public:
    int dword0;
    bool byte4;
    std::vector<ModelPartSkin*> mModelParts;
    void* qword20;
};