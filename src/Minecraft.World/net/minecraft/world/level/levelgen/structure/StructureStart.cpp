#include "net/minecraft/world/level/levelgen/structure/StructureStart.h"

#include "java/io/ByteArrayOutputStream.h"
#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"
#include "net/minecraft/world/level/levelgen/structure/StructureFeatureIO.h"
#include "net/minecraft/world/level/levelgen/structure/StructurePiece.h"

StructureStart::StructureStart() : m_boundingBox(nullptr), m_chunkX(0), m_chunkZ(0), m_dirty(true) {}

StructureStart::StructureStart(int chunkX, int chunkZ) : m_chunkX(chunkX), m_chunkZ(chunkZ) {
    m_boundingBox = nullptr;
    m_dirty = true;
}

StructureStart::~StructureStart() {
    for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it)
        delete *it;
    delete m_boundingBox;
}

void StructureStart::postProcess(Level* level, Random& random, BoundingBox* bounds) {
    auto it = m_pieces.begin();
    while (it != m_pieces.end()) {
        StructurePiece* piece = *it;
        if (piece->getBoundingBox()->intersects(bounds) && !piece->postProcess(level, random, bounds)) {
            // The original removes the pointer without deleting the rejected piece.
            it = m_pieces.erase(it);
        } else {
            if (piece->isDirty()) {
                setDirty();
                piece->clearDirty();
            }
            ++it;
        }
    }
}

void StructureStart::calculateBoundingBox() {
    m_boundingBox = BoundingBox::getUnknownBox();
    for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it)
        m_boundingBox->expand((*it)->getBoundingBox());
}

arrayWithLength<unsigned char> StructureStart::createTag(int chunkX, int chunkZ) {
    ByteArrayOutputStream bytes;
    DataOutputStream output(&bytes);
    output.writeInt(3);
    output.writeUTF(StructureFeatureIO::getEncodeId(this));
    output.writeInt(chunkX);
    output.writeInt(chunkZ);
    m_boundingBox->write(&output);
    output.writeInt(m_pieces.size());
    for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it)
        (*it)->write(&output);
    addAdditionalSaveData(&output);
    return bytes.toByteArray();
}

void StructureStart::addAdditionalSaveData(DataOutputStream*) {}

void StructureStart::load(Level* level, DataInputStream* input) {
    m_chunkX = input->readInt();
    m_chunkZ = input->readInt();
    m_boundingBox = new BoundingBox();
    m_boundingBox->read(input);
    int count = input->readInt();
    for (int i = 0; i < count; ++i) {
        StructurePiece* piece = StructureFeatureIO::loadStaticPiece(input, level);
        if (piece)
            m_pieces.push_back(piece);
    }
    readAdditionalSaveData(input);
}

void StructureStart::readAdditionalSaveData(DataInputStream*) {}

void StructureStart::moveBelowSeaLevel(Level* level, Random& random, int padding) {
    int limit = level->getSeaLevel() - padding;
    int target = m_boundingBox->getYSpan() + 1;
    if (target < limit)
        target += random.nextInt(limit - target);
    int delta = target - m_boundingBox->m_y1;
    m_boundingBox->move(0, delta, 0);
    for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it)
        (*it)->move(0, delta, 0);
}

void StructureStart::moveInsideHeights(Level*, Random& random, int minY, int maxY) {
    int range = maxY - minY + 1 - m_boundingBox->getYSpan();
    int target = minY;
    if (range > 1)
        target += random.nextInt(range);
    int delta = target - m_boundingBox->m_y0;
    m_boundingBox->move(0, delta, 0);
    for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it)
        (*it)->move(0, delta, 0);
}

bool StructureStart::isValid() {
    return true;
}
bool StructureStart::isValidForPostProcess(ChunkPos*) {
    return true;
}
void StructureStart::notifyPostProcessAt(ChunkPos*) {}
std::vector<StructurePiece*>* StructureStart::getPieces() {
    return &m_pieces;
}
BoundingBox* StructureStart::getBoundingBox() {
    return m_boundingBox;
}
int StructureStart::getChunkX() {
    return m_chunkX;
}
int StructureStart::getChunkZ() {
    return m_chunkZ;
}
void StructureStart::setDirty() {
    m_dirty = true;
}
void StructureStart::clearDirty() {
    m_dirty = false;
}
bool StructureStart::isDirty() {
    return m_dirty;
}
