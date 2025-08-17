#pragma once

#include <memory>

class Dimension;
class LevelData;
class PlayerUID;
class Player;
class ChunkStorage;
class PlayerIO;
class ConsoleSavePath;
class ConsoleSaveFile;

class LevelStorage {
public:
    LevelStorage();

    virtual ~LevelStorage();
    virtual LevelData* prepareLevel() = 0;
    virtual void checkSession() = 0;
    virtual ChunkStorage* createChunkStorage(Dimension*) = 0;
    virtual void saveLevelData(LevelData*, std::vector<std::shared_ptr<Player>>*) = 0;
    virtual void saveLevelData(LevelData*) = 0;
    virtual PlayerIO* getPlayerIO() = 0;
    virtual void closeAll() = 0;
    virtual void getFolder() = 0;
    virtual ConsoleSavePath getDataFile(const std::wstring&) = 0;
    virtual void getLevelId() = 0;
    virtual void getStructureManager() = 0;
    virtual ConsoleSaveFile* getSaveFile();
    virtual void flushSaveFile(bool);
    virtual int getAuxValueForMap(PlayerUID, int, int, int, int);
};
