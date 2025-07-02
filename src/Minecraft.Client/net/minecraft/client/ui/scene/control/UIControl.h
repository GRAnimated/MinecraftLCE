#pragma once
#include <string>

class UIScene;
class fuiRenderNode;

class UIControl {
public:
    enum eUIControlType {};

    UIControl();

    virtual ~UIControl();
    virtual bool setupControl(UIScene*, fuiRenderNode*, const std::string&);
    virtual void UpdateControl();
    virtual void tick();
    virtual void ReInit();
    virtual void setFocus(bool);
    virtual bool hasFocus();

    int getControlID() {
        return mControlID;
    }  // not sure if it should be here or _Base as UIScene::hasControlFocus passes _Base for whatever
       // reason...

    void setSettedUp(int val) { this->mSettedUp = val; }
    void setVisible(bool);

    int mSettedUp;  // not sure
    int mControlID;
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
    bool mBoolIdk2;
};