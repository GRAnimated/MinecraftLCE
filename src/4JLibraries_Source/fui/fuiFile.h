#pragma once

#include "fui/fuiSymbol.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"
#include <cstddef>

// Most structs derived from
// https://github.com/NessieHax/fui-research-repo/blob/main/DOCUMENTATION.md

class fuiRenderNode;
struct fuiBitmapFont;
struct fuiRenderNodeStage;
struct fuiRenderNodeTimeline;
struct fuiRect {
    float m_inX;
    float m_axX;
    float m_inY;
    float m_axY;

    // getHeight?
    float getHeight() { return this->m_axY - this->m_inY; }

    // getWidth?
    float getWidth() { return this->m_axX - this->m_inX; }
};
struct fuiRGBA {
    int m_color;  // RGBA
};
struct fuiMatrix {
    float m_scaleX;
    float m_scaleY;
    float m_rotSkewX;
    float m_rotSkewY;
    float m_posX;
    float m_posY;

    // spent an hour trying to figure out what this was
    // finally thought of it being a built in C++ operator... which looks good to me.
    // NON_MATCHING | score: 205 (lower is better)
    fuiMatrix operator*(const fuiMatrix& rhs) const {
        fuiMatrix out = {};
        mul(*this, rhs, out);

        return out;
    }

    static void mul(const fuiMatrix& lhs, const fuiMatrix& rhs, fuiMatrix& out);
};
struct fuiColorTransform {
    float m_redAddTerm;
    float m_greenAddTerm;
    float m_blueAddTerm;
    float m_alphaAddTerm;
    float m_redMultTerm;
    float m_greenMultTerm;
    float m_blueMultTerm;
    float m_alphaMultTerm;
};

struct fuiTimeline {
    int m_symbolIndex;
    uint16_t m_frameIndex;
    uint16_t m_frameCount;
    uint16_t m_actionIndex;
    uint16_t m_actionCount;
    fuiRect m_rect;
};
struct fuiTimelineAction {
    uint16_t m_type;
    int16_t m_frame;
    char m_argument0[64];
    char m_argument1[64];
};
struct fuiShape {
    int m_symbolIndex;
    int m_componentIndex;
    int m_componentCount;
    fuiRect m_rect;
};
struct fuiFillStyle {
    int m_type;
    fuiRGBA m_colour;
    int m_bitmapIndex;
    fuiMatrix m_matrix;
};
struct fuiShapeComponent {
    fuiFillStyle m_fill;
    int m_vertexIndex;
    int m_vertexCount;
};
struct fuiVert {
    float m_x, m_y;
};
struct fuiTimelineFrame {
    char m_name[64];
    int m_eventIndex;
    int m_eventCount;
};
struct fuiTimelineEvent {
    uint16_t m_type;
    uint8_t m_objectType;
    uint8_t m_flags;
    int16_t m_depth;
    int16_t m_objectIndex;
    int16_t m_unknown;
    int16_t m_nameIndex;
    fuiMatrix m_matrix;
    fuiColorTransform m_colourTransform;
    fuiRGBA m_colour;
};
struct timelineEventName {
    char m_name[64];
};
struct fuiReference {
    int m_symbolIndex;
    char m_name[64];
    int m_index;
};
struct fuiEdittext {
    int m_symbolIndex;
    fuiRect m_rect;
    int m_fontId;
    float m_fontSize;
    fuiRGBA m_colour;
    int m_flags[6];
    char m_text[256];
};
struct fuiBitmap {
    int m_symbolIndex;
    int m_format;
    int m_width;
    int m_height;
    int m_offset;
    int m_size;
    int m_alphaOffset;
    int m_texture;
};
struct fuiFontName {
    int m_id;
    char m_name[256];
};
struct fuiImportAsset {
    char m_name[64];
};
class FJ_FuiNode;

struct fuiHeader {
    unsigned char m_signature[8];
    int m_contentSize;
    char m_fileName[64];
    int m_timelineCount;
    int m_timelineEventNameCount;
    int m_timelineActionCount;
    int m_shapeCount;
    int m_shapeComponentCount;
    int m_vertCount;
    int m_timelineFrameCount;
    int m_timelineEventCount;
    int m_referenceCount;
    int m_editTextCount;
    int m_symbolCount;
    int m_bitmapCount;
    int m_imagesSize;
    int m_fontNameCount;
    int m_importAssetCount;
    fuiRect m_stageSize;
    int m_index;
};

struct _48 {
    const char** m_name;
};

struct fuiData {
    fuiTimeline* m_timeline;
    fuiTimelineAction* m_timelineAction;
    fuiShape* m_shape;
    fuiShapeComponent* m_shapeComponent;
    fuiVert* m_vert;
    fuiTimelineFrame* m_timelineFrame;
    fuiTimelineEvent* m_timelineEvent;
    timelineEventName* m_timelineEventName;
    fuiReference* m_fuiReference;
    fuiEdittext* m_fuiEdittext;
    fuiSymbol* m_fuiSymbol;
    fuiBitmap* m_fuiBitmap;
    void* m_imageMaybe;
    fuiFontName* m_fuiFontName;
    fuiImportAsset* m_fuiImportAsset;
};

struct fuiFile {
    fuiFile();
    ~fuiFile();
    /** Retain the recovered symbol's ABI; its third argument is a byte stride,
     * despite the old unsigned-char** declaration in the symbol map.
     */
    static uint64_t addDataRegion(uint a1, uint a2, uchar** ptr, uint64_t* callbackData);
    bool load(arrayWithLength<uchar>, int);
    bool resolveReferences(fuiFile*);
    void dumpUnresolvedReferences();
    void initialiseRenderTexture(fuiBitmap*, bool);
    fuiRenderNode* getRootNode();
    void createNodeFromSymbol(char* const, fuiRenderNode*, int);
    // findNode - doesn't exist in switch edition
    // setVisible - doesn't exist in switch edition

    void setCustomDrawCallback(void (*)(void*, const char*, fuiRect*), void* node);
    float getStageWidth();
    float getStageHeight();
    void setIndex(int);

    fuiHeader m_header;
    int m_field9C;
    fuiData m_data;
    fuiRenderNodeStage* m_renderNodeStage;
    fuiRenderNodeTimeline* m_renderNodeTimeline;

    void (*m_callbackFunc)(void*, const char*, fuiRect*);
    void* m_callbackData;
    void* m_field138;
};

static_assert(sizeof(fuiHeader) == 0x9c, "FUI header including runtime file index");
static_assert(offsetof(fuiHeader, m_contentSize) == 8, "FUI content size");
static_assert(offsetof(fuiHeader, m_stageSize) == 0x88, "FUI stage rectangle");
static_assert(sizeof(fuiTimeline) == 0x1c && sizeof(fuiTimelineAction) == 0x84);
static_assert(sizeof(fuiShape) == 0x1c && sizeof(fuiShapeComponent) == 0x2c);
static_assert(sizeof(fuiTimelineFrame) == 0x48 && sizeof(fuiTimelineEvent) == 0x48);
static_assert(sizeof(fuiReference) == 0x48 && sizeof(fuiEdittext) == 0x138);
static_assert(sizeof(fuiBitmap) == 0x20 && sizeof(fuiFontName) == 0x104);
static_assert(offsetof(fuiFile, m_data) == 0xa0);
static_assert(offsetof(fuiFile, m_renderNodeStage) == 0x118);
static_assert(offsetof(fuiFile, m_field138) == 0x138);
