#pragma once

#include <vector>

#include "net/minecraft/client/model/geom/ModelPartSkin.h"

class ModelPartsSkinned {
public:
    int dword0;
    bool byte4;
    std::vector<ModelPartSkin*> mModelParts;
    void* qword20;
};
