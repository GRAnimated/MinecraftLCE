#include "net/minecraft/client/ui/scene/control/UIControl.h"

#include "fui/fuiRenderNode.h"

UIControl::UIControl() {
    this->m_parentUiScene = nullptr;
    this->m_opacity = 1.0f;
    this->m_name = "";
    this->m_visible = true;
    this->m_boolIdk = 0;
    this->m_settedUp = 0;
    this->m_fuiRenderNode = nullptr;
}

bool UIControl::setupControl(UIScene* parentUIScene, fuiRenderNode* renderNode, const std::string& name) {
    this->m_parentUiScene = parentUIScene;
    this->m_name = name;
    this->m_fuiRenderNode = renderNode->findNode(name.c_str());

    if (this->m_fuiRenderNode) {
        this->m_posX = this->m_fuiRenderNode->getX();
        this->m_posY = this->m_fuiRenderNode->getY();
        this->m_width = this->m_fuiRenderNode->getWidth();
        this->m_height = this->m_fuiRenderNode->getHeight();
    }

    return this->m_fuiRenderNode != nullptr;
}

void UIControl::UpdateControl() {
    if (this->m_fuiRenderNode) {
        this->m_posX = this->m_fuiRenderNode->getX();
        this->m_posY = this->m_fuiRenderNode->getY();
        this->m_width = this->m_fuiRenderNode->getWidth();
        this->m_height = this->m_fuiRenderNode->getHeight();
    }
}

void UIControl::tick() {}

void UIControl::ReInit() {
    if (this->m_fuiRenderNode) {
        this->m_fuiRenderNode->setAlpha(this->m_opacity);
        this->m_fuiRenderNode->setVisibility(this->m_visible);
    }
}

void UIControl::setFocus(bool) {}

bool UIControl::hasFocus() {
    return false;
}
