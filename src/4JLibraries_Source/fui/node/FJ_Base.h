#pragma once

#include "fui/node/FJ_FuiNode.h"
#include "types.h"

class fuiRenderNodeEditText;

class FJ_Base : public FJ_FuiNode {
    ~FJ_Base() override;
    int getType() override;
    virtual void getLabelTooWide();
    virtual unsigned int getOldWidth();
    virtual void SetLabel(const std::wstring&);
    virtual void GetLabelTooWide(fuiRenderNodeEditText*);
    virtual void SetNewObjectWidth(int);
    virtual void SetNewObjectHeight(int);  // this doesn't seem to exist on WiiU, why would they add it on
                                           // switch (and probably XB1 as they are on the same branch)
    virtual void HandleCharInput(uint);
};
