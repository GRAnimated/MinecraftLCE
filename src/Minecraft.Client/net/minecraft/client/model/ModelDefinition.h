#pragma once

#include "net/minecraft/client/model/ModelPartDefinition.h"
#include <string>
#include <unordered_map>

class ModelDefinition {
public:
    ModelDefinition();

    bool DoesOverrideModel() const;

    bool m_overrideModel;
    int m_dword4;
    int m_dword8;
    std::unordered_map<std::wstring, ModelPartDefinition> m_partsDef;
};
