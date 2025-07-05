#pragma once

#include "fui/node/FJ_FuiNode.h"
#include "types.h"

class fuiRenderNodeEditText;

class FJ_Base : public FJ_FuiNode {
public:
    ~FJ_Base() override;
    int getType() override;
    virtual bool getLabelTooWide();
    virtual int getOldWidth();
    virtual void SetLabel(std::wstring const&);
    virtual void GetLabelTooWide(fuiRenderNodeEditText*);
    virtual void SetNewObjectWidth(int);
    virtual void SetNewObjectHeight(int);  // this doesn't seem to exist on WiiU, why would they add it on
                                           // switch (and probably XB1 as they are on the same branch)
    virtual void HandleCharInput(uint);

    void *getObjListParent();
    int getId();

    char padding[0x60];
    int mId;
    char padding3[0x5b];
    bool mLabelTooWide;
    char padding2[0x34];
    void *mObjListParent;
};
