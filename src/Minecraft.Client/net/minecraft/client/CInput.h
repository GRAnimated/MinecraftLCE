#pragma once

#include "types.h"

class _STRING_VERIFY_RESPONSE;

class C_4JInput {
public:
    enum ETouchType {};
    enum EKeyboardMode {};

    virtual void Initialise(int, uchar, uchar) = 0;
    virtual void Tick(void) = 0;
    virtual void SetDeadzoneAndMovementRange(uint, uint, uint) = 0;
    virtual void SetGameControllerTypeJoypadMaps(int, uchar, uint) = 0;
    virtual void SetGameJoypadMaps(int, uchar, uint) = 0;
    virtual void GetGameJoypadMaps(int, uchar) = 0;
    virtual void SetJoypadMapArraySetupComplete(void) = 0;
    virtual void SetJoypadSensitivity(int, float) = 0;
    virtual void GetValue(int, uchar, bool) = 0;
    virtual void SetFakePadValue(int, uchar) = 0;
    virtual void ButtonPressed(int, uchar, uint) = 0;
    virtual void ButtonReleased(int, uchar) = 0;
    virtual void ButtonDown(int, uchar) = 0;
    virtual void SetJoypadStickAxisMap(int, uint, uint) = 0;
    virtual void SetJoypadStickTriggerMap(int, uint, uint) = 0;
    virtual void SetKeyRepeatRate(float, float) = 0;
    virtual void SetDebugSequence(const char*, int (*)(void*), void*) = 0;
    virtual void GetIdleSeconds(int) = 0;
    virtual void IsPadConnected(int) = 0;
    virtual void SetCircleCrossSwapped(bool) = 0;
    virtual bool IsCircleCrossSwapped(void) = 0;
    virtual void func_7100790784(void) = 0;
    virtual void MapTouchInput(int, uint) = 0;
    virtual float GetJoypadStick_Menu_LX(int) = 0;
    virtual float GetJoypadStick_Menu_LY(int) = 0;
    virtual float GetJoypadStick_Menu_RX(int) = 0;
    virtual float GetJoypadStick_Menu_RY(int) = 0;
    virtual void GetJoypadLTrigger_Menu(int) = 0;
    virtual void GetJoypadRTrigger_Menu(int) = 0;
    virtual float GetJoypadStick_LX(int, bool) = 0;
    virtual float GetJoypadStick_LY(int, bool) = 0;
    virtual float GetJoypadStick_RX(int, bool) = 0;
    virtual float GetJoypadStick_RY(int, bool) = 0;
    virtual void GetJoypadLTrigger(int, bool) = 0;
    virtual void GetJoypadRTrigger(int, bool) = 0;
    virtual void GetTouchPadData(int, C_4JInput::ETouchType, bool) = 0;
    virtual void SetMenuDisplayed(int, bool) = 0;
    virtual void func_7100790580(void) = 0;
    virtual void RequestKeyboard(const wchar_t*, const wchar_t*, uint, uint, int (*)(void*, bool), void*,
                                 C_4JInput::EKeyboardMode)
        = 0;
    virtual void RequestErrorViewer(uint, uint, int (*)(void*), void*) = 0;
    virtual void RequestErrorViewer(uint, wchar_t*, wchar_t*, int (*)(void*), void*) = 0;
    virtual void SetLocalMultiplayer(bool) = 0;
    virtual void IsLocalMultiplayerAvailable(void) = 0;
    virtual void UsingRemoteVita(void) = 0;
    virtual void VerifyStrings(wchar_t**, int, int (*)(void*, _STRING_VERIFY_RESPONSE*), void*) = 0;
    virtual void CancelQueuedVerifyStrings(int (*)(void*, _STRING_VERIFY_RESPONSE*), void*) = 0;
    virtual void CancelAllVerifyInProgress(void) = 0;
    virtual void LockPad(int, int) = 0;
    virtual void UnlockPad(int) = 0;
    virtual void IsPadLocked(int) = 0;
    virtual void GetControllerID(int) = 0;
    virtual void AcquiredForeground(void) = 0;
};

class CInput : public C_4JInput {
public:
    static CInput* sInstance;
    static unsigned int sControllers;  // seems like a good place

    void Initialise(int, uchar, uchar);
    void Tick();
    void SetDeadzoneAndMovementRange(uint, uint, uint);
    void SetGameControllerTypeJoypadMaps(int, uchar, uint);
    void SetGameJoypadMaps(int, uchar, uint);
    void GetGameJoypadMaps(int, uchar);
    void SetJoypadMapArraySetupComplete();
    void SetJoypadSensitivity(int, float);
    void GetValue(int, uchar, bool);
    void SetFakePadValue(int, uchar);
    void ButtonPressed(int, uchar, uint);
    void ButtonReleased(int, uchar);
    void ButtonDown(int, uchar);
    void SetJoypadStickAxisMap(int, uint, uint);
    void SetJoypadStickTriggerMap(int, uint, uint);
    void SetKeyRepeatRate(float, float);
    void SetDebugSequence(const char*, int (*)(void*), void*);
    void GetIdleSeconds(int);
    void IsPadConnected(int);
    void SetCircleCrossSwapped(bool);
    bool IsCircleCrossSwapped();
    void func_7100790784();
    void MapTouchInput(int, uint);
    float GetJoypadStick_Menu_LX(int);
    float GetJoypadStick_Menu_LY(int);
    float GetJoypadStick_Menu_RX(int);
    float GetJoypadStick_Menu_RY(int);
    void GetJoypadLTrigger_Menu(int);
    void GetJoypadRTrigger_Menu(int);
    float GetJoypadStick_LX(int, bool);
    float GetJoypadStick_LY(int, bool);
    float GetJoypadStick_RX(int, bool);
    float GetJoypadStick_RY(int, bool);
    void GetJoypadLTrigger(int, bool);
    void GetJoypadRTrigger(int, bool);
    void GetTouchPadData(int, C_4JInput::ETouchType, bool);
    void SetMenuDisplayed(int, bool);
    void func_7100790580();
    void RequestKeyboard(const wchar_t*, const wchar_t*, uint, uint, int (*)(void*, bool), void*,
                         C_4JInput::EKeyboardMode);
    void RequestErrorViewer(uint, uint, int (*)(void*), void*);
    void RequestErrorViewer(uint, wchar_t*, wchar_t*, int (*)(void*), void*);
    void SetLocalMultiplayer(bool);
    void IsLocalMultiplayerAvailable();
    void UsingRemoteVita();
    void VerifyStrings(wchar_t**, int, int (*)(void*, _STRING_VERIFY_RESPONSE*), void*);
    void CancelQueuedVerifyStrings(int (*)(void*, _STRING_VERIFY_RESPONSE*), void*);
    void CancelAllVerifyInProgress();
    void LockPad(int, int);
    void UnlockPad(int);
    void IsPadLocked(int);
    void GetControllerID(int);
    void AcquiredForeground();
};
