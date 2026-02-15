#pragma once

#include "java/io/File.h"
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

        bool m_isProgress;
        bool m_field1;
        std::wstring m_optionName;
    };

    Options(Minecraft* minecraft, File file);
    void init();
    void save();

    std::wstring getKeyDescription(int key);
    std::wstring getKeyMessage(int key);
    void setKey(int key, int key2);

    void getMessage(const Option*);
    float getProgressValue(const Option*);

    float m_musicVolume;
    float m_soundVolume;
    float m_mouseSensitivity;
    bool m_invertYMouse;
    int m_viewDistance;
    bool m_isBobView;
    bool m_isAnaglyph3d;
    bool m_isAdvancedOpengl;
    bool m_gap17;
    int m_fpsLimit;
    bool m_isFancyGraphics;
    bool m_isEnableAo;
    bool m_isEnableClouds;
    bool m_byte1f;
    std::wstring m_skin;
    KeyMapping* m_keyForward;
    KeyMapping* m_keyLeft;
    KeyMapping* m_keyBack;
    KeyMapping* m_keyRight;
    KeyMapping* m_keyJump;
    KeyMapping* m_keyInventory;
    KeyMapping* m_keyDrop;
    KeyMapping* m_keyChat;
    KeyMapping* m_keySneak;
    KeyMapping* m_keyAttack;
    KeyMapping* m_keyUse;
    KeyMapping* m_keyPlayerList;
    KeyMapping* m_keyPickItem;
    KeyMapping* m_keyFog;
    KeyMapping* m_keyMappings[14];
    Minecraft* m_minecraft;
    File m_optionsFile;
    int m_difficulty;
    bool m_byte13c;
    void* m_qword140;
    bool m_byte148;
    int m_dword14c;
    std::wstring m_lastServer;
    bool m_byte168;
    bool m_byte169;
    bool m_byte16a;
    bool m_gap16B;
    float m_dword16c;
    float m_dword170;
    int m_guiScale;
    int m_particles;
    float m_fov;
    float m_gamma;
    bool m_byte184;
};
