#include "net/minecraft/world/level/gamemode/minigames/glide/GlideRingGenerator.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/phys/AABB.h"

TextureAtlasSprite* GlideRingGenerator::sIcons[3];  // name guessed
const int GlideRingGenerator::sCornerCounts[3] = {0, 1, 3};
const int GlideRingGenerator::sRadii[3] = {2, 3, 4};
const int GlideRingGenerator::sStraightOffsets[3] = {-1, 0, 1};  // name guessed
const int GlideRingGenerator::sCornerRadii[3] = {0, 2, 3};
const int GlideRingGenerator::sCornerOffsets[3] = {-2, -3, 2};

void GlideRingGenerator::BuildRing(std::vector<BlockPos>& blocks, const AABB* bounds, eGlideRingSize size) {
    BlockPos center(bounds->getCenter()->m_x, bounds->getCenter()->m_y, bounds->getCenter()->m_z);
    double width = bounds->m_axX - bounds->m_inX;
    double depth = bounds->m_axZ - bounds->m_inZ;
    double height = bounds->m_axY - bounds->m_inY;
    int plane;
    if (width < depth && width < height)
        plane = 1;
    else if (height < width && height < depth)
        plane = 2;
    else if (depth < width && depth < height)
        plane = 0;
    else
        return;

    appendSegment(blocks, center, size, 0, plane);
    appendSegment(blocks, center, size, 1, plane);
    appendSegment(blocks, center, size, 2, plane);
    appendSegment(blocks, center, size, 3, plane);
    appendSegment(blocks, center, size, 4, plane);
    appendSegment(blocks, center, size, 5, plane);
    appendSegment(blocks, center, size, 6, plane);
    appendSegment(blocks, center, size, 7, plane);
}

// name guessed
void GlideRingGenerator::appendSegment(std::vector<BlockPos>& blocks, const BlockPos& center,
                                       eGlideRingSize size, unsigned int segment, int plane) {
    int count = 3;
    if ((segment & ~3u) == 4) {
        if (static_cast<unsigned long>(static_cast<unsigned int>(size)) - 1 > 1)
            return;
        count = sCornerCounts[size];
    }
    int index = 0;
    do {
        int horizontal = horizontalOffset(size, segment, index);
        int vertical = verticalOffset(size, segment, index);
        BlockPos position = orientOffset(center, plane, horizontal, vertical);
        blocks.push_back(position);
        index++;
    } while (index != count);
}

TextureAtlasSprite* GlideRingGenerator::getIcon(eGlideRingSize size) {
    return sIcons[static_cast<unsigned int>(size)];
}

// name guessed
BlockPos GlideRingGenerator::orientOffset(const BlockPos& center, int plane, int horizontal, int vertical) {
    if (plane == 2) {
        return BlockPos(center.getX() + horizontal, center.getY(), center.getZ() + vertical);
    } else if (plane == 1) {
        return BlockPos(center.getX(), center.getY() + horizontal, center.getZ() + vertical);
    } else if (plane == 0) {
        return BlockPos(center.getX() + horizontal, center.getY() + vertical, center.getZ());
    } else {
        return BlockPos();
    }
}

// name guessed
int GlideRingGenerator::horizontalOffset(eGlideRingSize size, unsigned int segment, int index) {
    switch (segment) {
    case 0:
        return sRadii[static_cast<unsigned int>(size)];
    case 1:
        return -sRadii[static_cast<unsigned int>(size)];
    case 2:
    case 3:
        return sStraightOffsets[index];
    case 4:
        return -sCornerRadii[static_cast<unsigned int>(size)];
    case 5:
        return sCornerRadii[static_cast<unsigned int>(size)];
    case 6:
        return sCornerOffsets[index];
    case 7:
        return -sCornerOffsets[index];
    default:
        return 0;
    }
}

// name guessed
int GlideRingGenerator::verticalOffset(eGlideRingSize size, unsigned int segment, int index) {
    switch (segment) {
    case 0:
    case 1:
        return sStraightOffsets[index];
    case 2:
        return -sRadii[static_cast<unsigned int>(size)];
    case 3:
        return sRadii[static_cast<unsigned int>(size)];
    case 4:
        return -sCornerOffsets[index];
    case 5:
        return sCornerOffsets[index];
    case 6:
        return -sCornerRadii[static_cast<unsigned int>(size)];
    case 7:
        return sCornerRadii[static_cast<unsigned int>(size)];
    default:
        return 0;
    }
}
