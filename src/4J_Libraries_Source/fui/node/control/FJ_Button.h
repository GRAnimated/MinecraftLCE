#pragma once

#include "4J_Libraries_Source/fui/node/FJ_Base.h"

class FJ_Button : public FJ_Base {
public:
    virtual ~FJ_Button() override;
    virtual void SetLabel(std::wstring const&) override;
    virtual void GetLabelTooWide(fuiRenderNodeEditText*) override;
    virtual void Init(std::wstring const&, int);
    virtual void ChangeState(int);
    virtual void UpdateLabel();
    virtual void EnableButton(bool);
};