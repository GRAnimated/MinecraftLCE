#include "4JLibraries_Source/fui/fuiRenderNodeStage.h"

float fuiRenderNodeStage::getStageHeight() {
    return this->field_58->getStageHeight();
}

float fuiRenderNodeStage::getStageWidth() {
    return this->field_58->getStageWidth();
}

void fuiRenderNodeStage::addChild(fuiRenderNode* node) {
    this->child = node;
}

fuiRenderNodeStage::fuiRenderNodeStage(fuiFile* file)
    : fuiRenderNode(nullptr, nullptr, nullptr, 0, RENDER_NODE_STAGE, 0, nullptr, 0, false, file) {
    this->child = nullptr;
}
