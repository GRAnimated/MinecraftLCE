#pragma once

class Level;
class LevelChunk;
class CompoundTag;

class ChunkStorage {
public:
    ChunkStorage();

    virtual ~ChunkStorage() {}
    virtual void load(Level*, int, int, LevelChunk*) = 0;
    virtual void save(Level*, LevelChunk*) = 0;
    virtual void saveEntities(Level*, LevelChunk*) = 0;
    virtual void tick() = 0;
    virtual void flush() = 0;
    virtual void WaitForAll();
    virtual void WaitIfTooManyQueuedChunks();
};