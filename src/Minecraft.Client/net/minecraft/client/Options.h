#pragma once

#include "net/minecraft/core/io/File.h"
#include <string>

class KeyMapping;
class Minecraft;
class File;

class Options {
public:
    class Option {
    public:
        static Option* off_7101122750;
        static Option* off_7101122758;
        static Option* off_7101122760;
        static Option* off_7101122768;
        static Option* off_7101122770;
        static Option* off_7101122778;
        static Option* off_7101122780;
        static Option* off_7101122788;
        static Option* off_7101122790;
        static Option* off_7101122798;
        static Option* off_71011227A0;
        static Option* off_71011227A8;
        static Option* off_71011227B0;
        static Option* off_71011227B8;
        static Option* off_71011227C0;
        static Option* off_71011227C8;
        static Option* off_71011227D0;
        static Option* off_71011227D8;

        Option(const std::wstring&, bool, bool);

        bool isProgress() const;
        std::wstring getCaptionId() const;

        bool mIsProgress;
        bool field_1;
        std::wstring mOptionName;
    };

    Options(Minecraft* minecraft, File file);
    void init();
    void save();

    std::wstring getKeyDescription(int key);
    std::wstring getKeyMessage(int key);
    void setKey(int key, int key2);

    void getMessage(const Option*);
    float getProgressValue(const Option*);

    float mMusicVolume;
    float mSoundVolume;
    float mMouseSensitivity;
    bool mInvertYMouse;
    int mViewDistance;
    bool mIsBobView;
    bool mIsAnaglyph3d;
    bool mIsAdvancedOpengl;
    bool gap_17;
    int mFpsLimit;
    bool mIsFancyGraphics;
    bool mIsEnableAo;
    bool mIsEnableClouds;
    bool byte_1f;
    std::wstring mSkin;
    KeyMapping* mKeyForward;
    KeyMapping* mKeyLeft;
    KeyMapping* mKeyBack;
    KeyMapping* mKeyRight;
    KeyMapping* mKeyJump;
    KeyMapping* mKeyInventory;
    KeyMapping* mKeyDrop;
    KeyMapping* mKeyChat;
    KeyMapping* mKeySneak;
    KeyMapping* mKeyAttack;
    KeyMapping* mKeyUse;
    KeyMapping* mKeyPlayerList;
    KeyMapping* mKeyPickItem;
    KeyMapping* mKeyFog;
    KeyMapping* mKeyMappings[14];
    Minecraft* mMinecraft;
    File mOptionsFile;
    int mDifficulty;
    bool byte_13c;
    void* qword_140;
    bool byte_148;
    int dword_14c;
    std::wstring mLastServer;
    bool byte_168;
    bool byte_169;
    bool byte_16a;
    bool gap_16B;
    float dword_16c;
    float dword_170;
    int mGuiScale;
    int mParticles;
    float mFov;
    float mGamma;
    bool byte_184;
};
