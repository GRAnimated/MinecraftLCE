#include "4JLibraries_Source/fui/fuiRenderNode.h"

#include "4JLibraries_Source/fui/fuiRenderNodeTimeline.h"
#include "4JLibraries_Source/fui/node/FJ_FuiNodeStage.h"
#include <cmath>

void fuiRenderNode::setScaleX(float sX) {
    float scaleX = sX / this->getScaleX();

    this->mMatrix.mScaleX = this->mMatrix.mScaleX * scaleX;
    this->mMatrix.mRotSkewX = scaleX * this->mMatrix.mRotSkewX;

    this->generateGlobalMatrix();
    this->progogateBounds();
}

void fuiRenderNode::setScaleY(float sY) {
    float scaleY = sY / this->getScaleY();

    this->mMatrix.mScaleY = this->mMatrix.mScaleY * scaleY;
    this->mMatrix.mRotSkewY = scaleY * this->mMatrix.mRotSkewY;

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
    return sqrtf((this->mMatrix.mScaleY * this->mMatrix.mScaleY)
                 + (this->mMatrix.mRotSkewY * this->mMatrix.mRotSkewY));
}

fuiRenderNodeTimeline* fuiRenderNode::asTimeline() {
    if (this->field_20 != 2)  // is field_20 type?
        return nullptr;

    return reinterpret_cast<fuiRenderNodeTimeline*>(this);
}

float fuiRenderNode::getScaleX() {
    return sqrtf((this->mMatrix.mScaleX * this->mMatrix.mScaleX)
                 + (this->mMatrix.mRotSkewX * this->mMatrix.mRotSkewX));
}

float fuiRenderNode::getX() {
    return this->mMatrix.mPosX;
}

void fuiRenderNode::setX(float x) {
    this->mMatrix.mPosX = x;
    this->generateGlobalMatrix();
    this->progogateBounds();
}

float fuiRenderNode::getY() {
    return this->mMatrix.mPosY;
}

void fuiRenderNode::setY(float y) {
    this->mMatrix.mPosY = y;
    this->generateGlobalMatrix();
    this->progogateBounds();
}

void fuiRenderNode::shutdown() {};

void fuiRenderNode::disableCtor() {
    this->mFlags &= ~FLAG_CTOR_ENABLED;
}

void fuiRenderNode::setAlpha(float a) {
    this->mAlpha = a;
}

void fuiRenderNode::setVisibility(bool visible) {
    if (visible)
        this->mFlags |= FLAG_NODE_VISIBLE;
    else
        this->mFlags &= ~FLAG_NODE_VISIBLE;
}

bool fuiRenderNode::isVisible() {
    return this->mFlags & FLAG_NODE_VISIBLE;
}

void fuiRenderNode::handleAddedToStage() {
    if (this->mFuiNodeStage) {
        this->mFuiNodeStage->dispatchEvent(new FJ_Event(eFJEventType::ADDED_TO_STAGE, false, false));
    }
}

fuiRenderNode* fuiRenderNode::getNodeFromPath(const char* path) {
    bool diff = strcmp(this->mPath, path) == 0 || strcmp(path, DEFAULT_PATH) == 0;
    return diff ? this : nullptr;
}

fuiRenderNode* fuiRenderNode::findNode(const char* name) {
    if (strlen(name))
        return nullptr;

    return this;
}

void fuiRenderNode::progogateBounds() {
    // get timeline
    if (fuiRenderNode* tl = this->mTimeline) {
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
    rect->minX = this->mRect.minX * this->mMatrix.mScaleX + this->mMatrix.mPosX;
    rect->maxX = this->mRect.maxX * this->mMatrix.mScaleX + this->mMatrix.mPosX;
    rect->minY = this->mRect.minY * this->mMatrix.mRotSkewY + this->mMatrix.mPosY;
    rect->maxY = this->mRect.maxY * this->mMatrix.mRotSkewY + this->mMatrix.mPosY;
}

void fuiRenderNode::generateGlobalMatrix() {
    const fuiRenderNode* tl = this->mTimeline;

    if (tl) {
        this->mMatrix2 = this->mMatrix * tl->mMatrix2;
    } else {
        this->mMatrix2 = this->mMatrix;
    }
}
FJ_FuiNode* fuiRenderNode::Create(fuiRenderNode* node) {
    return new FJ_FuiNode(node);
}
