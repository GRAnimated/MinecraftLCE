#pragma once

#include <string>

class GameType {
public:
    static GameType* NOT_SET;
    static GameType* SURVIVAL;
    static GameType* CREATIVE;
    static GameType* ADVENTURE;
    static GameType* SPECTATOR;
    static GameType* LOBBY;

    static void staticCtor();

    GameType(int, const std::wstring&, const std::wstring&, int, int);

private:
    int mId;
    std::wstring mName;
    std::wstring mTag;
    int field_38;
    int field_3C;
};
