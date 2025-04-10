#pragma once
#include <string>

class UIScene;
class fuiRenderNode;

class UIControl {
public:
    UIControl();

    virtual ~UIControl();
    virtual bool setupControl(UIScene*, fuiRenderNode*, std::string const&);
    virtual void UpdateControl();
    virtual void tick();
    virtual void ReInit();
    virtual void setFocus();
    virtual bool hasFocus();

    int mIntIdk;
    int mIntIdk2;
    bool mBoolIdk;
    char fill[0x7];
    std::string mName;
    fuiRenderNode* mFuiRenderNode;
    UIScene* mParentUIScene;
    float mPosX;
    float mPosY;
    float mWidth;
    float mHeight;
    float mOpacity;
    bool mVisible;
};