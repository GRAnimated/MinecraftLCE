#pragma once

#include "net/minecraft/server/ConsoleInputStream.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include <string>

class ServerLevel;
class LevelStorageSource;
class LevelType;
class _NetworkGameInitData;
class PlayerList;
class ChunkSource;
class ChunkGenerator;
class ServerConnection;
class Settings;

class MinecraftServer : ConsoleInputStream {
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
    void setPvpAllowed(bool);
    void addPostProcessRequest(ChunkSource*, ChunkGenerator*, int, int);

    ServerLevel* getLevel(int);
    PlayerList* getPlayers();

    void info(const std::wstring&) override;
    void warn(const std::wstring&) override;
    std::wstring getConsoleName() override;

    ServerConnection* mConnection;
    Settings* mSettings;
    arrayWithLength<ServerLevel*> mLevels;
    PlayerList* mPlayers;
};
