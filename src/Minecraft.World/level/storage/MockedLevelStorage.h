#pragma once

#include "Minecraft.World/level/storage/LevelStorage.h"

class MockedLevelStorage : public LevelStorage {
public:
    ~MockedLevelStorage() override;
    LevelData* prepareLevel() override;
    void checkSession() override;
    ChunkStorage* createChunkStorage(Dimension*) override;
    void saveLevelData(LevelData*, std::vector<std::shared_ptr<Player>>*) override;
    void saveLevelData(LevelData*) override;
    PlayerIO* getPlayerIO() override;
    void closeAll() override;
    void getFolder() override;
    ConsoleSavePath getDataFile(const std::wstring&) override;
    void getLevelId() override;
    void getStructureManager() override;
    ConsoleSaveFile* getSaveFile() override;
};
