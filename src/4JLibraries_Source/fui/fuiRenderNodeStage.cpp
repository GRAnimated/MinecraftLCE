#include "fui/fuiRenderNodeStage.h"

#include <type_traits>

float fuiRenderNodeStage::getStageHeight() {
    return this->m_fuiFile->getStageHeight();
}

// name guessed
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

// 0x710048ef74. The matching runtime requires an attached child before teardown.
fuiRenderNodeStage::~fuiRenderNodeStage() {
    m_child->shutdown();
    delete m_child;
}

/** Virtual slots 3, 4, 5 and 7 of the original stage vtable.
 */
// name guessed
void fuiRenderNodeStage::gather(bool advance) {
    m_child->gather(advance);
}

// name guessed
void fuiRenderNodeStage::preRender() {
    m_child->preRender();
}

// name guessed
void fuiRenderNodeStage::render(fuiRect* clip, fuiMatrix* matrix) {
    m_child->render(clip, matrix);
}

// name guessed
fuiRenderNode* fuiRenderNodeStage::findNode(const char* name) {
    return m_child->findNode(name);
}

static_assert(!std::is_abstract<fuiRenderNodeStage>::value, "The original FUI stage must be instantiable");
