#pragma once

#include "Minecraft.Client/renderer/C4JRender.h"
#include "Minecraft.Client/ui/scene/control/UIControl_Base.h"
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
    UIScene_Intro = 1,
    UIScene_SaveMessage = 2,
    UIScene_MainMenu = 3,
    UIScene_FullscreenProgress = 4,
    UIScene_PauseMenu = 5,
    UIScene_CraftingMenu = 6,
    UIScene_FurnaceMenu = 8,
    UIScene_ContainerMenu = 9,
    UIScene_InventoryMenu = 11,
    UIScene_DispenserMenu = 12,
    UIScene_HelpAndOptionsMenu = 15,
    UIScene_HowToPlay = 16,
    UIScene_HowToPlayMenu = 17,
    UIScene_ControlsMenu = 18,
    UIScene_SettingsListMenu = 19,
    UIScene_InGameSettingsListMenu = 20,
    UIScene_SettingsMenu = 21,
    UIScene_LeaderboardsMenu = 22,
    UIScene_Credits = 23,
    UIScene_DeathMenu = 24,
    UIScene_CreateWorldMenu = 26,
    UIScene_LoadCreateJoinMenu = 27,
    UIScene_JoinMenu = 28,
    UIScene_SignEntryMenu = 29,
    UIScene_InGameInfoMenu = 30,
    UIScene_ConnectingProgress = 31,
    UIScene_DLCOffersMenu = 32,
    UIScene_TrialExitUpsell = 34,
    UIScene_LoadMenu = 35,
    UIScene_ReinstallMenu = 37,
    UIScene_SkinSelectMenu = 38,
    UIScene_InGameHostOptionsMenu = 40,
    UIScene_InGamePlayerOptionsMenu = 41,
    UIScene_CreativeMenu = 42,
    UIScene_LaunchMoreOptionsMenu = 43,
    UIScene_DLCMainMenu = 44,
    UIScene_NewUpdateMessage = 45,
    UIScene_EnchantingMenu = 46,
    UIScene_BrewingStandMenu = 47,
    UIScene_EndPoem = 48,
    UIScene_TradingMenu = 50,
    UIScene_AnvilMenu = 51,
    UIScene_TeleportMenu = 52,
    UIScene_HopperMenu = 53,
    UIScene_BeaconMenu = 54,
    UIScene_HorseInventoryMenu = 55,
    UIScene_ClassicCraftingMenu = 56,
    UIScene_SuperFlatMenu = 57,
    UIScene_SuperFlatEditLayer = 58,
    UIScene_SuperFlatPresets = 59,
    UIScene_GameModeScoreboardMenu = 60,
    UIScene_WritableBookMenu = 61,
    UIScene_MapVoteMenu = 62,
    UIScene_MapSelectMenu = 63,
    UIScene_BiomePreviewMenu = 64,
    UIScene_Keyboard = 72,
    UIScene_QuadrantSignin = 73,
    UIScene_MessageBox = 74,
    UIScene_Timer = 75,
    UIScene_EULA = 76,
    UIScene_InGameSaveManagementMenu = 77,
    UIScene_LanguageSelector = 78,
    UIScene_AchievementsMenu = 79,
    UIScene_BedrockUpsell = 80,
    UIScene_DefaultMAYBE = 81,

    UIComponent_TutorialPopup = 25,
    UIComponent_Chat = 36,
    UIScene_HUD = 49,
    UIComponent_Panorama = 65,
    UIComponent_Logo = 66,
    UIComponent_DebugUIConsole = 67,
    UIComponent_DebugUIMarketingGuide = 68,
    UIComponent_Tooltips = 69,
    UIComponent_PressStartToPlay = 70,
    UIComponent_MenuBackground = 71
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