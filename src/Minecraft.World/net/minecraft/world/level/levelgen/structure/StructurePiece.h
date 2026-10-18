#pragma once

#include <vector>

class BlockPos;
class BlockState;
class BoundingBox;
class CompoundTag;
class DataInputStream;
class DataOutputStream;
class Direction;
class Level;
class Mirror;
class Random;
class ResourceLocation;
class Rotation;
class StructureManager;

class StructurePiece {
public:
    class BlockSelector {
    public:
        BlockSelector();
        virtual ~BlockSelector();
        virtual void next(Random&, int x, int y, int z, bool boundary) = 0;
        virtual const BlockState* getNext();

        const BlockState* m_next;
    };

    StructurePiece();
    explicit StructurePiece(int genDepth);

    virtual int GetType() = 0;
    virtual ~StructurePiece();
    virtual CompoundTag* createTag();
    virtual void addAdditionalSaveData(DataOutputStream*) = 0;
    virtual void load(Level*, DataInputStream*);
    virtual void readAdditionalSaveData(DataInputStream*, StructureManager*) = 0;
    virtual void addChildren(StructurePiece*, std::vector<StructurePiece*>*, Random&);
    virtual bool postProcess(Level*, Random&, BoundingBox*) = 0;
    virtual BoundingBox* getBoundingBox();
    virtual BlockPos* getLocatorPosition();
    virtual void placeBlock(Level*, const BlockState*, int, int, int, BoundingBox*);
    virtual const BlockState* getBlock(Level*, int, int, int, BoundingBox*);
    virtual int getSkyBrightness(Level*, int, int, int, BoundingBox*);
    virtual void generateAirBox(Level*, BoundingBox*, int, int, int, int, int, int);
    virtual void generateBox(Level*, BoundingBox*, int, int, int, int, int, int, const BlockState*,
                             const BlockState*, bool);
    virtual void generateBox(Level*, BoundingBox*, BoundingBox*, const BlockState*, const BlockState*, bool);
    virtual void generateBox(Level*, BoundingBox*, int, int, int, int, int, int, bool, Random&,
                             BlockSelector*);
    virtual void generateBox(Level*, BoundingBox*, BoundingBox*, bool, Random&, BlockSelector*);
    virtual void generateMaybeBox(Level*, BoundingBox*, Random&, float, int, int, int, int, int, int,
                                  const BlockState*, const BlockState*, bool, int maxSkyBrightness);
    virtual void maybeGenerateBlock(Level*, BoundingBox*, Random&, float, int, int, int, const BlockState*);
    virtual void generateUpperHalfSphere(Level*, BoundingBox*, int, int, int, int, int, int,
                                         const BlockState*, bool);
    virtual void generateFullSphere(Level*, BoundingBox*, int, int, int, int, const BlockState*,
                                    const BlockState*, bool);
    virtual void generateAirColumnUp(Level*, int, int, int, BoundingBox*);
    virtual void generateAirBoxUp(Level*, int, int, int, int, int, BoundingBox*);
    virtual void fillColumnDown(Level*, const BlockState*, int, int, int, BoundingBox*);
    virtual void fillBoxDown(Level*, const BlockState*, int, int, int, int, int, BoundingBox*);
    virtual bool createChest(Level*, BoundingBox*, Random&, int, int, int, ResourceLocation*);
    virtual bool createChest(Level*, BoundingBox*, Random&, const BlockPos&, ResourceLocation*,
                             const BlockState*);
    virtual bool createDispenser(Level*, BoundingBox*, Random&, int, int, int, const Direction*,
                                 ResourceLocation*);
    virtual void addStructurePieceSaveData(DataOutputStream*, std::vector<bool>, std::vector<bool>,
                                           std::vector<int>, std::vector<int>);
    virtual void readStructurePieceSaveData(DataInputStream*, std::vector<bool>&, std::vector<bool>&,
                                            std::vector<int>&, std::vector<int>&);
    virtual void addBoolSaveData(DataOutputStream*, std::vector<bool>);
    virtual std::vector<bool> readBoolSaveData(DataInputStream*);
    virtual void addIntSaveData(DataOutputStream*, std::vector<int>);
    virtual std::vector<int> readIntSaveData(DataInputStream*);
    virtual void move(int, int, int);
    virtual Rotation* getRotation();
    virtual Mirror* getMirror();

    void write(DataOutputStream*);
    void setBoundingBox(BoundingBox*);
    const Direction* getOrientation();
    void setOrientation(const Direction*);
    int getWorldX(int x, int z);
    int getWorldY(int y);
    int getWorldZ(int x, int z);
    void setGenDepth(int);
    void setDirty();
    void clearDirty();
    bool isDirty();

    BoundingBox* m_boundingBox;
    const Direction* m_orientation;
    Mirror* m_mirror;
    Rotation* m_rotation;
    int m_genDepth;
    bool m_dirty;
};

static_assert(sizeof(StructurePiece) == 0x30, "Switch structure piece layout");
