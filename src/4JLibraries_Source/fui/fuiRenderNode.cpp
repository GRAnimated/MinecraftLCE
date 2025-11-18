#include "4JLibraries_Source/fui/fuiRenderNode.h"

#include "4JLibraries_Source/fui/fuiRenderNodeTimeline.h"
#include "4JLibraries_Source/fui/node/FJ_FuiNodeStage.h"
#include <cmath>

fuiMatrix fuiRenderNode::GLOBAL_MATRIX = {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
fuiRenderNodeColor fuiRenderNode::DEFAULT_COLORS[2] = {{1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}};

fuiRenderNode::fuiRenderNode(fuiRenderNode* stage, fuiRenderNode* timeline, fuiObject* fuiObject,
                             unsigned int a5, eFuiObjectType fuiObjectType, unsigned char a7, fuiRGBA* color,
                             unsigned char a9, bool a10, fuiFile* fuiFile) {
    this->mStage = stage;
    this->mTimeline = (fuiRenderNodeTimeline*)timeline;
    this->mFuiObject = fuiObject;
    this->mFuiObjectType = fuiObjectType;
    this->dword_10 = a5;
    this->mFuiFile = fuiFile;
    this->mMatrix = GLOBAL_MATRIX;
    this->generateGlobalMatrix();
    this->mRenderColor = DEFAULT_COLORS[1];
    this->mRenderColor2 = DEFAULT_COLORS[0];
    this->mFlags = 75;

    this->byte_c = a7 & 3;

    if (color) {
        this->mColor = color->color;
#ifdef MATCHING_HACK
        asm("");
#endif
    } else {
        this->mColor = 0;
    }

    this->byte_e4 = a9 ? a9 : 1;

    if (a10)
        this->mFlags = 0x14B;

    this->mPath[0] = '\0';  // null termination, I don't like that
    this->mFuiNodeStage = nullptr;
    this->byte_d = a7 & 0xF0;
    this->dword_14 = 0;
    this->mRect = {0.0f, 0.0f, 0.0f, 0.0f};
    this->qword_d0 = nullptr;
    this->qword_d8 = nullptr;
}

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
    if (this->mFuiObjectType != eFuiObjectType_Timeline)
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
    this->mRenderColor.a = a;
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
