#pragma once

#include <vector>

#include "net/minecraft/client/model/geom/ModelPartSkin.h"

class ModelPartsSkinned {
public:
    int m_dword0;
    bool m_byte4;
    std::vector<ModelPartSkin*> m_modelParts;
    void* m_qword20;
};
