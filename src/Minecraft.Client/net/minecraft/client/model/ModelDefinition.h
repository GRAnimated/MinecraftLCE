#pragma once

#include "net/minecraft/client/model/ModelPartDefinition.h"
#include <string>
#include <unordered_map>

class ModelDefinition {
public:
    ModelDefinition();

    bool DoesOverrideModel() const;

    bool mOverrideModel;
    int dword4;
    int dword8;
    std::unordered_map<std::wstring, ModelPartDefinition> mPartsDef;
};
