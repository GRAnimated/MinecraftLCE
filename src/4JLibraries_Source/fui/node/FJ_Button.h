#pragma once

#include "fui/node/FJ_Base.h"

class FJ_Button : public FJ_Base {
public:
    ~FJ_Button() override;
    void SetLabel(const std::wstring&) override;
    void GetLabelTooWide(fuiRenderNodeEditText*) override;
    virtual void Init(const std::wstring&, int);
    virtual void ChangeState(int);
    virtual void UpdateLabel();
    virtual void EnableButton(bool);
};
