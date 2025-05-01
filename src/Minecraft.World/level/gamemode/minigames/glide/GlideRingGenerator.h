#pragma once

#include <vector>

class AABB;
class BlockPos;
class TextureAtlasSprite;

class GlideRingGenerator {
public:
    enum eGlideRingSize {};

    static void BuildRing(std::vector<BlockPos>&, const AABB*, eGlideRingSize);
    static TextureAtlasSprite* getIcon(eGlideRingSize);
};
