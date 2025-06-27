#pragma once

#include "Minecraft.World/ArrayWithLength.h"

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
    void preRender(fuiFile*);
    void render(fuiFile*, float, float, float, float);
    void dispatchKeyboardEvent(fuiFile*, bool, int);
    void dispatchMouseMoveEvent(fuiFile*, float, float);
    void dispatchEnterFrameEvent();
    void addDirectEventListener(const FJ_EventListener&);
    void removeDirectEventListener(const FJ_EventListener&);
    void removeEventListenerForNode(FJ_FuiNode*);
    void manageTexture(fuiFile*, fuiBitmap*);
    void removeManagedTexture(fuiFile*, fuiBitmap*);
    void setFontIndirection(char const*, char const*);

    char padding[659];
    float mScreenWidth;
    float mScreenHeight;
    char padding2[0x128];
    std::vector<FJ_EventListener> mEventListeners;
    char padding4[0x68];
    fuiTextureManager *mTextureManager;
    int mResolution;
};
