#include "net/minecraft/world/level/levelgen/structure/StructurePiece.h"

BoundingBox* StructurePiece::getBoundingBox() {
    return m_boundingBox;
}

void StructurePiece::clearDirty() {
    m_dirty = false;
}

bool StructurePiece::isDirty() {
    return m_dirty;
}
