#pragma once

enum eUpsellType {};
enum eUpsellResponse {};

class C_4JProfile {
public:
    virtual void Initialise(const void*, const void*, unsigned short, unsigned int, unsigned int,
                            unsigned int*, int, unsigned int*)
        = 0;
    virtual int GetLockedProfile() = 0;
    virtual void SetLockedProfile(int)
        = 0;  // guessing int here is flags provided by the OS when getting the user
    virtual bool IsSignedIn(int) = 0;
    virtual bool IsSignedInLive(int) = 0;
    virtual bool IsSigningIn(int) = 0;
    virtual bool IsGuest(int) = 0;
    virtual void sub_710079238C() = 0;               // Wii U says CProfile::RequestSignInUI
    virtual void SignInUser(void*, int) = 0;  // void * used to be MiiDataEntry
    virtual void sub_710079239C() = 0;
    virtual void sub_71007923AC() = 0;
    virtual void sub_71007923C0() = 0;
    virtual void sub_71007923F0() = 0;
    virtual void sub_7100792640() = 0;
    virtual void sub_710079188C() = 0;
    virtual void sub_7100791B48() = 0;
    virtual void sub_7100791B78() = 0;
    virtual void sub_7100792734() = 0;
    virtual void sub_71007926EC() = 0;
    virtual void sub_7100792BE8() = 0;
    virtual void sub_7100791DB0() = 0;
    virtual void sub_7100791F5C() = 0;
    virtual void sub_7100791FFC() = 0;
    virtual void sub_710079201C() = 0;
    virtual void sub_7100792750() = 0;
    virtual void sub_7100792028() = 0;
    virtual void sub_7100792184() = 0;
    virtual void sub_7100792754() = 0;
    virtual void sub_71007927BC() = 0;
    virtual void sub_7100791ECC() = 0;
    virtual void sub_7100791ED4() = 0;
    virtual void sub_7100791EDC() = 0;
    virtual int GetPrimaryPad() = 0;
    virtual void sub_7100794A3C() = 0;
    virtual void sub_7100794A78() = 0;
    virtual void sub_7100792A30() = 0;
    virtual void sub_7100792A54() = 0;
    virtual void sub_7100792AAC() = 0;
    virtual void sub_7100792BFC() = 0;
    virtual void sub_7100792C04() = 0;
    virtual void sub_7100792C0C() = 0;
    virtual bool IsFullVersion() = 0;
    virtual void SetFullVersion(bool v) = 0;
    virtual void SetSignInChangeCallback(void (*)(void*, bool, unsigned int), void*) = 0;
    virtual void sub_7100792C1C() = 0;
    virtual void sub_7100794A20() = 0;
    virtual void sub_7100794A2C() = 0;
    virtual void sub_7100794A34() = 0;
    virtual void sub_7100794B58() = 0;
    virtual void sub_7100794B50() = 0;
    virtual void SetProfileReadErrorCallback(void (*)(void*), void*) = 0;
    virtual void sub_710079235C() = 0;
    virtual void Tick() = 0;
    virtual void AwardManagerOnCreate() = 0;
    virtual void RegisterAward(int idx, int idx2, eAwardType type, int name, int desc) = 0;
    virtual void sub_71007A2DE4() = 0;
    virtual void sub_71007A2DEC() = 0;
    virtual void sub_71007A2DF4() = 0;
    virtual void sub_71007A2894() = 0;
    virtual void sub_71007A2994() = 0;
    virtual void SetOnAwardHandler(void (*)(), void*) = 0;
    virtual void sub_7100792C4C() = 0;
    virtual void RichPresenceRegisterPresenceString(int, int) = 0;
    virtual void RichPresenceRegisterContext(int, int) = 0;
    virtual void RichPresenceRegisterContextString(int, int, int) = 0;
    virtual void RichPresenceInit(int, int) = 0;
    virtual void sub_7100793CE0() = 0;
    virtual void sub_7100794404() = 0;
    virtual void sub_71007946A8() = 0;
    virtual void sub_71007946B0() = 0;
    virtual void sub_7100794804() = 0;
    virtual void SetRichPresenceGetStringCallback(wchar_t* (*)(int)) = 0;
    virtual void sub_7100792C38() = 0;
    virtual void sub_710079457C() = 0;
    virtual void sub_710079493C() = 0;
    virtual void SetUpsellCallback(void (*)(void*, eUpsellType, eUpsellResponse, int), void*) = 0;
    virtual void sub_7100794B6C() = 0;
    virtual void sub_71007929E4() = 0;
    virtual void sub_7100792A08() = 0;
    virtual void sub_7100792A24() = 0;
    virtual void sub_7100792BF4() = 0;
    virtual void sub_7100792AF0() = 0;
    virtual void sub_7100792AF4() = 0;
    virtual void sub_7100792BE0() = 0;
    virtual void sub_7100792B80() = 0;
    virtual void sub_7100792B7C() = 0;
    virtual void sub_7100792B74() = 0;
    virtual void sub_7100792B88() = 0;
    virtual void sub_7100792BC8() = 0;
    virtual void sub_7100792BD0() = 0;
    virtual void sub_7100792BD8() = 0;
    virtual void SetSignInChoicesCallback(int (*)(int)) = 0;
    virtual void sub_7100792C44() = 0;
    virtual void sub_7100791DAC() = 0;
    virtual void sub_7100791D54() = 0;
};
