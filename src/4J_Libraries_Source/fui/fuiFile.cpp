#include "fuiFile.h"

// NON_MATCHING | Score: 550 (lower is better)
// Meth. Dunno what to do here...
// addr 710048EE20
void fuiMatrix::mul(const fuiMatrix& lhs, const fuiMatrix& rhs, fuiMatrix& out) {
    out.mScaleX = lhs.mScaleX * rhs.mScaleX + lhs.mScaleY * rhs.mRotSkewX
                       + static_cast<float>(rhs.mPosX * 0.0);
    out.mScaleY = lhs.mScaleX * rhs.mScaleY + lhs.mScaleY * rhs.mRotSkewY
                 + static_cast<float>(rhs.mPosY * 0.0);
    out.mRotSkewX = lhs.mRotSkewX * rhs.mScaleX + lhs.mRotSkewY * rhs.mRotSkewX
                   + static_cast<float>(rhs.mPosX * 0.0);
    out.mRotSkewY = lhs.mRotSkewX * rhs.mScaleY + (float)(lhs.mRotSkewY * rhs.mRotSkewY)
                   + static_cast<float>(rhs.mPosY * 0.0);
    out.mPosX = rhs.mPosX + (lhs.mPosX * rhs.mScaleX + lhs.mPosY * rhs.mRotSkewX);
    out.mPosY = rhs.mPosY + (lhs.mPosX * rhs.mScaleY + lhs.mPosY * rhs.mRotSkewY);
}

float fuiFile::getStageWidth() {
    return this->mHeader.stageSize.getWidth();
}

float fuiFile::getStageHeight() {
    return this->mHeader.stageSize.getHeight();
}