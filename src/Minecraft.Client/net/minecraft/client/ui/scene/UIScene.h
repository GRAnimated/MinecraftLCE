#pragma once

#include "NX/Render/C4JRender.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

enum EUIMessage {};
struct fuiFile;
struct fuiRect;
class UILayer;
class UIControl;
class ItemInstance;

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
        int m_timeDelay;
        int m_nextTickTime;
        bool m_enabled;
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
    void customDrawSlotControlFui(fuiRect*, int, not_null_ptr<ItemInstance>, float, bool, bool, bool);

    void removeControl(UIControl_Base* control, bool);

    fuiFile* getFuiFile() { return this->m_fuiFile; }

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
    virtual bool isReadyToDelete();

    static void customDrawFui(void*, const char*, fuiRect*);

    std::wstring m_wstring8;
    fuiFile* m_fuiFile;
    bool m_bool28;
    char m_gap29[3];
    void* m_qword30;
    std::unordered_map<std::wstring, bool> m_ap1;
    std::unordered_map<int, UIScene::_TimerInfo> m_timersMap;
    int m_controlFocused;
    int m_controlChildFocus;
    float m_opacity;
    bool m_isInitializedMovie;
    bool m_visible;
    bool m_byte96;
    bool m_bool97;
    UIScene* m_backScene;
    void* m_callbackUniqueId;
    int m_resType;  // 0 - 1080p | 1 - 720p
    bool m_hidden;
    bool m_boolAd;
    int m_stageWidth;
    int m_stageHeight;
    int m_stageWidth2;
    int m_stageHeight2;
    std::vector<UIControl*> m_uiControls;
    UILayer* m_uiLayer;
    bool m_focusRelated;
    int m_padId;
    bool m_hideLowerScenes;
    bool m_byteE9;
    bool m_byteEa;
    bool m_byteEb;
    int m_dwordF8;
    std::vector<UIScene::_CachedSlotDrawData*> m_cachedSlotDrawData;
};
