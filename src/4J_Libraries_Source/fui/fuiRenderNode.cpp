#include "cmath"
#include "fuiRenderNode.h"
#include "fuiRenderNodeTimeline.h"

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

float fuiRenderNode::getScaleY() {
    return sqrtf((this->mMatrix.mScaleY * this->mMatrix.mScaleY) + (this->mMatrix.mRotSkewY * this->mMatrix.mRotSkewY));
}

fuiRenderNodeTimeline* fuiRenderNode::asTimeline() {
    if ( this->field_20 != 2 ) // is field_20 type?
        return nullptr;

    return reinterpret_cast<fuiRenderNodeTimeline*>(this);
}

float fuiRenderNode::getScaleX() {
    return sqrtf((this->mMatrix.mScaleX * this->mMatrix.mScaleX) + (this->mMatrix.mRotSkewX * this->mMatrix.mRotSkewX));
}

float fuiRenderNode::getX() {
    return this->mMatrix.mPosX;
}

float fuiRenderNode::getY() {
    return this->mMatrix.mPosY;
}

void fuiRenderNode::disableCtor() {
    this->dword_8 &= ~1;
}

fuiRenderNode *fuiRenderNode::findNode(char const* name)
{
    if (strlen(name)) return nullptr;

    return this;
}

void fuiRenderNode::progogateBounds()
{

    // get timeline
    if (fuiRenderNode* tl = this->mTimeline)
    {
        // make sure it's a timeline
        if (fuiRenderNodeTimeline* tl2 = tl->asTimeline()) tl2->progogateBoundsFromChild();
    }
}

void fuiRenderNode::generateGlobalMatrix() {
    const fuiRenderNode* tl = this->mTimeline;

    if (tl) {
        this->mMatrix2 = this->mMatrix * tl->mMatrix2;
    } else {
        this->mMatrix2 = this->mMatrix;
    }
}
