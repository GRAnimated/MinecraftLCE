#pragma once

#include "Minecraft.World/ArrayWithLength.h"

class fuiBitmap;
class fuiFile;
class FJ_FuiNode;
class FJ_EventListener;

class fui {
public:
    static fui* sInstance;

    fui();
    void setScreenSize(float, float);
    void load(arrayWithLength<unsigned char>, bool, int);
    void allocatePermanentFileIndex(int);
    void unloadScene(fuiFile*);
    void setResolution(int);
    void getResolution();
    void tick();
    void preRender(fuiFile*);
    void dispatchKeyboardEvent(fuiFile*, bool, int);
    void dispatchMouseMoveEvent(fuiFile*, float, float);
    void dispatchEnterFrameEvent();
    void addDirectEventListener(FJ_EventListener const&);
    void removeDirectEventListener(FJ_EventListener const&);
    void removeEventListenerForNode(FJ_FuiNode*);
    void manageTexture(fuiFile*, fuiBitmap*);
    void removeManagedTexture(fuiFile*, fuiBitmap*);
    void setFontIndirection(char const*, char const*);
};
