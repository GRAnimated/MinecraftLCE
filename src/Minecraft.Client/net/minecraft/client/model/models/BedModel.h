#pragma once

#include "net/minecraft/client/model/Model.h"
#include "net/minecraft/client/model/ModelDefinition.h"

class BedModel : public Model {
public:
    BedModel(const ModelDefinition&);

    void render(bool);  // this is what 4J done :)

    std::wstring getName() override;

    ModelPartSkin* m_bedPart;
    ModelPartSkin* m_legPart;
};
