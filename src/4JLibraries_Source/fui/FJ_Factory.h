#pragma once
#include "fuiRenderNode.h"
#include "unordered_map"

class FJ_FuiNode;
class FJ_Factory {
#define ADD_NODE(n) sNodes.emplace(std::make_pair(std::string(n::sName), &n::Create))

    static void initialise();

    static std::unordered_map<std::string, FJ_FuiNode* (*)(fuiRenderNode*)> sNodes;
};
