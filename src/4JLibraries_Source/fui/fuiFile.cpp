#include "fui/fuiFile.h"
#include "fui/node/FJ_FuiNode.h"

// NON_MATCHING | Score: 550 (lower is better)
// Meth. Dunno what to do here...
// addr 710048EE20
void fuiMatrix::mul(const fuiMatrix& lhs, const fuiMatrix& rhs, fuiMatrix& out) {
    out.mScaleX
        = lhs.mScaleX * rhs.mScaleX + lhs.mScaleY * rhs.mRotSkewX + static_cast<float>(rhs.mPosX * 0.0);
    out.mScaleY
        = lhs.mScaleX * rhs.mScaleY + lhs.mScaleY * rhs.mRotSkewY + static_cast<float>(rhs.mPosY * 0.0);
    out.mRotSkewX
        = lhs.mRotSkewX * rhs.mScaleX + lhs.mRotSkewY * rhs.mRotSkewX + static_cast<float>(rhs.mPosX * 0.0);
    out.mRotSkewY
        = lhs.mRotSkewX * rhs.mScaleY + lhs.mRotSkewY * rhs.mRotSkewY + static_cast<float>(rhs.mPosY * 0.0);
    out.mPosX = rhs.mPosX + (lhs.mPosX * rhs.mScaleX + lhs.mPosY * rhs.mRotSkewX);
    out.mPosY = rhs.mPosY + (lhs.mPosX * rhs.mScaleY + lhs.mPosY * rhs.mRotSkewY);
}

fuiFile::fuiFile() {
    this->mHeader.index = 0;
    this->mData.fuiSymbol = nullptr;
    this->mData.fuiImportAsset = nullptr;
    this->mRenderNodeStage = nullptr;
    this->mCallbackData = nullptr;
}

// NON_MATCHING | Score: 10 (lower is better)
// 2 registers were swapped...
uint64_t fuiFile::addDataRegion(uint a1, unsigned int size, unsigned char** data, uint64_t* callbackData) {
    if (!size)
        return 0;

    const uint64_t res = *callbackData;
    *callbackData += size * reinterpret_cast<uint64_t>(data);
    return res;
}

fuiRenderNode* fuiFile::getRootNode() {
    return (fuiRenderNode*)this->mRenderNodeTimeline;  // ??? (I think our structs are fucked)
}

// NON_MATCHING | score: 10 (lower is better)
// can also get it to match by swapping the params and using mRootNode in place of mCallbackData, but that's
// not correct surely
void fuiFile::setCustomDrawCallback(void (*callback)(void*, const char*, fuiRect*), void* data) {
    this->mCallbackData = data;
    this->mCallbackFunc = callback;
}

float fuiFile::getStageWidth() {
    return this->mHeader.stageSize.getWidth();
}

float fuiFile::getStageHeight() {
    return this->mHeader.stageSize.getHeight();
}

void fuiFile::setIndex(int index) {
    this->mHeader.index = index;
}
