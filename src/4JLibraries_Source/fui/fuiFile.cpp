#include "fui/fuiFile.h"

#include "NX/Render/RendererCore.h"
#include "fui/fui.h"
#include "fui/fuiRenderNodeStage.h"

#include <cstring>

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
    this->m_renderNodeStage = nullptr;
    this->m_renderNodeTimeline = nullptr;
    this->m_callbackFunc = nullptr;
    this->m_field138 = nullptr;
}

// NON_MATCHING | score: 10 (lower is better)
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

/** Reads fourteen serialized tables followed by encoded images; excludes runtime pointers. */
// NON_MATCHING | score: 8880 (lower is better)
bool fuiFile::load(arrayWithLength<uchar> bytes, int resolution) {
    std::memcpy(&m_header, bytes.m_data, 0x98);
    m_field138 = nullptr;
    const fuiHeader& header = m_header;
    if (static_cast<uint64_t>(bytes.m_length)
        != static_cast<uint64_t>(static_cast<unsigned int>(header.m_contentSize)) + 0x98u)
        return false;

    m_field138 = new unsigned char[m_header.m_contentSize];
    std::memcpy(m_field138, bytes.m_data + 0x98, m_header.m_contentSize);
    m_field9C = resolution;
    uint64_t cursor = reinterpret_cast<uint64_t>(m_field138);
    auto take = [&cursor](int count, size_t stride) -> void* {
        // The original helper treats its third argument as an integer stride.
        return reinterpret_cast<void*>(
            fuiFile::addDataRegion(0, count, reinterpret_cast<unsigned char**>(stride), &cursor));
    };
    m_data.m_timeline = static_cast<fuiTimeline*>(take(m_header.m_timelineCount, 0x1c));
    m_data.m_timelineAction = static_cast<fuiTimelineAction*>(take(m_header.m_timelineActionCount, 0x84));
    m_data.m_shape = static_cast<fuiShape*>(take(m_header.m_shapeCount, 0x1c));
    m_data.m_shapeComponent = static_cast<fuiShapeComponent*>(take(m_header.m_shapeComponentCount, 0x2c));
    m_data.m_vert = static_cast<fuiVert*>(take(m_header.m_vertCount, 8));
    m_data.m_timelineFrame = static_cast<fuiTimelineFrame*>(take(m_header.m_timelineFrameCount, 0x48));
    m_data.m_timelineEvent = static_cast<fuiTimelineEvent*>(take(m_header.m_timelineEventCount, 0x48));
    if (!m_header.m_signature[0]) {
        // 0x7100489ff8: v0 -> v1 only changes the fourth event byte to one.
        for (int i = 0; i < m_header.m_timelineEventCount; ++i)
            m_data.m_timelineEvent[i].m_flags = 1;
    }
    m_data.m_timelineEventName
        = static_cast<timelineEventName*>(take(m_header.m_timelineEventNameCount, 0x40));
    m_data.m_fuiReference = static_cast<fuiReference*>(take(m_header.m_referenceCount, 0x48));
    m_data.m_fuiEdittext = static_cast<fuiEdittext*>(take(m_header.m_editTextCount, 0x138));
    m_data.m_fuiFontName = static_cast<fuiFontName*>(take(m_header.m_fontNameCount, 0x104));
    m_data.m_fuiSymbol = static_cast<fuiSymbol*>(take(m_header.m_symbolCount, 0x48));
    m_data.m_fuiImportAsset = static_cast<fuiImportAsset*>(take(m_header.m_importAssetCount, 0x40));
    m_data.m_fuiBitmap = static_cast<fuiBitmap*>(take(m_header.m_bitmapCount, 0x20));
    m_data.m_imageMaybe = reinterpret_cast<void*>(cursor);
    m_renderNodeTimeline = nullptr;
    return true;
}

/** Returns true while serialized references remain unresolved. */
// NON_MATCHING | score: 5485 (lower is better)
bool fuiFile::resolveReferences(fuiFile* imported) {
    if (!m_data.m_fuiReference)
        return false;
    if (imported->m_field9C != m_field9C || imported->m_renderNodeStage)
        return true;
    bool unresolved = false;
    for (int i = 0; i < m_header.m_referenceCount; ++i) {
        fuiReference& reference = m_data.m_fuiReference[i];
        if (reference.m_symbolIndex != -1)
            continue;
        for (int j = 0; j < imported->m_header.m_symbolCount; ++j) {
            const bool equal = std::strcmp(imported->m_data.m_fuiSymbol[j].m_name, reference.m_name) == 0;
            if (equal) {
                reference.m_index = imported->m_header.m_index;
                reference.m_symbolIndex = j;
                break;
            }
        }
        unresolved |= reference.m_symbolIndex == -1;
    }
    return unresolved;
}

/** Releases the render tree, managed textures and serialized tables, in that order. */
// NON_MATCHING | score: 2405 (lower is better)
fuiFile::~fuiFile() {
    delete m_renderNodeStage;
    for (int i = 0; i < m_header.m_bitmapCount; ++i) {
        fuiBitmap* bitmap = m_data.m_fuiBitmap + i;
        if (bitmap->m_texture) {
            if (bitmap->m_texture > 0)
                Renderer::sInstance->TextureFree(bitmap->m_texture);
            fui::sInstance->removeManagedTexture(this, bitmap);
        }
    }
    delete[] static_cast<unsigned char*>(m_field138);
}
