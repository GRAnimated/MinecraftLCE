#include "net/minecraft/client/ui/scene/control/UIControl.h"

#include "fui/fuiRenderNode.h"
#include "fui/node/FJ_FuiNodeStage.h"

UIControl::UIControl() {
    this->m_parentUiScene = nullptr;
    this->m_opacity = 1.0f;
    this->m_name = "";
    this->m_visible = true;
    this->m_boolIdk = 0;
    this->m_settedUp = 0;
    this->m_fuiRenderNode = nullptr;
}

UIControl::~UIControl() {}

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

// name guessed
fuiRenderNode* UIControl::getFuiRenderNode() {
    return m_fuiRenderNode;
}

float UIControl::getXPos() {
    return m_posX;
}

float UIControl::getYPos() {
    return m_posY;
}

// name guessed
float UIControl::getWidth() {
    return m_width;
}

// name guessed
float UIControl::getHeight() {
    return m_height;
}

// name guessed
void UIControl::setWidth(float width) {
    if (m_fuiRenderNode) {
        m_fuiRenderNode->setWidth(width);
        m_width = width;
    }
}

void UIControl::setVisible(bool visible) {
    if (m_fuiRenderNode) {
        if (m_fuiRenderNode->m_fuiNodeStage)
            m_fuiRenderNode->m_fuiNodeStage->setVisible(visible);
        else
            m_fuiRenderNode->setVisibility(visible);
        m_visible = visible;
    }
}

// name guessed
// NON_MATCHING | score: 5 (lower is better)
bool UIControl::getVisible() {
    bool visible = false;
    if (m_fuiRenderNode)
        visible = m_fuiRenderNode->isVisible();
    m_visible = visible;
    return visible;
}

void UIControl::removeUINodeRef() {
    m_fuiRenderNode = nullptr;
}
