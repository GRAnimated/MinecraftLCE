#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

#include "nn/os.h"

class fuiBitmap;
class fuiFile;
class FJ_FuiNode;
class FJ_EventListener;
class fuiTextureManager;

constexpr int FUI_RESOLUTION_1080 = 1;
constexpr int FUI_RESOLUTION_720 = 0;

typedef float mat4x4[4][4];

class fui {
public:
    static fui* sInstance;

    fui();
    void setScreenSize(float width, float height);
    fuiFile* load(arrayWithLength<unsigned char>, bool, int);
    void allocatePermanentFileIndex(int);
    void unloadScene(fuiFile*);
    void setResolution(int);
    int getResolution();
    void tick();
    void preRender(fuiFile* file);
    void render(fuiFile*, float, float, float, float);
    void render(fuiFile*, float, float, float, float, float, float);
    void dispatchKeyboardEvent(fuiFile*, bool, int);
    void dispatchMouseMoveEvent(fuiFile*, float, float);
    void dispatchEnterFrameEvent();
    void addDirectEventListener(const FJ_EventListener&);
    void removeDirectEventListener(const FJ_EventListener&);
    void removeEventListenerForNode(FJ_FuiNode* node);
    void manageTexture(fuiFile*, fuiBitmap*);
    void removeManagedTexture(fuiFile*, fuiBitmap*);
    void setFontIndirection(const char*, const char*);

    mat4x4 matrix;
    char mFPad4[16];
    char padding[568];
    float mUnk5;
    float mUnk6;
    char padding3[0x4];
    float mScreenWidth;
    float mScreenHeight;
    int padding6;
    std::vector<fuiFile*> mScenes;
    char padding2[260];
    bool mBoolIdk;
    char elo[7];
    std::vector<FJ_EventListener> mEventListeners;
    char padding4[72];
    nn::os::MutexType* mScenesMutex;
    char padding5[24];
    fuiTextureManager* mTextureManager;
    int mResolution;
};
