#pragma once

#include "fui/fuiRenderNode.h"
#include "unordered_map"

class FJ_FuiNode;
class FJ_Factory {
    static void initialise();

    static std::unordered_map<std::string, FJ_FuiNode* (*)(fuiRenderNode*)> sNodes;
};
