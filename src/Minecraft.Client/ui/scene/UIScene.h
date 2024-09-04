#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class C4JRender {
public:
    enum eViewportType {};
};
class EUIMessage;
class fuiFile;
class fuiRect;
class UILayer;

class UIScene {
public:
    class _CachedSlotDrawData;
    class _TimerInfo {
    public:
    };

    UIScene(int, UILayer*);

    virtual void reloadMovie(bool);
    virtual void needsReloaded();
    virtual void hasMovie();
    virtual void updateSafeZone();
    virtual void updateViewportTouchOffset();
    virtual void getSafeZoneHalfHeight();
    virtual void getSafeZoneHalfWidth();
    virtual void getMoviePath() = 0;
    virtual void mapElementsAndNames();
    virtual ~UIScene();
    virtual void getSceneType() = 0;
    virtual void getSubSceneType() const;
    virtual void tick();
    virtual void SetFocusToElement(int);
    virtual void handleTimerComplete(int);
    virtual void stealsFocus();
    virtual void hasFocus(int);
    virtual void updateTooltips();
    virtual void updateComponents();
    virtual void handleGainFocus(bool);
    virtual void handleLoseFocus();
    virtual void hidesLowerScenes();
    virtual void blocksInput();
    virtual void GetMainPanel();
    virtual void render(int, int, C4JRender::eViewportType);
    virtual void customDraw(char const*, fuiRect*);
    virtual void allowRepeat(int);
    virtual void handleInput(int, int, bool, bool, bool, bool const);
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

private:
    void* qword_8 = nullptr;
    void* qword_10 = nullptr;
    void* qword_18 = nullptr;
    fuiFile* mFuiFile = nullptr;
    void* qword_28 = nullptr;
    void* qword_30 = nullptr;
    std::unordered_map<std::wstring, bool> map1;
    std::unordered_map<int, UIScene::_TimerInfo> map2;
    int dword_88 = -1;
    int dword_8c = 0;
    float dword_90 = 1.0f;
    bool mIsInitializedMovie = false;
    bool byte_95 = true;
    bool byte_96 = false;
    bool bool_97 = false;
    UIScene* mBackScene = nullptr;
    void* qword_a0 = nullptr;
    int field_A8 = 0;
    bool bool_ac = false;
    bool bool_ad = false;
    int mStageWidth = 0;
    int mStageHeight = 0;
    int mStageWidth2 = 0;
    int mStageHeight2 = 0;
    std::vector<UIScene::_CachedSlotDrawData*> mCachedSlotDrawData;
    UILayer* mUILayer = nullptr;
    bool byte_e0 = false;
    int dword_e4 = 0;
    bool mIsHideLowerScenes = false;
    bool byte_e9 = false;
    bool byte_ea = true;
    bool byte_eb = false;
    int dword_ec = 0;
    std::wstring string1 = nullptr;
};