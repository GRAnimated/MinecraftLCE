#include "net/minecraft/world/level/levelgen/structure/StructurePiece.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Mirror.h"
#include "net/minecraft/world/level/block/Rotation.h"
#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"
#include "net/minecraft/world/level/levelgen/structure/StructureFeatureIO.h"
#include "net/minecraft/world/level/storage/LevelStorage.h"

StructurePiece::StructurePiece()
    : m_boundingBox(nullptr), m_orientation(nullptr), m_mirror(Mirror::NONE), m_rotation(Rotation::NONE),
      m_genDepth(0), m_dirty(true) {}

StructurePiece::StructurePiece(int genDepth) {
    m_boundingBox = nullptr;
    m_genDepth = genDepth;
    m_orientation = nullptr;
    m_mirror = Mirror::NONE;
    m_rotation = Rotation::NONE;
    m_dirty = true;
}

StructurePiece::~StructurePiece() {
    delete m_boundingBox;
}

void StructurePiece::setBoundingBox(BoundingBox* bounds) {
    delete m_boundingBox;
    m_boundingBox = bounds;
}

CompoundTag* StructurePiece::createTag() {
    return new CompoundTag();
}

void StructurePiece::write(DataOutputStream* output) {
    output->writeUTF(StructureFeatureIO::getEncodeId(this));
    m_boundingBox->write(output);
    output->writeInt(m_orientation ? m_orientation->get2DDataValue() : -1);
    output->writeInt(m_genDepth);
    addAdditionalSaveData(output);
}

void StructurePiece::load(Level* level, DataInputStream* input) {
    delete m_boundingBox;
    m_boundingBox = new BoundingBox();
    m_boundingBox->read(input);
    int orientation = input->readInt();
    setOrientation(orientation == -1 ? nullptr : Direction::from2DDataValue(orientation));
    m_genDepth = input->readInt();
    readAdditionalSaveData(input, level->getLevelStorage()->getStructureManager());
}

void StructurePiece::addChildren(StructurePiece*, std::vector<StructurePiece*>*, Random&) {}

BlockPos* StructurePiece::getLocatorPosition() {
    return new BlockPos(static_cast<const Vec3i&>(m_boundingBox->getCenter()));
}

const Direction* StructurePiece::getOrientation() {
    return m_orientation;
}

void StructurePiece::setOrientation(const Direction* orientation) {
    m_orientation = orientation;
    if (orientation != nullptr) {
        if (orientation == Direction::SOUTH) {
            m_mirror = Mirror::LEFT_RIGHT;
            m_rotation = Rotation::NONE;
        } else if (orientation == Direction::WEST) {
            m_mirror = Mirror::LEFT_RIGHT;
            m_rotation = Rotation::CLOCKWISE_90;
        } else if (orientation == Direction::EAST) {
            m_mirror = Mirror::NONE;
            m_rotation = Rotation::CLOCKWISE_90;
        } else {
            m_mirror = Mirror::NONE;
            m_rotation = Rotation::NONE;
        }
    } else {
        m_rotation = Rotation::NONE;
        m_mirror = Mirror::NONE;
    }
}

int StructurePiece::getWorldX(int x, int z) {
    const Direction* orientation = getOrientation();
    if (orientation) {
        switch (orientation->get3DDataValue()) {
        case 2:
        case 3:
            return m_boundingBox->m_x0 + x;
        case 4:
            return m_boundingBox->m_x1 - z;
        case 5:
            return m_boundingBox->m_x0 + z;
        }
    }
    return x;
}

int StructurePiece::getWorldY(int y) {
    return getOrientation() ? m_boundingBox->m_y0 + y : y;
}

int StructurePiece::getWorldZ(int x, int z) {
    const Direction* orientation = getOrientation();
    if (orientation) {
        switch (orientation->get3DDataValue()) {
        case 2:
            return m_boundingBox->m_z1 - z;
        case 3:
            return m_boundingBox->m_z0 + z;
        case 4:
        case 5:
            return m_boundingBox->m_z0 + x;
        }
    }
    return z;
}

void StructurePiece::setGenDepth(int depth) {
    m_genDepth = depth;
}

void StructurePiece::setDirty() {
    m_dirty = true;
}

void StructurePiece::move(int x, int y, int z) {
    m_boundingBox->move(x, y, z);
}

Rotation* StructurePiece::getRotation() {
    return m_rotation;
}

Mirror* StructurePiece::getMirror() {
    return m_mirror;
}
