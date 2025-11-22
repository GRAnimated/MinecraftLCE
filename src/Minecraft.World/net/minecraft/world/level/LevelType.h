#pragma once

#include <string>

class LevelType {
public:
    static LevelType* NORMAL;
    static LevelType* FLAT;
    static LevelType* LARGE_BIOMES;
    static LevelType* AMPLIFIED;
    static LevelType* CUSTOMIZED;
    static LevelType* NORMAL_1_1;

    static LevelType* TYPES[16];

    LevelType(int id, const std::wstring& name, int version);
    LevelType(int id, const std::wstring& name);

    void _init(int id, const std::wstring& name, int version);

    std::wstring getGeneratorName();
    int getVersion();

    LevelType* setHasReplacement();
    LevelType* setHasHelpText();
    LevelType* setSelectableByUser(bool state);

    static void staticCtor();

    int mId;
    std::wstring mName;
    int mVersion;
    bool mSelectableByUser;
    bool mHasReplacement;
    bool mHasHelpText;
};
