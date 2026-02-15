#include "net/minecraft/client/Options.h"

#include "java/io/DataOutputStream.h"
#include "java/io/FileOutputStream.h"
#include "net/minecraft/client/KeyMapping.h"
#include "net/minecraft/locale/Language.h"

Options::Option::Option(const std::wstring& a2, bool isProgress, bool a4)
    : m_isProgress(isProgress), m_field1(a4), m_optionName(a2) {}

bool Options::Option::isProgress() const {
    return m_isProgress;
}

std::wstring Options::Option::getCaptionId() const {
    return m_optionName;
}

Options::Options(Minecraft* minecraft, File file) {
    init();
    m_minecraft = minecraft;
    m_optionsFile = File(file, L"options.txt");
}

void Options::init() {
    m_musicVolume = 1.0;
    m_soundVolume = 1.0;
    m_mouseSensitivity = 0.5;
    m_invertYMouse = false;
    m_viewDistance = false;
    m_isBobView = true;
    m_isAnaglyph3d = false;
    m_isAdvancedOpengl = false;
    m_fpsLimit = 2;
    m_isFancyGraphics = true;
    m_isEnableAo = true;
    m_isEnableClouds = true;
    m_skin = L"Default";

    m_keyForward = new KeyMapping(L"key.forward", 22);
    m_keyLeft = new KeyMapping(L"key.left", 0);
    m_keyBack = new KeyMapping(L"key.back", 18);
    m_keyRight = new KeyMapping(L"key.right", 3);
    m_keyJump = new KeyMapping(L"key.jump", 26);
    m_keyInventory = new KeyMapping(L"key.inventory", 4);
    m_keyDrop = new KeyMapping(L"key.drop", 16);
    m_keyChat = new KeyMapping(L"key.chat", 19);
    m_keySneak = new KeyMapping(L"key.sneak", 27);
    m_keyAttack = new KeyMapping(L"key.attack", -100);
    m_keyUse = new KeyMapping(L"key.use", -99);
    m_keyPlayerList = new KeyMapping(L"key.playerlist", 34);
    m_keyPickItem = new KeyMapping(L"key.pickItem", -98);
    m_keyFog = new KeyMapping(L"key.fog", 5);

    m_keyMappings[0] = m_keyAttack;
    m_keyMappings[1] = m_keyUse;
    m_keyMappings[2] = m_keyForward;
    m_keyMappings[3] = m_keyLeft;
    m_keyMappings[4] = m_keyBack;
    m_keyMappings[5] = m_keyRight;
    m_keyMappings[6] = m_keyJump;
    m_keyMappings[7] = m_keySneak;
    m_keyMappings[8] = m_keyDrop;
    m_keyMappings[9] = m_keyInventory;
    m_keyMappings[10] = m_keyChat;
    m_keyMappings[11] = m_keyPlayerList;
    m_keyMappings[12] = m_keyPickItem;
    m_keyMappings[13] = m_keyFog;

    m_minecraft = nullptr;
    m_difficulty = 2;
    m_byte13c = false;
    m_qword140 = nullptr;
    m_byte148 = false;
    m_dword14c = 0;
    m_lastServer = L"";
    m_byte168 = false;
    m_byte169 = false;
    m_byte16a = false;
    m_dword16c = 1.0;
    m_dword170 = 1.0;
    m_guiScale = 0;
    m_particles = 0;
    m_fov = 0;
    m_gamma = 0;
    m_byte184 = true;
    m_byte1f = true;
}

void Options::save() {
    FileOutputStream output = FileOutputStream(m_optionsFile);
    DataOutputStream dataOutput = DataOutputStream(&output);

    dataOutput.writeChars(L"music:" + std::to_wstring(m_musicVolume) + L"\n");
    dataOutput.writeChars(L"sound:" + std::to_wstring(m_soundVolume) + L"\n");
    dataOutput.writeChars(L"invertYMouse:" + std::wstring(m_invertYMouse ? L"true" : L"false") + L"\n");
    dataOutput.writeChars(L"mouseSensitivity:" + std::to_wstring(m_mouseSensitivity));
    dataOutput.writeChars(L"fov:" + std::to_wstring(m_fov));
    dataOutput.writeChars(L"gamma:" + std::to_wstring(m_gamma));
    dataOutput.writeChars(L"viewDistance:" + std::to_wstring(m_viewDistance));
    dataOutput.writeChars(L"guiScale:" + std::to_wstring(m_guiScale));
    dataOutput.writeChars(L"particles:" + std::to_wstring(m_particles));
    dataOutput.writeChars(L"bobView:" + std::wstring(m_isBobView ? L"true" : L"false"));
    dataOutput.writeChars(L"anaglyph3d:" + std::wstring(m_isAnaglyph3d ? L"true" : L"false"));
    dataOutput.writeChars(L"advancedOpengl:" + std::wstring(m_isAdvancedOpengl ? L"true" : L"false"));
    dataOutput.writeChars(L"fpsLimit:" + std::to_wstring(m_fpsLimit));
    dataOutput.writeChars(L"difficulty:" + std::to_wstring(m_difficulty));
    dataOutput.writeChars(L"fancyGraphics:" + std::wstring(m_isFancyGraphics ? L"true" : L"false"));
    dataOutput.writeChars(L"ao:" + std::wstring(m_isEnableAo ? L"true" : L"false"));
    dataOutput.writeChars(L"clouds:" + std::wstring(std::to_wstring(m_isEnableClouds)));
    dataOutput.writeChars(L"skin:" + m_skin);
    dataOutput.writeChars(L"lastServer:" + m_lastServer);
    for (int i = 0; i < 14; i++) {
        dataOutput.writeChars(L"key_" + m_keyMappings[i]->m_keyDescription + L":"
                              + std::to_wstring(m_keyMappings[i]->m_keyCode));
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
