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
        return m_controlId;
    }  // not sure if it should be here or _Base as UIScene::hasControlFocus passes _Base for whatever
       // reason...

    fuiRenderNode* getFuiRenderNode();
    void setSettedUp(int val) { this->m_settedUp = val; }
    void setVisible(bool);
    float getWidth();
    float getHeight();
    float getXPos();
    float getYPos();

    int m_settedUp;  // not sure
    int m_controlId;
    bool m_boolIdk;
    char m_fill[0x7];
    std::string m_name;
    fuiRenderNode* m_fuiRenderNode;
    UIScene* m_parentUiScene;
    float m_posX;
    float m_posY;
    float m_width;
    float m_height;
    float m_opacity;
    bool m_visible;
    bool m_boolIdk2;
};
