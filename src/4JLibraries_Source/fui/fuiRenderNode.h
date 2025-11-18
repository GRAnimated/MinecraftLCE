#pragma once

#include "4JLibraries_Source/fui/fuiFile.h"

class FJ_FuiNodeStage;
struct fuiRenderNodeTimeline;
struct fuiMatrix;
struct fuiObject;
struct fuiRect;
struct fuiRGBA;
enum eFuiObjectType { RENDER_NODE_STAGE = 0, eFuiObjectType_1 = 1, eFuiObjectType_2 = 2 };

// weird flag thing
constexpr uint32_t FLAG_CTOR_ENABLED = 0x1;
constexpr uint32_t FLAG_NODE_VISIBLE = 0x8;
constexpr const char* DEFAULT_PATH = "?";

class fuiRenderNode {
public:
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

    void setScaleX(float sX);
    void setScaleY(float sY);

    float getScaleX();
    float getScaleY();

    fuiRenderNode* getStage() { return mStage; }

    fuiRenderNodeTimeline* asTimeline();

    int mFlags;
    bool byte_c;
    bool byte_d;
    unsigned int dword_10;
    int dword_14;
    fuiObject* field_18;
    eFuiObjectType field_20;
    fuiMatrix mMatrix;
    fuiMatrix mMatrix2;
    int unk;
    fuiFile* field_58;
    void* qword_60;
    void* qword_68;
    void* qword_70;
    int dword78;
    float mAlpha;
    fuiRect mRect;
    char mPath[64];
    void* qword_d0;
    void* qword_d8;
    int dword_e0;
    bool byte_e4;
    fuiRenderNode* mStage;
    fuiRenderNodeTimeline* mTimeline;
    FJ_FuiNodeStage* mFuiNodeStage;
};
