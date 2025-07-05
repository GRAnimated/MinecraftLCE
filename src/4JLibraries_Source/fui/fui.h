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
    void dispatchKeyboardEvent(fuiFile*, bool, int);
    void dispatchMouseMoveEvent(fuiFile*, float, float);
    void dispatchEnterFrameEvent();
    void addDirectEventListener(const FJ_EventListener&);
    void removeDirectEventListener(const FJ_EventListener&);
    void removeEventListenerForNode(FJ_FuiNode* node);
    void manageTexture(fuiFile*, fuiBitmap*);
    void removeManagedTexture(fuiFile*, fuiBitmap*);
    void setFontIndirection(const char*, const char*);

    float mUnk1;
    char mFPad[16];  // to pad each float since each one is +20 offset
    float mUnk2;
    char mFPad2[16];
    float mUnk3;
    char mFPad3[16];
    float mUnk4;
    char mFPad4[16];
    char padding[568];
    float mUnk5;
    float mUnk6;
    char padding3[0x4];
    float mScreenWidth;
    float mScreenHeight;
    int padding6;
    std::vector<fuiFile*> mScenes;
    char padding2[0x110];
    std::vector<FJ_EventListener> mEventListeners;
    char padding4[72];
    nn::os::MutexType* mScenesMutex;
    char padding5[24];
    fuiTextureManager* mTextureManager;
    int mResolution;
};
