#include "fui/fuiRenderNode.h"

#include "fui/fuiRenderNodeTimeline.h"
#include "fui/node/FJ_FuiNodeStage.h"
#include <cmath>

fuiMatrix fuiRenderNode::GLOBAL_MATRIX = {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
fuiRenderNodeColor fuiRenderNode::DEFAULT_COLORS[2] = {{1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}};

fuiRenderNode::fuiRenderNode(fuiRenderNode* stage, fuiRenderNode* timeline, fuiObject* fuiObject,
                             unsigned int a5, eFuiObjectType fuiObjectType, unsigned char a7, fuiRGBA* color,
                             unsigned char a9, bool a10, fuiFile* fuiFile) {
    this->m_stage = stage;
    this->m_timeline = (fuiRenderNodeTimeline*)timeline;
    this->m_fuiObject = fuiObject;
    this->m_fuiObjectType = fuiObjectType;
    this->m_dword10 = a5;
    this->m_fuiFile = fuiFile;
    this->m_matrix = GLOBAL_MATRIX;
    this->generateGlobalMatrix();
    this->m_renderColor = DEFAULT_COLORS[1];
    this->m_renderColor2 = DEFAULT_COLORS[0];
    this->m_flags = 75;

    this->m_byteC = a7 & 3;

    if (color) {
        this->m_color = color->m_color;
#ifdef MATCHING_HACK
        asm("");
#endif
    } else {
        this->m_color = 0;
    }

    this->m_byteE4 = a9 ? a9 : 1;

    if (a10)
        this->m_flags = 0x14B;

    this->m_path[0] = '\0';  // null termination, I don't like that
    this->m_fuiNodeStage = nullptr;
    this->m_byteD = a7 & 0xF0;
    this->m_dword14 = 0;
    this->m_rect = {0.0f, 0.0f, 0.0f, 0.0f};
    this->m_qwordD0 = nullptr;
    this->m_qwordD8 = nullptr;
}

void fuiRenderNode::setScaleX(float sX) {
    float scaleX = sX / this->getScaleX();

    this->m_matrix.m_scaleX = this->m_matrix.m_scaleX * scaleX;
    this->m_matrix.m_rotSkewX = scaleX * this->m_matrix.m_rotSkewX;

    this->generateGlobalMatrix();
    this->progogateBounds();
}

void fuiRenderNode::setScaleY(float sY) {
    float scaleY = sY / this->getScaleY();

    this->m_matrix.m_scaleY = this->m_matrix.m_scaleY * scaleY;
    this->m_matrix.m_rotSkewY = scaleY * this->m_matrix.m_rotSkewY;

    this->generateGlobalMatrix();
    this->progogateBounds();
}

void fuiRenderNode::setWidth(float w) {
    float cW = this->getWidth();
    float sX = this->getScaleX();

    if (w > 0.0f)
        this->setScaleX(sX * (w / cW));
    if (this->getWidth() != w)
        this->getWidth();
}

void fuiRenderNode::setHeight(float h) {
    const float cH = this->getHeight();
    if (h > 0.0f) {
        const float v5 = h / cH;
        this->setScaleY(v5 * this->getScaleY());
    }
}

float fuiRenderNode::getScaleY() {
    return sqrtf((this->m_matrix.m_scaleY * this->m_matrix.m_scaleY)
                 + (this->m_matrix.m_rotSkewY * this->m_matrix.m_rotSkewY));
}

fuiRenderNodeTimeline* fuiRenderNode::asTimeline() {
    if (this->m_fuiObjectType != eFuiObjectType_Timeline)
        return nullptr;

    return reinterpret_cast<fuiRenderNodeTimeline*>(this);
}

float fuiRenderNode::getScaleX() {
    return sqrtf((this->m_matrix.m_scaleX * this->m_matrix.m_scaleX)
                 + (this->m_matrix.m_rotSkewX * this->m_matrix.m_rotSkewX));
}

float fuiRenderNode::getX() {
    return this->m_matrix.m_posX;
}

void fuiRenderNode::setX(float x) {
    this->m_matrix.m_posX = x;
    this->generateGlobalMatrix();
    this->progogateBounds();
}

float fuiRenderNode::getY() {
    return this->m_matrix.m_posY;
}

void fuiRenderNode::setY(float y) {
    this->m_matrix.m_posY = y;
    this->generateGlobalMatrix();
    this->progogateBounds();
}

void fuiRenderNode::shutdown() {};

void fuiRenderNode::disableCtor() {
    this->m_flags &= ~FLAG_CTOR_ENABLED;
}

void fuiRenderNode::setAlpha(float a) {
    this->m_renderColor.m_a = a;
}

void fuiRenderNode::setVisibility(bool visible) {
    if (visible)
        this->m_flags |= FLAG_NODE_VISIBLE;
    else
        this->m_flags &= ~FLAG_NODE_VISIBLE;
}

bool fuiRenderNode::isVisible() {
    return this->m_flags & FLAG_NODE_VISIBLE;
}

void fuiRenderNode::handleAddedToStage() {
    if (this->m_fuiNodeStage) {
        this->m_fuiNodeStage->dispatchEvent(new FJ_Event(eFJEventType::ADDED_TO_STAGE, false, false));
    }
}

fuiRenderNode* fuiRenderNode::getNodeFromPath(const char* path) {
    bool diff = strcmp(this->m_path, path) == 0 || strcmp(path, DEFAULT_PATH) == 0;
    return diff ? this : nullptr;
}

fuiRenderNode* fuiRenderNode::findNode(const char* name) {
    if (strlen(name))
        return nullptr;

    return this;
}

void fuiRenderNode::progogateBounds() {
    // get timeline
    if (fuiRenderNode* tl = this->m_timeline) {
        // make sure it's a timeline(???)
        if (fuiRenderNodeTimeline* tl2 = tl->asTimeline())
            tl2->progogateBoundsFromChild();
    }
}

float fuiRenderNode::getWidth() {
    fuiRect rect;
    this->getParentSpaceBounds(&rect);
    return rect.getWidth();
}

float fuiRenderNode::getHeight() {
    fuiRect rect;
    this->getParentSpaceBounds(&rect);
    return rect.getHeight();
}

void fuiRenderNode::getParentSpaceBounds(fuiRect* rect) {
    rect->m_inX = this->m_rect.m_inX * this->m_matrix.m_scaleX + this->m_matrix.m_posX;
    rect->m_axX = this->m_rect.m_axX * this->m_matrix.m_scaleX + this->m_matrix.m_posX;
    rect->m_inY = this->m_rect.m_inY * this->m_matrix.m_rotSkewY + this->m_matrix.m_posY;
    rect->m_axY = this->m_rect.m_axY * this->m_matrix.m_rotSkewY + this->m_matrix.m_posY;
}

void fuiRenderNode::generateGlobalMatrix() {
    const fuiRenderNode* tl = this->m_timeline;

    if (tl) {
        this->m_matrix2 = this->m_matrix * tl->m_matrix2;
    } else {
        this->m_matrix2 = this->m_matrix;
    }
}
FJ_FuiNode* fuiRenderNode::Create(fuiRenderNode* node) {
    return new FJ_FuiNode(node);
}
