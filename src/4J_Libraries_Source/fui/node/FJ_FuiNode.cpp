#include "4J_Libraries_Source/fui/node/FJ_FuiNode.h"

#include "4J_Libraries_Source/fui/fui.h"
#include "4J_Libraries_Source/fui/fuiRenderNode.h"
#include "4J_Libraries_Source/fui/node/FJ_FuiNodeStage.h"

FJ_FuiNode::FJ_FuiNode(fuiRenderNode* renderNode) {
    mTabIndex = -1;
    this->mRenderNode = renderNode;
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
    mRenderNode->setX(x);
}

void FJ_FuiNode::setY(float y) {
    mRenderNode->setY(y);
}

void FJ_FuiNode::setHeight(float height) {
    mRenderNode->setHeight(height);
}

void FJ_FuiNode::setVisible(bool visible) {
    mRenderNode->setVisibility(visible);
}

int FJ_FuiNode::getType() {
    return 0;
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
