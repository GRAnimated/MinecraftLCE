#include "Minecraft.Client/Options.h"
#include "Minecraft.Client/KeyMapping.h"

Options::Options(Minecraft* minecraft, File file) {
    init();
    mMinecraft = minecraft;
    mOptionsFile = File(file, L"options.txt");
}

void Options::init() {
    mMusicVolume = 1.0;
    mSoundVolume = 1.0;
    mSensitivity = 0.5;
    mInvertYMouse = false;
    dword_10 = false;
    byte_14 = true;
    byte_15 = false;
    byte_16 = false;
    dword_18 = 2;
    byte_1c = true;
    byte_1d = true;
    byte_1e = true;
    field_20 = L"Default";

    mKeyForward = new KeyMapping(L"key.forward", 22);
    mKeyLeft = new KeyMapping(L"key.left", 0);
    mKeyBack = new KeyMapping(L"key.back", 18);
    mKeyRight = new KeyMapping(L"key.right", 3);
    mKeyJump = new KeyMapping(L"key.jump", 26);
    mKeyInventory = new KeyMapping(L"key.inventory", 4);
    mKeyDrop = new KeyMapping(L"key.drop", 16);
    mKeyChat = new KeyMapping(L"key.chat", 19);
    mKeySneak = new KeyMapping(L"key.sneak", 27);
    mKeyAttack = new KeyMapping(L"key.attack", -100);
    mKeyUse = new KeyMapping(L"key.use", -99);
    mKeyPlayerList = new KeyMapping(L"key.playerlist", 34);
    mKeyPickItem = new KeyMapping(L"key.pickItem", -98);
    mKeyFog = new KeyMapping(L"key.fog", 5);

    mKeyMappings[0] = mKeyAttack;
    mKeyMappings[1] = mKeyUse;
    mKeyMappings[2] = mKeyForward;
    mKeyMappings[3] = mKeyLeft;
    mKeyMappings[4] = mKeyBack;
    mKeyMappings[5] = mKeyRight;
    mKeyMappings[6] = mKeyJump;
    mKeyMappings[7] = mKeySneak;
    mKeyMappings[8] = mKeyDrop;
    mKeyMappings[9] = mKeyInventory;
    mKeyMappings[10] = mKeyChat;
    mKeyMappings[11] = mKeyPlayerList;
    mKeyMappings[12] = mKeyPickItem;
    mKeyMappings[13] = mKeyFog;

    mMinecraft = nullptr;
    dword_138 = 2;
    byte_13c = false;
    qword_140 = nullptr;
    byte_148 = false;
    dword_14c = 0;
    field_150 = L"";
    byte_168 = false;
    byte_169 = false;
    byte_16a = false;
    dword_16c = 1.0;
    dword_170 = 1.0;
    mMaxScreenScale = 0;
    qword_178 = nullptr;
    dword_180 = 0;
    byte_184 = true;
    byte_1f = true;
}
