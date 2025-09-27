#pragma once

#include "FJ_BeaconEffectButton.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_BeaconEffectButton_Small : public FJ_BeaconEffectButton {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
