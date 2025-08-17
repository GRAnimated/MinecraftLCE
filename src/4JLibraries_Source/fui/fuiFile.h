#pragma once

#include "fui/fuiSymbol.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"

// Most structs derived from
// https://github.com/NessieHax/fui-research-repo/blob/main/DOCUMENTATION.md

class fuiRenderNode;
class fuiBitmapFont;
class fuiRenderNodeStage;
class fuiRenderNodeTimeline;
class fuiRect {
public:
    float minX;
    float maxX;
    float minY;
    float maxY;

    // getHeight?
    float getHeight() { return this->maxY - this->minY; }

    // getWidth?
    float getWidth() { return this->maxX - this->minX; }
};
struct fuiRGBA {
    int color;  // RGBA
};
struct fuiMatrix {
    float mScaleX;
    float mScaleY;
    float mRotSkewX;
    float mRotSkewY;
    float mPosX;
    float mPosY;

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
    float redMultTerm;
    float greenMultTerm;
    float blueMultTerm;
    float alphaMultTerm;
    float redAddTerm;
    float greenAddTerm;
    float blueAddTerm;
    float alphaAddTerm;
};

struct fuiTimeline {
    int symbolIndex;
    short frameIndex;
    short frameCount;
    short actionIndex;
    short actionCount;
    fuiRect rect;
};
class fuiTimelineAction;
class fuiShape;
class fuiShapeComponent;
class fuiVert;
class fuiTimelineFrame;
class fuiTimelineEvent;
class timelineEventName;
struct fuiReference {
    int symbolIndex;
    char name[64];
    int index;
};
class fuiEdittext;
class fuiBitmap;
class fuiFontName;
class fuiImportAsset;
class FJ_FuiNode;

struct fuiHeader {
    bool field_0;
    int contentSize;
    int field_8;
    char fileName[60];
    int timelineCount;
    int timelineEventNameCount;
    int timelineActionCount;
    int shapeCount;
    int shapeComponentCount;
    int vertCount;
    int timelineFrameCount;
    int timelineEventCount;
    int referenceCount;
    int editTextCount;
    int bitmapCount;
    int imagesSize;
    int field_7C;
    int fontNameCount;
    int importAssetCount;
    int mUnk;
    fuiRect stageSize;
    int index;
};

struct _48 {
    const char** name;
};

struct fuiData {
    fuiTimeline* timeline;
    fuiTimelineAction* timelineAction;
    fuiShape* shape;
    fuiShapeComponent* shapeComponent;
    fuiVert* vert;
    fuiTimelineFrame* timelineFrame;
    fuiTimelineEvent* timelineEvent;
    timelineEventName* timelineEventName;
    fuiReference* fuiReference;
    fuiEdittext* fuiEdittext;
    fuiSymbol* fuiSymbol;
    fuiBitmapFont* fuiBitmap;
    void* imageMaybe;
    fuiFontName* fuiFontName;
    fuiImportAsset* fuiImportAsset;
};

class fuiFile {
public:
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

    fuiHeader mHeader;
    int field_9C;
    fuiData mData;
    fuiRenderNodeStage* mRenderNodeStage;
    fuiRenderNodeTimeline* mRenderNodeTimeline;

    void(__fastcall* mCallbackFunc)(void*, const char*, fuiRect*);
    void* mCallbackData;
    void* field_138;
};
