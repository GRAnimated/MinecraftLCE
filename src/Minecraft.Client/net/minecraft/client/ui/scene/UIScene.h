#pragma once

#include "NX/Render/C4JRender.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

enum EUIMessage {};
class fuiFile;
class fuiRect;
class UILayer;
class UIControl;

enum EUIScene {
    EUIScene_Intro = 1,
    EUIScene_SaveMessage = 2,
    EUIScene_MainMenu = 3,
    EUIScene_FullscreenProgress = 4,
    EUIScene_PauseMenu = 5,
    EUIScene_CraftingMenu = 6,
    EUIScene_FurnaceMenu = 8,
    EUIScene_ContainerMenu = 9,
    EUIScene_InventoryMenu = 11,
    EUIScene_DispenserMenu = 12,
    EUIScene_HelpAndOptionsMenu = 15,
    EUIScene_HowToPlay = 16,
    EUIScene_HowToPlayMenu = 17,
    EUIScene_ControlsMenu = 18,
    EUIScene_SettingsListMenu = 19,
    EUIScene_InGameSettingsListMenu = 20,
    EUIScene_SettingsMenu = 21,
    EUIScene_LeaderboardsMenu = 22,
    EUIScene_Credits = 23,
    EUIScene_DeathMenu = 24,
    EUIScene_CreateWorldMenu = 26,
    EUIScene_LoadCreateJoinMenu = 27,
    EUIScene_JoinMenu = 28,
    EUIScene_SignEntryMenu = 29,
    EUIScene_InGameInfoMenu = 30,
    EUIScene_ConnectingProgress = 31,
    EUIScene_DLCOffersMenu = 32,
    EUIScene_TrialExitUpsell = 34,
    EUIScene_LoadMenu = 35,
    EUIScene_ReinstallMenu = 37,
    EUIScene_SkinSelectMenu = 38,
    EUIScene_InGameHostOptionsMenu = 40,
    EUIScene_InGamePlayerOptionsMenu = 41,
    EUIScene_CreativeMenu = 42,
    EUIScene_LaunchMoreOptionsMenu = 43,
    EUIScene_DLCMainMenu = 44,
    EUIScene_NewUpdateMessage = 45,
    EUIScene_EnchantingMenu = 46,
    EUIScene_BrewingStandMenu = 47,
    EUIScene_EndPoem = 48,
    EUIScene_TradingMenu = 50,
    EUIScene_AnvilMenu = 51,
    EUIScene_TeleportMenu = 52,
    EUIScene_HopperMenu = 53,
    EUIScene_BeaconMenu = 54,
    EUIScene_HorseInventoryMenu = 55,
    EUIScene_ClassicCraftingMenu = 56,
    EUIScene_SuperFlatMenu = 57,
    EUIScene_SuperFlatEditLayer = 58,
    EUIScene_SuperFlatPresets = 59,
    EUIScene_GameModeScoreboardMenu = 60,
    EUIScene_WritableBookMenu = 61,
    EUIScene_MapVoteMenu = 62,
    EUIScene_MapSelectMenu = 63,
    EUIScene_BiomePreviewMenu = 64,
    EUIScene_Keyboard = 72,
    EUIScene_QuadrantSignin = 73,
    EUIScene_MessageBox = 74,
    EUIScene_Timer = 75,
    EUIScene_EULA = 76,
    EUIScene_InGameSaveManagementMenu = 77,
    EUIScene_LanguageSelector = 78,
    EUIScene_AchievementsMenu = 79,
    EUIScene_BedrockUpsell = 80,
    EUIScene_DefaultMAYBE = 81,

    EUIComponent_TutorialPopup = 25,
    EUIComponent_Chat = 36,
    EUIScene_HUD = 49,
    EUIComponent_Panorama = 65,
    EUIComponent_Logo = 66,
    EUIComponent_DebugUIConsole = 67,
    EUIComponent_DebugUIMarketingGuide = 68,
    EUIComponent_Tooltips = 69,
    EUIComponent_PressStartToPlay = 70,
    EUIComponent_MenuBackground = 71
};

class UIScene {
public:
    class _CachedSlotDrawData;
    class _TimerInfo {
    public:
        int mTimeDelay;
        int mNextTickTime;
        bool mEnabled;
    };

    UIScene(int, UILayer*);

    void setSafeZone(double, double, double, double);
    void tickTimers();
    void initialiseMovie();
    void loadMovie();
    void doHorizontalResizeCheck();
    void navigateBack();
    void sendInputToMovie(int, bool, bool, bool);
    int convertGameActionToFuiKeycode(int);
    // void handleFocusChange(int, int);
    bool controlHasFocus(UIControl_Base*);
    bool controlHasFocus(int);
    void addTimer(int, int);
    void killTimer(int);
    bool hasTimer(int);
    void* GetCallbackUniqueId();

    void removeControl(UIControl_Base* control, bool);

    fuiFile* getFuiFile() { return this->mFuiFile; }

    virtual void reloadMovie(bool);
    virtual bool needsReloaded();
    virtual bool hasMovie();
    virtual void updateSafeZone();
    virtual void updateViewportTouchOffset();
    virtual double getSafeZoneHalfHeight();
    virtual double getSafeZoneHalfWidth();
    virtual std::wstring getMoviePath() = 0;
    virtual bool mapElementsAndNames();
    virtual ~UIScene();
    virtual EUIScene getSceneType() = 0;
    virtual int getSubSceneType() const;
    virtual void tick();
    virtual void SetFocusToElement(int);
    virtual void handleTimerComplete(int);
    virtual bool stealsFocus();
    virtual bool hasFocus(int);
    virtual void updateTooltips();
    virtual void updateComponents();
    virtual void handleGainFocus(bool);
    virtual void handleLoseFocus();
    virtual bool hidesLowerScenes();
    virtual bool blocksInput();
    virtual void* GetMainPanel();
    virtual void render(int, int, C4JRender::eViewportType);
    virtual void customDraw(const char*, fuiRect*);
    virtual bool allowRepeat(int);
    virtual void handleInput(int, int, bool, bool, bool, bool&);
    virtual void handleDestroy();
    virtual void handlePreUnloadForReload();
    virtual void handlePreReload();
    virtual void handleReload();
    virtual void handlePress(int, int);
    virtual void handleFocusChange(int, int);
    virtual void handleInitFocus(int, int);
    virtual void handleCheckboxToggled(int, bool);
    virtual void handleCheckboxElementToggled(int, int, bool);
    virtual void handleSliderMove(int, int);
    virtual void handleSliderElementMove(int, int, int);
    virtual void handleAnimationEnd();
    virtual void handleSelectionChanged(int);
    virtual void handleRequestMoreData(int, bool);
    virtual void handleTouchBoxRebuild();
    virtual void HandleDLCMountingComplete();
    virtual void HandleDLCInstalled();
    virtual void HandleDLCLicenseChange();
    virtual void HandleTMSBanFileRetrieved();
    virtual void HandleMessage(EUIMessage, void*);
    virtual void HandleSaveDeviceRemoved(int);
    virtual void handleUnlockFullVersion();
    virtual void handleTouchInput(unsigned int, int, int, int, bool, bool, bool);
    virtual void isReadyToDelete();

    static void customDrawFui(void*, const char*, fuiRect*);

    std::wstring wstring_8;
    fuiFile* mFuiFile;
    bool bool_28;
    char gap_29[3];
    void* qword30;
    std::unordered_map<std::wstring, bool> map1;
    std::unordered_map<int, UIScene::_TimerInfo> mTimersMap;
    int mControlFocused;
    int mControlChildFocus;
    float mOpacity;
    bool mIsInitializedMovie;
    bool mVisible;
    bool byte_96;
    bool bool_97;
    UIScene* mBackScene;
    void* mCallbackUniqueId;
    int mResType;  // 0 - 1080p | 1 - 720p
    bool mHidden;
    bool bool_ad;
    int mStageWidth;
    int mStageHeight;
    int mStageWidth2;
    int mStageHeight2;
    std::vector<UIControl*> mUIControls;
    UILayer* mUILayer;
    bool mFocusRelated;
    int mPadID;
    bool mHideLowerScenes;
    bool byte_e9;
    bool byte_ea;
    bool byte_eb;
    int dwordF8;
    std::vector<UIScene::_CachedSlotDrawData*> mCachedSlotDrawData;
};
