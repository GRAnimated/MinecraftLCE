#pragma once

#include "NX/Render/C4JRender.h"
#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/core/storage/C4JStorage.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "nn/os/os_MutexTypes.h"
#include "types.h"

#include <string>
#include <unordered_map>
#include <vector>

class SoundEvent;
enum EUILayer {};
enum EUIGroup {};
enum EControllerActions {};
class _TutorialPopupInfo {};  // TODO: define somewhere else

class IUIController {
public:
    enum eRESOLUTION_DISABLE_FLAG { FLAG_0 };

    // nullsub here, although it's probs just the second destructor
    virtual ~IUIController();
    virtual void tick() = 0;
    virtual void requestResolutionChange() = 0;
    virtual void setResolutionChangeDisableFlag(eRESOLUTION_DISABLE_FLAG) = 0;
    virtual void clearResolutionChangeDisableFlag(eRESOLUTION_DISABLE_FLAG) = 0;
    virtual void render() = 0;
    virtual void StartReloadSkinThread() = 0;
    virtual bool IsReloadingSkin() = 0;
    virtual void CleanUpSkinReload() = 0;
    virtual void NavigateToScene(int, EUIScene, void*, EUILayer, EUIGroup) = 0;
    virtual void NavigateBack(int, bool, EUIScene, EUILayer) = 0;
    virtual void CloseUIScenes(int, bool) = 0;
    virtual void CloseAllPlayersScenes(bool) = 0;
    virtual bool IsPauseMenuDisplayed(int) = 0;
    virtual bool IsContainerMenuDisplayed(int) = 0;
    virtual bool IsIgnorePlayerJoinMenuDisplayed(int) = 0;
    virtual bool IsIgnoreAutosaveMenuDisplayed(int) = 0;
    virtual void SetIgnoreAutosaveMenuDisplayed(int, bool) = 0;
    virtual bool IsSceneInStack(int, EUIScene) = 0;
    virtual void* GetMenuDisplayed(int) = 0;  // unk return type
    virtual void CheckMenuDisplayed() = 0;
    virtual void SetTooltipText(unsigned int, unsigned int, int) = 0;
    virtual void SetEnableTooltips(unsigned int, bool) = 0;
    virtual void ShowTooltip(unsigned int, unsigned int, bool) = 0;
    virtual int SetTooltips(unsigned int, int, int, int, int, int, int, int, int, int, int, int, int, int,
                            int, int, int, bool, bool)
        = 0;  // how many params holy fuck
    virtual void EnableTooltip(unsigned int, unsigned int, bool) = 0;
    virtual void RefreshTooltips(unsigned int) = 0;
    virtual void PlayUISFX(const SoundEvent*) = 0;
    virtual void ShowUIDebugConsole(bool) {}
    virtual void ShowUIDebugMarketingGuide(bool) {}
    virtual void DisplayGamertag(unsigned int, bool) = 0;
    virtual void SetSelectedItem(unsigned int, const std::wstring&, const std::wstring&) = 0;
    virtual void ResetSelectedItem() = 0;
    virtual void UpdateSelectedItemPos(unsigned int) = 0;
    virtual void HandleDLCMountingComplete() = 0;
    virtual void HandleDLCInstalled(int) = 0;
    virtual void HandleDLCLicenseChange() = 0;
    virtual void HandleTMSDLCFileRetrieved(int) = 0;
    virtual void HandleTMSBanFileRetrieved(int) = 0;
    virtual void HandleInventoryUpdated(int) = 0;
    virtual void HandleGameTick() = 0;
    virtual void HandleSaveDeviceRemoved(int) = 0;
    virtual void SetTutorialDescription(int, _TutorialPopupInfo*) = 0;
    virtual void SetTutorialVisible(int, bool) = 0;
    virtual bool IsTutorialVisible(int) = 0;
    virtual void UpdatePlayerBasePositions() = 0;
    virtual void SetEmptyQuadrantLogo(int) = 0;
    virtual void HideAllGameUIElements() = 0;
    virtual void ShowOtherPlayersBaseScene(unsigned int, bool) = 0;
    virtual void ShowTrialTimer(bool shown) = 0;
    virtual void SetTrialTimerLimitSecs(unsigned int secs) = 0;
    virtual void UpdateTrialTimer(unsigned int) = 0;
    virtual void ReduceTrialTimerValue() = 0;
    virtual void ShowAutosaveCountdownTimer(bool shown) = 0;
    virtual void UpdateAutosaveCountdownTimer(unsigned int) = 0;
    virtual void ShowSavingMessage(unsigned int, C4JStorage::ESavingMessage) = 0;
    virtual void PressStartPlaying(unsigned int) = 0;
    virtual void ShowPressStart(unsigned int) = 0;
    virtual void ShowChestRefillAnimation(bool) = 0;
    virtual void SetWinUserIndex(unsigned int) = 0;  // windows mentioned again
    virtual void ShowTimedSplash(unsigned int, const std::wstring&, unsigned int) = 0;
    virtual bool IsShowingErrorMessage(int) = 0;
    virtual bool IsShowingAlertMessage(int) = 0;
    virtual bool getCleanupOnReload() = 0;
    virtual bool setCleanupOnReload(bool) = 0;
    virtual bool IsExpectingOrReloadingSkin() = 0;
    virtual void SetTooltips(unsigned int, int*, bool, bool) = 0;
    virtual bool IsToolTipDynamic(unsigned int, unsigned int, EControllerActions&) = 0;
    virtual int GetHotBarX(unsigned int) = 0;       // could return float too
    virtual int GetHotBarY(unsigned int) = 0;       // could return float too
    virtual int GetHotBarWidth(unsigned int) = 0;   // could return float too
    virtual int GetHotBarHeight(unsigned int) = 0;  // could return float too
    virtual bool GetQuickSelectVisible(unsigned int) = 0;
    virtual void sub_71005300EC() = 0;
    virtual void RemoveInteractSceneReference(int, UIScene*) = 0;
    virtual void HideChestRefillAnimation() = 0;
    virtual void ShowPlayerDisplayname(bool) = 0;
    virtual void HidePressStart() = 0;
    virtual void RequestProfileSignInMenu(int, int, wchar_t**, unsigned int, unsigned int,
                                          int (*)(void*, int, int), void*, wchar_t*, unsigned int)
        = 0;
    virtual void RequestAlertMessage(int, int, int*, unsigned int, unsigned int,
                                     int (*)(void*, int, C4JStorage::EMessageResult), void*, wchar_t*, bool)
        = 0;
    virtual void RequestErrorMessage(int, int, int*, unsigned int, unsigned int,
                                     int (*)(void*, int, C4JStorage::EMessageResult), void*, wchar_t*, bool)
        = 0;
    virtual void RequestMessageBox(int, int, int*, unsigned int, unsigned int,
                                   int (*)(void*, int, C4JStorage::EMessageResult), void*, wchar_t*,
                                   unsigned int, bool, bool)
        = 0;
};

class ConsoleUIController : public IUIController {
public:
    static void* qword_71017BE950;
    static nn::os::MutexType unk_71017BE928;
    static bool unk_71017BE928_initalised;
    static EUIScene sCurrentScene;

    class UICONTROL {};
    class TextureDetail {};
    class _CachedMovieData : public arrayWithLength<uchar> {
    public:
        long time;
    };
    class _QueuedMessageBoxData {};

    ConsoleUIController();

    virtual ~ConsoleUIController();
    void updateViewportTouchOffset(C4JRender::eViewportType);
    bool IsReloadingSkin() override;
    int SetTooltips(unsigned int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int,
                    int, bool, bool) override;
    void setResolutionChangeDisableFlag(IUIController::eRESOLUTION_DISABLE_FLAG) override;
    void setUnk2(bool);
    void preInit(int screenWidth, int screenHeight);
    void init(int screenWidth, int screenHeight);
    void postInit();
    int SetAchievementUnlocked();
    void TouchBoxRebuild(UIScene*);
    void AnimateKeyPress(int, int, bool, bool, bool);
    void PlayUISFX(const SoundEvent*) override;
    void NavigateToScene(int, EUIScene, void*, EUILayer, EUIGroup) override;
    arrayWithLength<uchar> getMovieData(const std::wstring&);
    void setupRenderPosition(C4JRender::eViewportType);
    void NavigateBack(int, bool, EUIScene, EUILayer) override;
    void* RegisterForCallbackId(UIScene*);
    void ResetSelectedItem() override;

    void tick() override;
    void render() override;
    void CheckMenuDisplayed() override;

    void RequestErrorMessage(int, int, int*, unsigned int, unsigned int,
                             int (*)(void*, int, C4JStorage::EMessageResult), void*, wchar_t*, bool) override;
    float getScreenWidth() { return this->mScreenWidth; }
    bool IsPauseMenuDisplayed(int pad) override;
    void UpdateTrialTimer(unsigned int pad) override;
    void ShowTrialTimer(bool) override;
    void ShowUIDebugConsole(bool) override;
    void ShowUIDebugMarketingGuide(bool) override;
    void requestResolutionChange() override;
    void clearResolutionChangeDisableFlag(eRESOLUTION_DISABLE_FLAG) override;
    void StartReloadSkinThread() override;
    void CleanUpSkinReload() override;
    void CloseUIScenes(int, bool) override;
    void CloseAllPlayersScenes(bool) override;
    bool IsContainerMenuDisplayed(int) override;
    bool IsIgnorePlayerJoinMenuDisplayed(int) override;
    bool IsIgnoreAutosaveMenuDisplayed(int) override;
    void SetIgnoreAutosaveMenuDisplayed(int, bool) override;
    bool IsSceneInStack(int, EUIScene) override;
    void* GetMenuDisplayed(int) override;
    void SetTooltipText(unsigned, unsigned, int) override;
    void SetEnableTooltips(unsigned, bool) override;
    void ShowTooltip(unsigned, unsigned, bool) override;
    void EnableTooltip(unsigned, unsigned, bool) override;
    void RefreshTooltips(unsigned) override;
    void DisplayGamertag(unsigned, bool) override;
    void SetSelectedItem(unsigned, const std::wstring&, const std::wstring&) override;
    void UpdateSelectedItemPos(unsigned) override;
    void HandleDLCMountingComplete() override;
    void HandleDLCInstalled(int) override;
    void HandleDLCLicenseChange() override;
    void HandleTMSDLCFileRetrieved(int) override;
    void HandleTMSBanFileRetrieved(int) override;
    void HandleInventoryUpdated(int) override;
    void HandleGameTick() override;
    void HandleSaveDeviceRemoved(int) override;
    void SetTutorialDescription(int, _TutorialPopupInfo*) override;
    void SetTutorialVisible(int, bool) override;
    bool IsTutorialVisible(int) override;
    void UpdatePlayerBasePositions() override;
    void SetEmptyQuadrantLogo(int) override;
    void HideAllGameUIElements() override;
    void ShowOtherPlayersBaseScene(unsigned, bool) override;
    void SetTrialTimerLimitSecs(unsigned secs) override;
    void ReduceTrialTimerValue() override;
    void ShowAutosaveCountdownTimer(bool shown) override;
    void UpdateAutosaveCountdownTimer(unsigned) override;
    void ShowSavingMessage(unsigned, C4JStorage::ESavingMessage) override;
    void PressStartPlaying(unsigned) override;
    void ShowPressStart(unsigned) override;
    void ShowChestRefillAnimation(bool) override;
    void SetWinUserIndex(unsigned) override;
    void ShowTimedSplash(unsigned, const std::wstring&, unsigned) override;
    bool IsShowingErrorMessage(int) override;
    bool IsShowingAlertMessage(int) override;
    bool getCleanupOnReload() override;
    bool setCleanupOnReload(bool) override;
    bool IsExpectingOrReloadingSkin() override;
    void SetTooltips(unsigned, int*, bool, bool) override;
    bool IsToolTipDynamic(unsigned, unsigned, EControllerActions&) override;
    int GetHotBarX(unsigned) override;
    int GetHotBarY(unsigned) override;
    int GetHotBarWidth(unsigned) override;
    int GetHotBarHeight(unsigned) override;
    bool GetQuickSelectVisible(unsigned) override;
    void sub_71005300EC() override;
    void RemoveInteractSceneReference(int, UIScene*) override;
    void HideChestRefillAnimation() override;
    void ShowPlayerDisplayname(bool) override;
    void HidePressStart() override;
    void RequestProfileSignInMenu(int, int, wchar_t**, unsigned, unsigned, int (*)(void*, int, int), void*,
                                  wchar_t*, unsigned) override;
    void RequestAlertMessage(int, int, int*, unsigned, unsigned,
                             int (*)(void*, int, C4JStorage::EMessageResult), void*, wchar_t*, bool) override;
    void RequestMessageBox(int, int, int*, unsigned, unsigned,
                           int (*)(void*, int, C4JStorage::EMessageResult), void*, wchar_t*, unsigned, bool,
                           bool) override;

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
    int mFlags;
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
