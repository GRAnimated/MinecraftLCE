#include "fui/fuiRenderNodeTimeline.h"

#include <cstring>

void fuiRenderNodeTimeline::progogateBoundsFromChild() {
    fuiRenderNodeTimeline* cur = this;

    do {
        cur->updateBoundsLocal();

        fuiRenderNode* tl = cur->m_timeline;

        if (!tl)
            break;

        cur = tl->asTimeline();
    } while (cur);
}

// 0x710048f040. A timeline object is a serialized fuiTimeline record.
// NON_MATCHING | score: 620 (lower is better)
fuiRenderNodeTimeline::fuiRenderNodeTimeline(fuiRenderNode* stage, fuiRenderNode* parent, fuiObject* object,
                                             unsigned int depth, unsigned char flags, fuiRGBA* colour,
                                             unsigned char alpha, bool blend, fuiFile* file)
    : fuiRenderNode(stage, parent, object, depth, eFuiObjectType_Timeline, flags, colour, alpha, blend, file),
      m_mask(nullptr), m_frame(-1), m_nextFrame(0) {
    const int initialFlags = m_flags;
    m_flags = initialFlags | 4;
    if (object) {
        const fuiRect& rect = reinterpret_cast<fuiTimeline*>(object)->m_rect;
        if (rect.m_inX != 0 || rect.m_axX != 0 || rect.m_inY != 0 || rect.m_axY != 0)
            m_flags = initialFlags | 0x24;
    }
}

fuiRenderNodeTimeline::~fuiRenderNodeTimeline() {
    for (unsigned int i = 0; i < m_children.size(); ++i)
        delete m_children[i];
    delete m_mask;
}

void fuiRenderNodeTimeline::shutdown() {
    for (unsigned int i = 0; i < m_children.size(); ++i)
        m_children[i]->shutdown();
}

// name guessed
void fuiRenderNodeTimeline::preRender() {
    if (isVisible()) {
        for (unsigned int i = 0; i < m_children.size(); ++i)
            m_children[i]->preRender();
    }
}

void fuiRenderNodeTimeline::handleAddedToStage() {
    fuiRenderNode::handleAddedToStage();
    for (unsigned int i = 0; i < m_children.size(); ++i)
        m_children[i]->handleAddedToStage();
}

fuiRenderNode* fuiRenderNodeTimeline::findNode(const char* name) {
    for (unsigned int i = 0; i < m_children.size(); ++i) {
        if (fuiRenderNode* node = m_children[i]->getNodeFromPath(name))
            return node;
    }
    return nullptr;
}

fuiRenderNode* fuiRenderNodeTimeline::getNodeFromPath(const char* path) {
    const char* end = path;
    while (*end && *end != '.')
        ++end;
    if (!*end)
        return fuiRenderNode::getNodeFromPath(path);
    if (std::strncmp(m_path, path, end - path) == 0) {
        for (unsigned int i = 0; i < m_children.size(); ++i) {
            if (fuiRenderNode* node = m_children[i]->getNodeFromPath(end + 1))
                return node;
        }
    }
    return nullptr;
}

void fuiRenderNodeTimeline::generateGlobalMatrix() {
    fuiRenderNode::generateGlobalMatrix();
    for (size_t i = 0; i < m_children.size(); ++i)
        m_children[i]->generateGlobalMatrix();
}

// name guessed
void fuiRenderNodeTimeline::setPlaying(bool playing) {
    if (playing) {
        m_flags |= 6;
    } else {
        m_flags &= ~4;
        if (!(m_flags & 0x10))
            m_nextFrame = m_frame;
    }
}

// name guessed
// NON_MATCHING | score: 25 (lower is better)
void fuiRenderNodeTimeline::setFrame(unsigned int frame) {
    m_flags |= 0x12;
    unsigned int last = reinterpret_cast<fuiTimeline*>(m_fuiObject)->m_frameCount - 1u;
    m_nextFrame = frame - 1u <= last ? frame - 1u : last;
}

// NON_MATCHING | score: 1365 (lower is better)
void fuiRenderNodeTimeline::expandBoundsFromChild(fuiRect& rect) {
    // Original MI selects retain the current bits for equal or unordered bounds.
    m_rect.m_inX = *(rect.m_inX < m_rect.m_inX ? &rect.m_inX : &m_rect.m_inX);
    m_rect.m_axX = *(m_rect.m_axX < rect.m_axX ? &rect.m_axX : &m_rect.m_axX);
    m_rect.m_inY = *(rect.m_inY < m_rect.m_inY ? &rect.m_inY : &m_rect.m_inY);
    m_rect.m_axY = *(m_rect.m_axY < rect.m_axY ? &rect.m_axY : &m_rect.m_axY);
}

void fuiRenderNodeTimeline::updateBoundsLocal() {
    for (unsigned int i = 0; i < m_children.size(); ++i) {
        fuiRect rect;
        m_children[i]->getParentSpaceBounds(&rect);
        if (i == 0)
            m_rect = rect;
        else
            expandBoundsFromChild(rect);
    }
}
