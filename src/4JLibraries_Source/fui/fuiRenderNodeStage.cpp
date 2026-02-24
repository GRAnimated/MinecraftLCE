#include "fui/fuiRenderNodeStage.h"

float fuiRenderNodeStage::getStageHeight() {
    return this->m_fuiFile->getStageHeight();
}

float fuiRenderNodeStage::getStageWidth() {
    return this->m_fuiFile->getStageWidth();
}

void fuiRenderNodeStage::addChild(fuiRenderNode* node) {
    this->m_child = node;
}

fuiRenderNodeStage::fuiRenderNodeStage(fuiFile* file)
    : fuiRenderNode(nullptr, nullptr, nullptr, 0, eFuiObjectType_Stage, 0, nullptr, 0, false, file) {
    this->m_child = nullptr;
}
