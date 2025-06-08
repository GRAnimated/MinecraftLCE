#pragma once
#include "nn/os/os_MutexTypes.h"
#include "types.h"
#include "Minecraft.Client/renderer/C4JRender.h"
#include "Minecraft.Client/ui/scene/UIScene.h"
#include "Minecraft.World/ArrayWithLength.h"
#include <string>
#include <unordered_map>
#include <vector>

class SoundEvent;
enum EUILayer {};
enum EUIGroup {};

class IUIController {
    virtual void empty();
};

class ConsoleUIController : public IUIController {
public:
    static void* qword_71017BE950;
    static nn::os::MutexType unk_71017BE928;
    static bool unk_71017BE928_initalised;

    class UICONTROL {};
    class TextureDetail {};
    class _CachedMovieData : public arrayWithLength<uchar> {
    public:
        long time;
    };
    class _QueuedMessageBoxData {};

    ConsoleUIController();

    void updateViewportTouchOffset(C4JRender::eViewportType);
    bool IsReloadingSkin();
    int SetTooltips(unsigned int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int,
                    int, bool, bool);
    // I don't know what it sets, and it seems that there's no such a thing on WiiU (not that it's inlined or
    // something, it's just not there at all)
    void setUnk(bool);
    void preInit(int screenWidth, int screenHeight);
    void init(int screenWidth, int screenHeight);
    void postInit();
    int SetAchievementUnlocked();
    void TouchBoxRebuild(UIScene*);
    void AnimateKeyPress(int, int, bool, bool, bool);
    void PlayUISFX(const SoundEvent*);
    void NavigateToScene(int, EUIScene, void*, EUILayer, EUIGroup);
    arrayWithLength<uchar> getMovieData(const std::wstring&);
    void setupRenderPosition(C4JRender::eViewportType);
    void NavigateBack(int, bool, EUIScene, EUILayer);
    void* RegisterForCallbackId(UIScene*);

    float getScreenWidth() { return this->mScreenWidth; }

    // void* VTable;
    void* qword8;
    void* qword10;
    nn::os::MutexType mMutex1;
    nn::os::MutexType mMutex2;
    nn::os::MutexType mMutex3;
    char gap10[864];
    float mScreenWidth;
    float mScreenHeight;
    bool mPreInited;
    char gap3E1[15];
    nn::os::MutexType mMutex4;
    void* qword410;
    char byte418;
    char byte419;
    char byte41A;
    void* qword420;
    void* qword428;
    void* qword430;
    void* qword438;
    int dword440;
    int dword444;
    std::vector<UIControl*> mUICONTROLs[3240];
    char byte13408[4];
    char byte1340C;
    void* qword13410;
    char byte13418;
    void* qword13420;
    void* qword13428;
    void* qword13430;
    void* qword13438;
    void* qword13440;
    void* qword13448;
    void* qword13450;
    void* qword13458;
    void* qword13460;
    void* qword13468;
    void* qword13470;
    void* qword13478;
    void* qword13480;
    void* qword13488;
    void* qword13490;
    void* qword13498;
    void* qword134A0;
    void* qword134A8;
    void* qword134B0;
    void* qword134B8;
    void* qword134C0;
    void* qword134C8;
    char gap134D0[24];
    char byte134E8;
    char byte134E9;
    char byte134EA;
    char byte134EB;
    char byte134EC;
    int dword134F0;
    __attribute__((aligned(8))) int dword134F8;
    char byte134FC;
    std::unordered_map<std::wstring, TextureDetail> mTextureDetails;
    std::unordered_map<std::wstring, _CachedMovieData> mCachedMovieDatas;
    std::vector<_QueuedMessageBoxData> mQueuedMessageBoxDatas;
    int cipa;
    char byte1356C;
    void* qword13570;
    nn::os::MutexType mMutex5;
    char byte13598;
    int dword1359C;
    void* qword135A0;
    char gap135A8[16];
    std::unordered_map<int, UIScene*> mUIScenes;
    nn::os::MutexType mMutex6;
    int mViewportTouchOffset1;
    int mViewportTouchOffset2;
};

extern ConsoleUIController gConsoleUIController;