#include "fuiRenderNodeStage.h"

float fuiRenderNodeStage::getStageHeight() {
    return this->mFuiFile->getStageHeight();
}

float fuiRenderNodeStage::getStageWidth() {
    return this->mFuiFile->getStageWidth();
}

void fuiRenderNodeStage::addChild(fuiRenderNode* node) {
    this->child = node;
}

fuiRenderNodeStage::fuiRenderNodeStage(fuiFile* file)
    : fuiRenderNode(nullptr, nullptr, nullptr, 0, eFuiObjectType_Stage, 0, nullptr, 0, false, file) {
    this->child = nullptr;
}
