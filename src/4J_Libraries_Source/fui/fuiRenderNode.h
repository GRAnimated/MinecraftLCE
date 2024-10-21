#pragma once

#include "4J_Libraries_Source/fui/node/FJ_FuiNode.h"
class fuiFile;
class fuiMatrix;
class fuiObject;
class fuiRect;
class fuiRGBA;
enum eFuiObjectType {};

class fuiRenderNode {
public:
    fuiRenderNode(fuiRenderNode*, fuiRenderNode*, fuiObject*, unsigned int, eFuiObjectType, unsigned char, fuiRGBA*, unsigned char, bool, fuiFile*);

    virtual ~fuiRenderNode();
    virtual void shutdown();
    virtual void gather(bool) = 0;
    virtual void preRender() = 0;
    virtual void render(fuiRect*, fuiMatrix*) = 0;
    virtual void handleAddedToStage();
    virtual void findNode(char const*);
    virtual void getNodeFromPath(char const*);
    virtual void setVisibility(bool);
    virtual void setX(float);
    virtual void setY(float);
    virtual void setWidth(float);
    virtual void setHeight(float);
    virtual void getWidth();
    virtual void getHeight();
    virtual void getParentSpaceBounds(fuiRect*);
    virtual void generateGlobalMatrix();

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
    float float_34;
    float float_38;
    char gap_3C[28];
    fuiFile* field_58;
    void* qword_60;
    void* qword_68;
    void* qword_70;
    void* qword_78;
    void* qword_80;
    void* qword_88;
    char byte_90[64];
    void* qword_d0;
    void* qword_d8;
    int dword_e0;
    bool byte_e4;
    fuiRenderNode* mStage;
    fuiRenderNode* field_f0;
    FJ_FuiNodeStage* mFuiNodeStage;
    void* field_100;
};
