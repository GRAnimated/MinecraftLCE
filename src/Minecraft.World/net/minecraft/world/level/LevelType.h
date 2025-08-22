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

    std::wstring getGeneratorName();
    int getVersion();
};
