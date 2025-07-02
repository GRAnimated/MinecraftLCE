#include "Minecraft.World/level/block/GlassBlock.h"
#include "Minecraft.World/level/block/HalfTransparentBlock.h"

GlassBlock::GlassBlock(Material* material, bool unk) : HalfTransparentBlock(L"glass", material, unk) {
    DerivedInit();
}

bool GlassBlock::isCubeShaped(const BlockState* blockState) {
    return false;
}

int GlassBlock::getResourceCount(Random*) {
    return 0;
}

int GlassBlock::getRenderLayer() {
    return 0;
}

bool GlassBlock::isSilkTouchable() {
    return true;
}
