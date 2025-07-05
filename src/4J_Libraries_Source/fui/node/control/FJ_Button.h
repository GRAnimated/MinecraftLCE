#pragma once

#include "4J_Libraries_Source/fui/node/FJ_Base.h"

class FJ_Button : public FJ_Base {
public:
    virtual ~FJ_Button() override;
    virtual void SetLabel(const std::wstring&) override;
    virtual void GetLabelTooWide(fuiRenderNodeEditText*) override;
    virtual void Init(const std::wstring&, int);
    virtual void ChangeState(int);
    virtual void UpdateLabel();
    virtual void EnableButton(bool);
};