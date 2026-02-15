#include "fui/fuiFile.h"
#include "fui/node/FJ_FuiNode.h"

void fuiMatrix::mul(const fuiMatrix& lhs, const fuiMatrix& rhs, fuiMatrix& out) {
    out.m_scaleX
        = lhs.m_scaleX * rhs.m_scaleX + lhs.m_scaleY * rhs.m_rotSkewX + static_cast<float>(rhs.m_posX * 0.0);
    out.m_scaleY
        = lhs.m_scaleX * rhs.m_scaleY + lhs.m_scaleY * rhs.m_rotSkewY + static_cast<float>(rhs.m_posY * 0.0);
    out.m_rotSkewX = lhs.m_rotSkewX * rhs.m_scaleX + lhs.m_rotSkewY * rhs.m_rotSkewX
                     + static_cast<float>(rhs.m_posX * 0.0);
    out.m_rotSkewY = lhs.m_rotSkewX * rhs.m_scaleY + lhs.m_rotSkewY * rhs.m_rotSkewY
                     + static_cast<float>(rhs.m_posY * 0.0);
    out.m_posX = lhs.m_posX * rhs.m_scaleX + lhs.m_posY * rhs.m_rotSkewX + rhs.m_posX;
    out.m_posY = lhs.m_posX * rhs.m_scaleY + lhs.m_posY * rhs.m_rotSkewY + rhs.m_posY;
}

fuiFile::fuiFile() {
    this->m_header.m_index = 0;
    this->m_data.m_fuiSymbol = nullptr;
    this->m_data.m_fuiImportAsset = nullptr;
    this->m_renderNodeStage = nullptr;
    this->m_callbackData = nullptr;
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
    return (fuiRenderNode*)this->m_renderNodeTimeline;  // ??? (I think our structs are fucked)
}

// NON_MATCHING | score: 10 (lower is better)
// can also get it to match by swapping the params and using mRootNode in place of mCallbackData, but that's
// not correct surely
void fuiFile::setCustomDrawCallback(void (*callback)(void*, const char*, fuiRect*), void* data) {
    this->m_callbackData = data;
    this->m_callbackFunc = callback;
}

float fuiFile::getStageWidth() {
    return this->m_header.m_stageSize.getWidth();
}

float fuiFile::getStageHeight() {
    return this->m_header.m_stageSize.getHeight();
}

void fuiFile::setIndex(int index) {
    this->m_header.m_index = index;
}
