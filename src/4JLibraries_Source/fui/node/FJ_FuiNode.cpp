#include "fui/node/FJ_FuiNode.h"

#include "control/button/FJ_Button.h"
#include "control/list/FJ_List.h"
#include "control/list/button/FJ_List_ListButton.h"
#include "control/list/button/menubutton/FJ_List_MenuButton.h"
#include "control/list/button/playerlist/FJ_List_ListButtonPlayerList.h"
#include "document/FJ_Document.h"
#include "fui/fui.h"
#include "fui/fuiRenderNode.h"
#include "fui/node/FJ_Base.h"
#include "fui/node/FJ_FuiNodeStage.h"

ADD_CREATOR(FJ_FuiNode)

FJ_FuiNode::FJ_FuiNode(fuiRenderNode* renderNode) {
    m_tabIndex = -1;
    m_renderNode = renderNode;
    m_callbackScene = nullptr;
}

FJ_FuiNode::~FJ_FuiNode() {
    fui::sInstance->removeEventListenerForNode(this);
    if (m_renderNode && m_renderNode->m_stage) {
        getStage()->removeFocus(this);
    }
}

void FJ_FuiNode::ASConstructor() {}

void FJ_FuiNode::setX(float x) {
    this->m_renderNode->setX(x);
}

void FJ_FuiNode::setY(float y) {
    this->m_renderNode->setY(y);
}

void FJ_FuiNode::setHeight(float height) {
    this->m_renderNode->setHeight(height);
}

void FJ_FuiNode::setVisible(bool visible) {
    this->m_renderNode->setVisibility(visible);
}

int FJ_FuiNode::getType() {
    return 0;
}

void FJ_FuiNode::setScaleX(float sX) {
    this->m_renderNode->setScaleX(sX);
}

void FJ_FuiNode::setScaleY(float sY) {
    this->m_renderNode->setScaleY(sY);
}
float FJ_FuiNode::getWidth() {
    return this->m_renderNode->getWidth();
}

float FJ_FuiNode::getHeight() {
    return this->m_renderNode->getHeight();
}

void FJ_FuiNode::setWidth(float width) {
    this->m_renderNode->setWidth(width);
}

int FJ_FuiNode::getTabIndex() {
    return m_tabIndex;
}

FJ_FuiNodeStage* FJ_FuiNode::getStage() {
    return m_renderNode->getStage()->m_fuiNodeStage;
}

void FJ_FuiNode::setCallbackScene(UIScene* scene) {
    m_callbackScene = scene;
}

FJ_Base* FJ_FuiNode::asFJ_Base() {
    return dynamic_cast<FJ_Base*>(this);
}

FJ_Document* FJ_FuiNode::asFJ_Document() {
    return dynamic_cast<FJ_Document*>(this);
}

FJ_List* FJ_FuiNode::asFJ_List() {
    return dynamic_cast<FJ_List*>(this);
}

FJ_List_ListButton* FJ_FuiNode::asFJ_List_ListButton() {
    return dynamic_cast<FJ_List_ListButton*>(this);
}

FJ_List_ListButtonPlayerList* FJ_FuiNode::asFJ_List_ListButtonPlayerList() {
    return dynamic_cast<FJ_List_ListButtonPlayerList*>(this);
}

FJ_List_MenuButton* FJ_FuiNode::asFJ_List_MenuButton() {
    return dynamic_cast<FJ_List_MenuButton*>(this);
}

FJ_Button* FJ_FuiNode::asFJ_Button() {
    return dynamic_cast<FJ_Button*>(this);
}

void* FJ_FuiNode::asMovieClip() {
    if (this->m_renderNode->m_fuiObjectType != eFuiObjectType_Timeline)
        return nullptr;

    return this;
}

bool FJ_FuiNode::isFJ_Document() {
    return this->asFJ_Document() != nullptr;
}
