#include "4JLibraries_Source/fui/node/FJ_FuiNodeStage.h"

#include "4JLibraries_Source/fui/event/FJ_FocusEvent.h"
#include "4JLibraries_Source/fui/fuiRenderNodeStage.h"

float FJ_FuiNodeStage::getStageWidth() {
    return static_cast<fuiRenderNodeStage*>(this->mRenderNode)->getStageWidth();
}

float FJ_FuiNodeStage::getStageHeight() {
    return static_cast<fuiRenderNodeStage*>(this->mRenderNode)->getStageHeight();
}

void FJ_FuiNodeStage::setFocus(FJ_FuiNode* node) {
    FJ_FuiNode* focused = this->mFocusedNode;

    // if what's already focused isn't anything and also isn't already the node
    // then we dispatch an event
    if (focused != node && focused)
        focused->dispatchEvent(new FJ_FocusEvent(false, false, false));

    // set our node to the new node
    this->mFocusedNode = node;

    // dispatch an event on the new node
    if (node)
        node->dispatchEvent(new FJ_FocusEvent(true, false, false));
}

FJ_FuiNode* FJ_FuiNodeStage::getFocus() {
    // return focused node if available
    if (this->mFocusedNode != nullptr)
        return this->mFocusedNode;

    // otherwise we return ourselves (?????)
    return this;
}

void FJ_FuiNodeStage::removeFocus(FJ_FuiNode* node) {
    if (this->mFocusedNode == node)
        this->mFocusedNode = nullptr;
}
