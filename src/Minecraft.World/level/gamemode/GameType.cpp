#include "Minecraft.World/level/gamemode/GameType.h"

void GameType::staticCtor() {
    NOT_SET = new GameType(-1, L"", L"", -1, -1);
    SURVIVAL = new GameType(0, L"survival", L"s", 0x15AA0E94, 0x9BA782A6);
    CREATIVE = new GameType(1, L"creative", L"c", 0xB7C2FCAF, 0x12D696DD);
    ADVENTURE = new GameType(2, L"adventure", L"a", 0xA48E97FA, 0xF9915358);
    SPECTATOR = new GameType(3, L"spectator", L"sp", -1, -1);
    LOBBY = new GameType(4, L"lobby", L"l", -1, -1);
}

GameType::GameType(int id, const std::wstring& name, const std::wstring& tag, int field_38, int field_3C) {
    mId = id;
    mName = name;
    mTag = tag;
    this->field_38 = field_38;
    this->field_3C = field_3C;
}
