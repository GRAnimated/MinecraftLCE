#include "fui/fuiFile.h"
#include <cstring>

// Reconstructed from 0x7100487eec. The file contains fourteen consecutive
// tables followed by encoded images; runtime pointers are never serialized.
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

// Reconstructed from 0x71004881a4. true means references remain unresolved.
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
