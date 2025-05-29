#pragma once

#include "types.h"
#include "Minecraft.World/ArrayWithLength.h"

// Most structs derived from
// https://github.com/NessieHax/fui-research-repo/blob/main/DOCUMENTATION.md

class fuiRenderNode;
class fuiBitmap;
struct fuiRect {
    float minX;
    float maxX;
    float minY;
    float maxY;
};
struct fuiRGBA {
    int color;  // RGBA
};
struct fuiMatrix {
    float scaleX;
    float scaleY;
    float rotateSkew0;
    float rotateSkew1;
    float posX;
    float posY;
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
struct fuiReference {
    int symbolIndex;
    char name[64];
    int index;
};
class fuiEdittext;
class fuiBitmap;
class fuiFontName;
class fuiSymbol;
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
    void* size_0x40;
    fuiReference* fuiReference;
    fuiEdittext* fuiEdittext;
    _48* size_0x48;
    fuiBitmap* fuiBitmap;
    void* size_0x20;
    fuiFontName* fuiFontName;
    fuiSymbol* fuiSymbol;
    fuiImportAsset* fuiImportAsset;
};

class fuiFile {
public:
    fuiFile();
    ~fuiFile();
    void addDataRegion(uint, uint, uchar**, void (*)(void*));
    void load(arrayWithLength<uchar>, int);
    bool resolveReferences(fuiFile*);
    void dumpUnresolvedReferences();
    void initialiseRenderTexture(fuiBitmap*, bool);
    fuiRenderNode* getRootNode();
    void createNodeFromSymbol(char* const, fuiRenderNode*, int);
    // findNode - doesn't exist in switch edition
    // setVisible - doesn't exist in switch edition
    void setCustomDrawCallback(void (*)(void*, char const*, fuiRect*), void*);
    float getStageWidth();
    float getStageHeight();
    void setIndex(int);

    fuiHeader mHeader;
    int mIndex;
    int field_9C;
    fuiData mData;
    FJ_FuiNode* mRootNode;

    void (*mCallbackFunc)(void*, const char*, fuiRect*);
    void* mCallbackData;
    void* field_138;
};