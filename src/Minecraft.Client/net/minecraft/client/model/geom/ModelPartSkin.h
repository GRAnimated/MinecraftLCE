#pragma once

#include "net/minecraft/client/model/geom/ModelPart.h"

#include "net/minecraft/client/model/ModelDefinition.h"

class ModelPartsSkinned;

class ModelPartSkin : public ModelPart {
public:
    ModelPartSkin(Model*, const std::wstring&, const ModelDefinition&, ModelPart*, float, ModelPartsSkinned*);
    ModelPartSkin(Model*, int xTexOffs, int yTexOffs);
    ModelPartSkin(Model*, int xTexOffs, int yTexOffs, ModelPartsSkinned*);

    char m_fill[0x10];
};
