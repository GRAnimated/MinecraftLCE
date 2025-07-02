#pragma once
class C_4JProfile {
public:
    virtual void Initialise(const void*, const void*, unsigned short, unsigned int, unsigned int,
                            unsigned int*, int, unsigned int*)
        = 0;
    virtual int GetLockedProfile() = 0;
    virtual void SetLockedProfile(int)
        = 0;  // guessing int here is flags provided by the OS when getting the user
    virtual bool IsSignedInt(int) = 0;
    virtual bool IsSignedInLive(int) = 0;
    virtual bool IsSigningIn(int) = 0;
    virtual bool IsGuest(int) = 0;
    virtual void unk() = 0;               // Wii U says CProfile::RequestSignInUI
    virtual void SignInUser(void*, int);  // void * used to be MiiDataEntry
    virtual void unk2() = 0;
    virtual void unk3() = 0;
    virtual void unk4() = 0;
    virtual void unk5() = 0;
    virtual void unk6() = 0;
    virtual void unk7() = 0;
    virtual void unk8() = 0;
    virtual void unk9() = 0;
    virtual void unk10() = 0;
    virtual void unk11() = 0;
    virtual void unk12() = 0;
    virtual void unk13() = 0;
    virtual void unk14() = 0;
    virtual void unk15() = 0;
    virtual void unk16() = 0;
    virtual void unk17() = 0;
    virtual void unk18() = 0;
    virtual void unk19() = 0;
    virtual void unk20() = 0;
    virtual void unk21() = 0;
    virtual void unk22() = 0;
    virtual void unk23() = 0;
    virtual void unk24() = 0;
    virtual void unk25() = 0;
    virtual void unk26() = 0;
    virtual void unk27() = 0;
    virtual void unk28() = 0;
    virtual void unk29() = 0;
    virtual void unk30() = 0;
    virtual void unk31() = 0;
    virtual void unk32() = 0;
    virtual void unk33() = 0;
    virtual bool IsFullVersion() = 0;
    virtual void SetFullVersion(bool v) = 0;
    virtual void SetSignInChangeCallback(void (*)(void*, bool, unsigned int), void*) = 0;
    virtual void unk34() = 0;
    virtual void unk35() = 0;
    virtual void unk36() = 0;
    virtual void unk37() = 0;
    virtual void unk38() = 0;
    virtual void unk39() = 0;
    virtual void SetProfileReadErrorCallback(void (*)(void*), void*) = 0;
};
