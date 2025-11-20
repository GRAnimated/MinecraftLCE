#pragma once

#include "fui/node/FJ_FuiNode.h"

class FJ_Document : public FJ_FuiNode {
public:
    virtual void init(FJ_Event*);
    virtual void SetSafeZone(int, int, int, int);
    virtual void handlePress(FJ_Event*);
    virtual void keyDownHandler(FJ_Event*);
    virtual void OnFocusChange(bool);
    virtual void DoHorizontalResizeCheck();
};
