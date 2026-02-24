#pragma once

#include "fui/node/FJ_FuiNode.h"
#include "types.h"

struct fuiRenderNodeEditText;

class FJ_Base : public FJ_FuiNode {
public:
    ~FJ_Base() override;
    int getType() override;
    virtual bool getLabelTooWide();
    virtual int getOldWidth();
    virtual void SetLabel(const std::wstring&);
    virtual void GetLabelTooWide(fuiRenderNodeEditText*);
    virtual void SetNewObjectWidth(int);
    virtual void SetNewObjectHeight(int);  // this doesn't seem to exist on WiiU, why would they add it on
                                           // switch (and probably XB1 as they are on the same branch)
    virtual void HandleCharInput(uint);

    void* getObjListParent();
    int getId();

    char m_padding[0x60];
    int m_id;
    char m_padding3[0x5b];
    bool m_labelTooWide;
    char m_padding2[0x34];
    void* m_objListParent;
};
