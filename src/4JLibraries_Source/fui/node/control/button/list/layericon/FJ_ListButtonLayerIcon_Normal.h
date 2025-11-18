#pragma once

#include "4JLibraries_Source/fui/node/control/button/list/layericon/FJ_ListButtonLayerIcon.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_ListButtonLayerIcon_Normal : public FJ_ListButtonLayerIcon {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
