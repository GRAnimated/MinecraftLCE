#pragma once

#include "fui/node/FJ_FuiNode.h"
class fuiFile;
class fuiMatrix;
class fuiObject;
class fuiRect;
class fuiRGBA;
enum eFuiObjectType {};

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
    virtual void setX(float);
    virtual void setY(float);
    virtual void setWidth(float);
    virtual void setHeight(float);
    virtual float getWidth();
    virtual float getHeight();
    virtual void getParentSpaceBounds(fuiRect*);
    virtual void generateGlobalMatrix();

    float getX();
    float getY();
    void setAlpha(float);

    fuiRenderNode* getStage() { return mStage; }

    int dword_8;
    bool byte_c;
    bool byte_d;
    unsigned int dword_10;
    int dword_14;
    fuiObject* field_18;
    eFuiObjectType field_20;
    float float_24;
    float float_28;
    float float_2c;
    float float_30;
    float mX;
    float mY;
    char gap_3C[28];
    fuiFile* field_58;
    void* qword_60;
    void* qword_68;
    void* qword_70;
    int dword78;
    float mAlpha;
    void* qword_80;
    void* qword_88;
    char byte_90[64];
    void* qword_d0;
    void* qword_d8;
    int dword_e0;
    bool byte_e4;
    fuiRenderNode* mStage;
    fuiRenderNode* mTimeline;
    FJ_FuiNodeStage* mFuiNodeStage;
    void* field_100;
};
