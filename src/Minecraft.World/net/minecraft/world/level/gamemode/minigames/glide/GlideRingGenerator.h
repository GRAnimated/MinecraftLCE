#pragma once

#include <vector>

class AABB;
class BlockPos;
class TextureAtlasSprite;

class GlideRingGenerator {
public:
    // name guessed: ordinal labels for the three entries in the executable tables.
    enum eGlideRingSize { Size0 = 0, Size1 = 1, Size2 = 2 };

    static void BuildRing(std::vector<BlockPos>&, const AABB*, eGlideRingSize);
    static TextureAtlasSprite* getIcon(eGlideRingSize);

    // name guessed: data tables and internal helpers identified by their uses.
    static TextureAtlasSprite* sIcons[3];
    static const int sCornerCounts[3];
    static const int sRadii[3];
    static const int sStraightOffsets[3];
    static const int sCornerRadii[3];
    static const int sCornerOffsets[3];

private:
    static void appendSegment(std::vector<BlockPos>&, const BlockPos&, eGlideRingSize, unsigned int segment,
                              int plane);
    static BlockPos orientOffset(const BlockPos&, int plane, int horizontal, int vertical);
    static int horizontalOffset(eGlideRingSize, unsigned int segment, int index);
    static int verticalOffset(eGlideRingSize, unsigned int segment, int index);
};
