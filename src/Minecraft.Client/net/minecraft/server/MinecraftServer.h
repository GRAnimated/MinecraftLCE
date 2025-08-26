#pragma once

#include <string>

class ServerLevel;
class LevelStorageSource;
class LevelType;
class _NetworkGameInitData;
class PlayerList;

class MinecraftServer {
public:
    static MinecraftServer* sInstance;
    static MinecraftServer* getInstance();

    // unknown name & location
    static PlayerList* tryGetPlayers() {
        if (sInstance) {
            return sInstance->mPlayers;
        }
        return nullptr;
    }

    void loadLevel(LevelStorageSource* source, const std::wstring& param_2, long long param_3,
                   LevelType* type, _NetworkGameInitData* initData);
    void saveGameRules();

    ServerLevel* getLevel(int);

    PlayerList* getPlayers();

    void* padding[5];
    PlayerList* mPlayers;
};
