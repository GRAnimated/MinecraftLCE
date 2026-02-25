#pragma once

#include "fui/fuiSymbol.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"

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
    fuiMatrix operator*(const fuiMatrix& rhs) const {
        fuiMatrix out = {};
        mul(*this, rhs, out);

        return out;
    }

    static void mul(const fuiMatrix& lhs, const fuiMatrix& rhs, fuiMatrix& out);
};
struct fuiColorTransform {
    float m_redMultTerm;
    float m_greenMultTerm;
    float m_blueMultTerm;
    float m_alphaMultTerm;
    float m_redAddTerm;
    float m_greenAddTerm;
    float m_blueAddTerm;
    float m_alphaAddTerm;
};

struct fuiTimeline {
    int m_symbolIndex;
    short m_frameIndex;
    short m_frameCount;
    short m_actionIndex;
    short m_actionCount;
    fuiRect m_rect;
};
struct fuiTimelineAction;
struct fuiShape;
struct fuiShapeComponent;
struct fuiVert;
struct fuiTimelineFrame;
struct fuiTimelineEvent;
struct timelineEventName;
struct fuiReference {
    int m_symbolIndex;
    char m_name[64];
    int m_index;
};
struct fuiEdittext;
struct fuiBitmap;
struct fuiFontName;
struct fuiImportAsset;
class FJ_FuiNode;

struct fuiHeader {
    bool m_field0;
    int m_contentSize;
    int m_field8;
    char m_fileName[60];
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
    int m_bitmapCount;
    int m_imagesSize;
    int m_field7C;
    int m_fontNameCount;
    int m_importAssetCount;
    int m_unk;
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
    fuiBitmapFont* m_fuiBitmap;
    void* m_imageMaybe;
    fuiFontName* m_fuiFontName;
    fuiImportAsset* m_fuiImportAsset;
};

struct fuiFile {
    fuiFile();
    ~fuiFile();
    // NOTE: HAD TO CHANGE THE SIGNATURE BECAUSE OF THE METHOD BEING DIFFERENT
    // ORIG HAD A CALLBACK METHOD INSTEAD OF DATA
    static uint64_t addDataRegion(uint a1, uint a2, uchar** ptr, uint64_t* callbackData);
    void load(arrayWithLength<uchar>, int);
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
