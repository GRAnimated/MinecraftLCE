#include "fui/fuiRenderNodeStage.h"
#include <type_traits>

// 0x710048ef74. The matching runtime requires an attached child before teardown.
fuiRenderNodeStage::~fuiRenderNodeStage() {
    m_child->shutdown();
    delete m_child;
}

// Virtual slots 3, 4, 5 and 7 of the original stage vtable.
void fuiRenderNodeStage::gather(bool advance) {
    m_child->gather(advance);
}

void fuiRenderNodeStage::preRender() {
    m_child->preRender();
}

void fuiRenderNodeStage::render(fuiRect* clip, fuiMatrix* matrix) {
    m_child->render(clip, matrix);
}

fuiRenderNode* fuiRenderNodeStage::findNode(const char* name) {
    return m_child->findNode(name);
}

static_assert(!std::is_abstract<fuiRenderNodeStage>::value, "The original FUI stage must be instantiable");
