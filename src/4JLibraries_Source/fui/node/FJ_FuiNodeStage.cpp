#include "fui/node/FJ_FuiNodeStage.h"

#include "fui/event/FJ_FocusEvent.h"
#include "fui/fuiRenderNodeStage.h"

float FJ_FuiNodeStage::getStageWidth() {
    return static_cast<fuiRenderNodeStage*>(this->m_renderNode)->getStageWidth();
}

float FJ_FuiNodeStage::getStageHeight() {
    return static_cast<fuiRenderNodeStage*>(this->m_renderNode)->getStageHeight();
}

void FJ_FuiNodeStage::setFocus(FJ_FuiNode* node) {
    FJ_FuiNode* focused = this->m_focusedNode;

    // if what's already focused isn't anything and also isn't already the node
    // then we dispatch an event
    if (focused != node && focused)
        focused->dispatchEvent(new FJ_FocusEvent(false, false, false));

    // set our node to the new node
    this->m_focusedNode = node;

    // dispatch an event on the new node
    if (node)
        node->dispatchEvent(new FJ_FocusEvent(true, false, false));
}

FJ_FuiNode* FJ_FuiNodeStage::getFocus() {
    // return focused node if available
    if (this->m_focusedNode != nullptr)
        return this->m_focusedNode;

    // otherwise we return ourselves (?????)
    return this;
}

void FJ_FuiNodeStage::removeFocus(FJ_FuiNode* node) {
    if (this->m_focusedNode == node)
        this->m_focusedNode = nullptr;
}
