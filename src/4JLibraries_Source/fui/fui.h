#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

#include "nn/os.h"

struct fuiBitmap;
struct fuiFile;
class FJ_FuiNode;
class FJ_EventListener;
struct fuiTextureManager;

constexpr int FUI_RESOLUTION_1080 = 1;
constexpr int FUI_RESOLUTION_720 = 0;

typedef float mat4x4[4][4];

struct fui {
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

    mat4x4 m_atrix;
    char m_fPad4[16];
    char m_padding[568];
    float m_unk5;
    float m_unk6;
    char m_padding3[0x4];
    float m_screenWidth;
    float m_screenHeight;
    int m_padding6;
    std::vector<fuiFile*> m_scenes;
    char m_padding2[260];
    bool m_boolIdk;
    char m_elo[7];
    std::vector<FJ_EventListener> m_eventListeners;
    char m_padding4[72];
    nn::os::MutexType* m_scenesMutex;
    char m_padding5[24];
    fuiTextureManager* m_textureManager;
    int m_resolution;
};
