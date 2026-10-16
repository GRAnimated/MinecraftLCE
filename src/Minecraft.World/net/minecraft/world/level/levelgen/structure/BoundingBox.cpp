#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include <algorithm>
#include <climits>

BoundingBox::BoundingBox(int x0, int y0, int z0, int x1, int y1, int z1) {
    this->m_x0 = x0;
    this->m_y0 = y0;
    this->m_z0 = z0;
    this->m_x1 = x1;
    this->m_y1 = y1;
    this->m_z1 = z1;
}

// Names of the shared integer helpers are inferred from their use in box expansion.
int boundingBoxMin(int a, int b) {
    return a < b ? a : b;
}
int boundingBoxMax(int a, int b) {
    return a > b ? a : b;
}

BoundingBox::BoundingBox() : m_x0(0), m_y0(0), m_z0(0), m_x1(0), m_y1(0), m_z1(0) {}

BoundingBox::BoundingBox(BoundingBox* other) {
    m_x0 = other->m_x0;
    m_y0 = other->m_y0;
    m_z0 = other->m_z0;
    m_x1 = other->m_x1;
    m_y1 = other->m_y1;
    m_z1 = other->m_z1;
}

BoundingBox::BoundingBox(int x0, int z0, int x1, int z1) {
    m_y1 = 512;
    m_z1 = z1;
    m_z0 = z0;
    m_x1 = x1;
    m_x0 = x0;
    m_y0 = 1;
}

BoundingBox* BoundingBox::getUnknownBox() {
    return new BoundingBox(INT_MAX, INT_MAX, INT_MAX, INT_MIN, INT_MIN, INT_MIN);
}

BoundingBox* BoundingBox::createProper(int x0, int y0, int z0, int x1, int y1, int z1) {
    return new BoundingBox(std::min(x0, x1), std::min(y0, y1), std::min(z0, z1), std::max(x0, x1),
                           std::max(y0, y1), std::max(z0, z1));
}

BoundingBox* BoundingBox::orientBox(int x, int y, int z, int offsetX, int offsetY, int offsetZ, int width,
                                    int height, int depth, const Direction* direction) {
    switch (direction->get3DDataValue()) {
    case 2:
        return new BoundingBox(x + offsetX, y + offsetY, z + offsetZ + 1 - depth, x + offsetX + width - 1,
                               y + offsetY + height - 1, z + offsetZ);
    case 4:
        return new BoundingBox(x + offsetZ + 1 - depth, y + offsetY, z + offsetX, x + offsetZ,
                               y + offsetY + height - 1, z + offsetX + width - 1);
    case 5:
        return new BoundingBox(x + offsetZ, y + offsetY, z + offsetX, x + offsetZ + depth - 1,
                               y + offsetY + height - 1, z + offsetX + width - 1);
    default:
        return new BoundingBox(x + offsetX, y + offsetY, z + offsetZ, x + offsetX + width - 1,
                               y + offsetY + height - 1, z + offsetZ + depth - 1);
    }
}

bool BoundingBox::intersects(BoundingBox* other) {
    return m_x1 >= other->m_x0 && m_x0 <= other->m_x1 && m_z1 >= other->m_z0 && m_z0 <= other->m_z1
           && m_y1 >= other->m_y0 && m_y0 <= other->m_y1;
}

bool BoundingBox::intersects(Vec3i lower, Vec3i upper) {
    return m_x1 >= lower.getX() && m_x0 <= upper.getX() && m_z1 >= lower.getZ() && m_z0 <= upper.getZ()
           && m_y1 >= lower.getY() && m_y0 <= upper.getY();
}

bool BoundingBox::intersects(int x0, int z0, int x1, int z1) {
    return m_x1 >= x0 && m_x0 <= x1 && m_z1 >= z0 && m_z0 <= z1;
}

void BoundingBox::expand(BoundingBox* other) {
    m_x0 = boundingBoxMin(m_x0, other->m_x0);
    m_y0 = boundingBoxMin(m_y0, other->m_y0);
    m_z0 = boundingBoxMin(m_z0, other->m_z0);
    m_x1 = boundingBoxMax(m_x1, other->m_x1);
    m_y1 = boundingBoxMax(m_y1, other->m_y1);
    m_z1 = boundingBoxMax(m_z1, other->m_z1);
}

void BoundingBox::move(int x, int y, int z) {
    m_x0 += x;
    m_y0 += y;
    m_z0 += z;
    m_x1 += x;
    m_y1 += y;
    m_z1 += z;
}

bool BoundingBox::isInside(Vec3i pos) {
    return pos.getX() >= m_x0 && pos.getX() <= m_x1 && pos.getZ() >= m_z0 && pos.getZ() <= m_z1
           && pos.getY() >= m_y0 && pos.getY() <= m_y1;
}

int BoundingBox::getXSpan() {
    return m_x1 - m_x0 + 1;
}
int BoundingBox::getYSpan() {
    return m_y1 - m_y0 + 1;
}
int BoundingBox::getZSpan() {
    return m_z1 - m_z0 + 1;
}

BlockPos BoundingBox::getCenter() {
    return BlockPos(m_x0 + (m_x1 - m_x0 + 1) / 2, m_y0 + (m_y1 - m_y0 + 1) / 2, m_z0 + (m_z1 - m_z0 + 1) / 2);
}

void BoundingBox::write(DataOutputStream* stream) {
    stream->writeInt(m_x0);
    stream->writeInt(m_y0);
    stream->writeInt(m_z0);
    stream->writeInt(m_x1);
    stream->writeInt(m_y1);
    stream->writeInt(m_z1);
}

void BoundingBox::read(DataInputStream* stream) {
    m_x0 = stream->readInt();
    m_y0 = stream->readInt();
    m_z0 = stream->readInt();
    m_x1 = stream->readInt();
    m_y1 = stream->readInt();
    m_z1 = stream->readInt();
}
