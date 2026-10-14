#include "fui/fuiRenderNode.h"
#include "fui/node/FJ_FuiNodeStage.h"

// 0x710048a3dc: the wrapper belongs to the render node.
fuiRenderNode::~fuiRenderNode() {
    delete m_fuiNodeStage;
    m_fuiNodeStage = nullptr;
}
