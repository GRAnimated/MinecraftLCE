#pragma once

#include <string>
#include "Minecraft.Core/io/File.h"

class KeyMapping;
class Minecraft;
class File;

class Options {
public:
    Options(Minecraft* minecraft, File file);
    void init();

    float mMusicVolume;
    float mSoundVolume;
    float mSensitivity;
    bool mInvertYMouse;
    int dword_10;
    bool byte_14;
    bool byte_15;
    bool byte_16;
    bool gap_17;
    int dword_18;
    bool byte_1c;
    bool byte_1d;
    bool byte_1e;
    bool byte_1f;
    std::wstring field_20;
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
    int dword_138;
    bool byte_13c;
    void* qword_140;
    bool byte_148;
    int dword_14c;
    std::wstring field_150;
    bool byte_168;
    bool byte_169;
    bool byte_16a;
    bool gap_16B;
    float dword_16c;
    float dword_170;
    int mMaxScreenScale;
    void* qword_178;
    int dword_180;
    bool byte_184;
};
