#pragma once

#include "Minecraft.Client/renderer/C4JRender.h"
#include <string>
#include <unordered_map>
#include <vector>

enum EUIMessage {};
class fuiFile;
class fuiRect;
class UILayer;
class UIControl;

class UIScene {
public:
    class _CachedSlotDrawData;
    class _TimerInfo {
    public:
    };

    UIScene(int, UILayer*);

    void setSafeZone(double, double, double, double);
    void tickTimers();
    // void handleFocusChange(int, int);

    virtual void reloadMovie(bool);
    virtual bool needsReloaded();
    virtual bool hasMovie();
    virtual void updateSafeZone();
    virtual void updateViewportTouchOffset();
    virtual double getSafeZoneHalfHeight();
    virtual double getSafeZoneHalfWidth();
    virtual void getMoviePath() = 0;
    virtual bool mapElementsAndNames();
    virtual ~UIScene();
    virtual void getSceneType() = 0;
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
    virtual void customDraw(char const*, fuiRect*);
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

private:
    std::wstring wstring_8;
    fuiFile* mFuiFile;
    bool bool_28;
    char gap_29[3];
    void* qword30;
    std::unordered_map<std::wstring, bool> map1;
    std::unordered_map<int, UIScene::_TimerInfo> map2;
    int mControlFocus;
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