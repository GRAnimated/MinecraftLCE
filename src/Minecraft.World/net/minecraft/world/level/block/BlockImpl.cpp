#include "net/minecraft/world/level/block/BlockImpl.h"

BlockImpl::BlockImpl(Material* material) : Block(material) {
    DerivedInit();
}

BlockImpl::BlockImpl(Material* material, const MaterialColor* materialColor)
    : Block(material, materialColor) {
    DerivedInit();
}
