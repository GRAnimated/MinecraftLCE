#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include <vector>

class BoundingBox;
class ChunkPos;
class DataInputStream;
class DataOutputStream;
class Level;
class Random;
class StructurePiece;

class StructureStart {
public:
    StructureStart();
    StructureStart(int chunkX, int chunkZ);
    virtual ~StructureStart();
    virtual void postProcess(Level*, Random&, BoundingBox*);
    virtual arrayWithLength<unsigned char> createTag(int chunkX, int chunkZ);
    virtual void addAdditionalSaveData(DataOutputStream*);
    virtual void load(Level*, DataInputStream*);
    virtual void readAdditionalSaveData(DataInputStream*);
    virtual bool isValid();
    virtual bool isValidForPostProcess(ChunkPos*);
    virtual void notifyPostProcessAt(ChunkPos*);
    virtual int GetType() = 0;

    std::vector<StructurePiece*>* getPieces();
    BoundingBox* getBoundingBox();
    int getChunkX();
    int getChunkZ();
    void setDirty();
    void clearDirty();
    bool isDirty();
    void calculateBoundingBox();
    void moveBelowSeaLevel(Level*, Random&, int padding);
    void moveInsideHeights(Level*, Random&, int minY, int maxY);

    std::vector<StructurePiece*> m_pieces;
    BoundingBox* m_boundingBox;
    int m_chunkX;
    int m_chunkZ;
    bool m_dirty;
};

static_assert(sizeof(StructureStart) == 0x38, "Switch structure start layout");
