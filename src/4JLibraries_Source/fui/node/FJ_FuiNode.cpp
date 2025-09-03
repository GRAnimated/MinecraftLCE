#include "fui/node/FJ_FuiNode.h"

#include "control/FJ_List.h"
#include "fui/fui.h"
#include "fui/fuiRenderNode.h"
#include "fui/node/FJ_Base.h"
#include "fui/node/FJ_Document.h"
#include "fui/node/FJ_FuiNodeStage.h"
#include "fui/node/control/FJ_Button.h"
#include "fui/node/control/FJ_List_ListButton.h"
#include "fui/node/control/FJ_List_ListButtonPlayerList.h"
#include "fui/node/control/FJ_List_MenuButton.h"

FJ_FuiNode::FJ_FuiNode(fuiRenderNode* renderNode) {
    mTabIndex = -1;
    mRenderNode = renderNode;
    mCallbackScene = nullptr;
}

FJ_FuiNode::~FJ_FuiNode() {
    fui::sInstance->removeEventListenerForNode(this);
    if (mRenderNode && mRenderNode->mStage) {
        getStage()->removeFocus(this);
    }
}

void FJ_FuiNode::ASConstructor() {}

void FJ_FuiNode::setX(float x) {
    this->mRenderNode->setX(x);
}

void FJ_FuiNode::setY(float y) {
    this->mRenderNode->setY(y);
}

void FJ_FuiNode::setHeight(float height) {
    this->mRenderNode->setHeight(height);
}

void FJ_FuiNode::setVisible(bool visible) {
    this->mRenderNode->setVisibility(visible);
}

int FJ_FuiNode::getType() {
    return 0;
}

void FJ_FuiNode::setScaleX(float sX) {
    this->mRenderNode->setScaleX(sX);
}

void FJ_FuiNode::setScaleY(float sY) {
    this->mRenderNode->setScaleY(sY);
}
float FJ_FuiNode::getWidth() {
    return this->mRenderNode->getWidth();
}

float FJ_FuiNode::getHeight() {
    return this->mRenderNode->getHeight();
}

void FJ_FuiNode::setWidth(float width) {
    this->mRenderNode->setWidth(width);
}

int FJ_FuiNode::getTabIndex() {
    return mTabIndex;
}

FJ_FuiNodeStage* FJ_FuiNode::getStage() {
    return mRenderNode->getStage()->mFuiNodeStage;
}

void FJ_FuiNode::setCallbackScene(UIScene* scene) {
    mCallbackScene = scene;
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
    if (this->mRenderNode->field_20 != eFuiObjectType_2)
        return nullptr;

    return this;
}

bool FJ_FuiNode::isFJ_Document() {
    return this->asFJ_Document() != nullptr;
}
