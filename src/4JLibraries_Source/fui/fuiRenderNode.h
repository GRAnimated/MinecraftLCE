#pragma once

#include "fui/fuiFile.h"

class FJ_FuiNodeStage;
struct fuiRenderNodeTimeline;
struct fuiMatrix;
struct fuiObject;
struct fuiRect;
struct fuiRGBA;
enum eFuiObjectType {
    eFuiObjectType_Stage,
    eFuiObjectType_Shape,
    eFuiObjectType_Timeline,
    eFuiObjectType_Bitmap,
    eFuiObjectType_Unknown,
    eFuiObjectType_EditText
};

// weird flag thing
constexpr uint32_t FLAG_CTOR_ENABLED = 0x1;
constexpr uint32_t FLAG_NODE_VISIBLE = 0x8;
constexpr const char* DEFAULT_PATH = "?";

struct fuiRenderNodeColor {  // made up struct
    float r, g, b, a;
};

class fuiRenderNode {
public:
    // could be part of fui, or anything else, but let's leave it here
    // TLDR: unknown location
    static fuiMatrix GLOBAL_MATRIX;
    static fuiRenderNodeColor DEFAULT_COLORS[2];

    fuiRenderNode(fuiRenderNode*, fuiRenderNode*, fuiObject*, unsigned int, eFuiObjectType, unsigned char,
                  fuiRGBA*, unsigned char, bool, fuiFile*);

    virtual ~fuiRenderNode();
    virtual void shutdown();
    virtual void gather(bool) = 0;
    virtual void preRender() = 0;
    virtual void render(fuiRect*, fuiMatrix*) = 0;
    virtual void handleAddedToStage();
    virtual fuiRenderNode* findNode(const char*);
    virtual fuiRenderNode* getNodeFromPath(const char*);
    virtual void setVisibility(bool);
    bool isVisible();
    virtual void setX(float);
    virtual void setY(float);
    virtual void setWidth(float);
    virtual void setHeight(float);
    virtual float getWidth();
    virtual float getHeight();
    virtual void getParentSpaceBounds(fuiRect*);
    virtual void generateGlobalMatrix();

    // apparently this is static? (SFP)
    static FJ_FuiNode* Create(fuiRenderNode* node);

    float getX();
    float getY();
    void disableCtor();
    void setAlpha(float a);
    void progogateBounds();  // english 100
    void pushMatrix();
    void pushMatrix(fuiMatrix&);

    void setScaleX(float sX);
    void setScaleY(float sY);

    float getScaleX();
    float getScaleY();

    fuiRenderNode* getStage() { return mStage; }

    fuiRenderNodeTimeline* asTimeline();

    int mFlags;
    char byte_c;
    char byte_d;
    unsigned int dword_10;
    int dword_14;
    fuiObject* mFuiObject;
    eFuiObjectType mFuiObjectType;
    fuiMatrix mMatrix;
    fuiMatrix mMatrix2;
    int unk;
    fuiFile* mFuiFile;
    fuiRenderNodeColor mRenderColor2;
    fuiRenderNodeColor mRenderColor;
    fuiRect mRect;
    char mPath[64];
    void* qword_d0;
    void* qword_d8;
    int mColor;
    char byte_e4;
    fuiRenderNode* mStage;
    fuiRenderNodeTimeline* mTimeline;
    FJ_FuiNodeStage* mFuiNodeStage;
};
