#pragma once
#include <string>

class Level;
class LevelStorageSource;
class LevelType;
class _NetworkGameInitData;
class PlayerList;

class MinecraftServer {
public:
    static MinecraftServer* sInstance;
    static MinecraftServer* getInstance();

    void loadLevel(LevelStorageSource* source, const std::wstring& param_2, long long param_3,
                   LevelType* type, _NetworkGameInitData* initData);
    void saveGameRules();

    Level* getLevel(int);

    PlayerList* getPlayers();
};
