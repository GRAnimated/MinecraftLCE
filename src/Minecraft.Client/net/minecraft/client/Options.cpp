#include "Minecraft.Client/Options.h"

#include "Minecraft.Client/KeyMapping.h"
#include "Minecraft.Client/resources/language/Language.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Core/io/FileOutputStream.h"

Options::Option::Option(const std::wstring& a2, bool isProgress, bool a4)
    : mIsProgress(isProgress), field_1(a4), mOptionName(a2) {}

bool Options::Option::isProgress() const {
    return mIsProgress;
}

std::wstring Options::Option::getCaptionId() const {
    return mOptionName;
}

Options::Options(Minecraft* minecraft, File file) {
    init();
    mMinecraft = minecraft;
    mOptionsFile = File(file, L"options.txt");
}

void Options::init() {
    mMusicVolume = 1.0;
    mSoundVolume = 1.0;
    mMouseSensitivity = 0.5;
    mInvertYMouse = false;
    mViewDistance = false;
    mIsBobView = true;
    mIsAnaglyph3d = false;
    mIsAdvancedOpengl = false;
    mFpsLimit = 2;
    mIsFancyGraphics = true;
    mIsEnableAo = true;
    mIsEnableClouds = true;
    mSkin = L"Default";

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
    mDifficulty = 2;
    byte_13c = false;
    qword_140 = nullptr;
    byte_148 = false;
    dword_14c = 0;
    mLastServer = L"";
    byte_168 = false;
    byte_169 = false;
    byte_16a = false;
    dword_16c = 1.0;
    dword_170 = 1.0;
    mGuiScale = 0;
    mParticles = 0;
    mFov = 0;
    mGamma = 0;
    byte_184 = true;
    byte_1f = true;
}

void Options::save() {
    FileOutputStream output = FileOutputStream(mOptionsFile);
    DataOutputStream dataOutput = DataOutputStream(&output);

    dataOutput.writeChars(L"music:" + std::to_wstring(mMusicVolume) + L"\n");
    dataOutput.writeChars(L"sound:" + std::to_wstring(mSoundVolume) + L"\n");
    dataOutput.writeChars(L"invertYMouse:" + std::wstring(mInvertYMouse ? L"true" : L"false") + L"\n");
    dataOutput.writeChars(L"mouseSensitivity:" + std::to_wstring(mMouseSensitivity));
    dataOutput.writeChars(L"fov:" + std::to_wstring(mFov));
    dataOutput.writeChars(L"gamma:" + std::to_wstring(mGamma));
    dataOutput.writeChars(L"viewDistance:" + std::to_wstring(mViewDistance));
    dataOutput.writeChars(L"guiScale:" + std::to_wstring(mGuiScale));
    dataOutput.writeChars(L"particles:" + std::to_wstring(mParticles));
    dataOutput.writeChars(L"bobView:" + std::wstring(mIsBobView ? L"true" : L"false"));
    dataOutput.writeChars(L"anaglyph3d:" + std::wstring(mIsAnaglyph3d ? L"true" : L"false"));
    dataOutput.writeChars(L"advancedOpengl:" + std::wstring(mIsAdvancedOpengl ? L"true" : L"false"));
    dataOutput.writeChars(L"fpsLimit:" + std::to_wstring(mFpsLimit));
    dataOutput.writeChars(L"difficulty:" + std::to_wstring(mDifficulty));
    dataOutput.writeChars(L"fancyGraphics:" + std::wstring(mIsFancyGraphics ? L"true" : L"false"));
    dataOutput.writeChars(L"ao:" + std::wstring(mIsEnableAo ? L"true" : L"false"));
    dataOutput.writeChars(L"clouds:" + std::wstring(std::to_wstring(mIsEnableClouds)));
    dataOutput.writeChars(L"skin:" + mSkin);
    dataOutput.writeChars(L"lastServer:" + mLastServer);
    for (int i = 0; i < 14; i++) {
        dataOutput.writeChars(L"key_" + mKeyMappings[i]->mKeyDescription + L":"
                              + std::to_wstring(mKeyMappings[i]->mKeyCode));
    }

    dataOutput.close();
}

// NON_MATCHING: Unfinished
void Options::getMessage(const Option* option) {
    Language* language = Language::getInstance();
    std::wstring captionId = option->getCaptionId();
    std::wstring element = language->getElement(captionId).append(L": ");

    /*
    if (option->isProgress()) {
        float progressValue = getProgressValue(option);
        if (Option::off_7101122768 != option) {
            if (Option::off_71011227B8 != option) {
                if (Option::off_71011227C0 == option) {
                    const wchar_t* v11;
                    if (progressValue == 0.0) {
                        v11 = L"options.gamma.min";
                    } else {
                        if (progressValue == 1.0) {

                        }
                        v11 = L"options.gamma.max";
                    }
                }
            }
        }
    }
    */
}
