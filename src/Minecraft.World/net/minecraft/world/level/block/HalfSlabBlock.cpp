#include "net/minecraft/world/level/block/HalfSlabBlock.h"

#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/storage/LevelSource.h"
#include "net/minecraft/world/phys/AABB.h"

HalfSlabBlock::Half* HalfSlabBlock::Half::TOP = new HalfSlabBlock::Half(L"top");
HalfSlabBlock::Half* HalfSlabBlock::Half::BOTTOM = new HalfSlabBlock::Half(L"bottom");
HalfSlabBlock::Half* HalfSlabBlock::Half::VARIANTS[2] = {TOP, BOTTOM};

const AABB* HalfSlabBlock::topShape = AABB::newPermanent(0.0, 0.5, 0.0, 1.0, 1.0, 1.0);
const AABB* HalfSlabBlock::bottomShape = AABB::newPermanent(0.0, 0.0, 0.0, 1.0, 0.5, 1.0);

void HalfSlabBlock::blockStaticCtor() {
    VARIANT = EnumProperty<Half*>::create(L"half", typeid(Half), Half::VARIANTS, PREDICATE);
}

bool HalfSlabBlock::isHalfSlab(Block* block) {
    return block == Blocks::STONE_SLAB || block == Blocks::WOODEN_SLAB || block == Blocks::STONE_SLAB2
           || block == Blocks::PURPUR_SLAB;
}

bool HalfSlabBlock::isHalfSlab(const BlockState* state) {
    return isHalfSlab(state->getBlock());
}

HalfSlabBlock::HalfSlabBlock(Material* material) : Block(material) {
    this->_init();
}

HalfSlabBlock::HalfSlabBlock(Material* material, const MaterialColor* materialColor)
    : Block(material, materialColor) {
    this->_init();
}

void HalfSlabBlock::_init() {
    this->field_A0 = 8;
    this->setLightBlock(255);
}

bool HalfSlabBlock::isTopSolidBlocking(const BlockState* state) {
    if (((HalfSlabBlock*)state->getBlock())->isFullSize()) {
        return true;
    }
    return state->getValue<Half*>(VARIANT) == Half::TOP;
}

void HalfSlabBlock::DerivedInit() {
    Block::DerivedInit();
    this->field_28 = this->isFullSize();
    this->setLightBlock(255);
}

bool HalfSlabBlock::isCubeShaped(const BlockState*) {
    return this->isFullSize();
}

bool HalfSlabBlock::isPathfindable(LevelSource* level, const BlockPos& pos) {
    const BlockState* state = level->getBlockState(pos);
    if (!this->isFullSize() && state->getValue<Half*>(VARIANT) == Half::BOTTOM) {
        return true;
    }

    return Block::isPathfindable(level, pos);
}

const AABB* HalfSlabBlock::getShape(const BlockState* state, LevelSource* level, const BlockPos& pos) {
    if (this->isFullSize()) {
        return Block::defaultBlockShape;
    }

    return state->getValue<Half*>(VARIANT) == Half::TOP ? topShape : bottomShape;
}

// NON_MATCHING: I really don't know
bool HalfSlabBlock::shouldRenderFace(const BlockState* state, LevelSource* level, const BlockPos& pos,
                                     const Direction* dir) {
    if (this->isFullSize()) {
        return Block::shouldRenderFace(state, level, pos, dir);
    } else if (dir != Direction::UP && dir != Direction::DOWN
               && !Block::shouldRenderFace(state, level, pos, dir)) {
        return false;
    } else {
        const BlockState* relState = level->getBlockState(pos.relative(dir));
        bool isTopHalfRel = isHalfSlab(relState) && relState->getValue<Half*>(VARIANT) == Half::TOP;
        bool isTopHalf = isHalfSlab(state) && state->getValue<Half*>(VARIANT) == Half::TOP;
        if (isTopHalf) {
            if (dir == Direction::DOWN) {
                return true;
            }

            if (dir == Direction::UP && Block::shouldRenderFace(state, level, pos, dir)) {
                return true;
            }

            return !isHalfSlab(state) || !isTopHalfRel;
        } else {
            if (dir == Direction::UP) {
                return true;
            }

            if (dir == Direction::DOWN && Block::shouldRenderFace(state, level, pos, dir)) {
                return true;
            }

            return !isHalfSlab(relState) || isTopHalfRel;
        }
    }
}

int HalfSlabBlock::getBlockFaceShape(LevelSource* level, const BlockState* state, const BlockPos&,
                                     const Direction* dir) {
    if (((HalfSlabBlock*)state->getBlock())->isFullSize()) {
        return 0;
    }

    if ((Direction::UP == dir && state->getValue<Half*>(VARIANT) == Half::TOP)
        || (Direction::DOWN == dir && state->getValue<Half*>(VARIANT) == Half::BOTTOM)) {
        return 0;
    }
    return 8;
}

bool HalfSlabBlock::isSolidRender(const BlockState*) const {
    return this->isFullSize();
}

int HalfSlabBlock::getResourceCount(Random*) {
    return this->isFullSize() ? 2 : 1;
}

const BlockState* HalfSlabBlock::getStateForPlacement(Level* level, const BlockPos& pos, const Direction* dir,
                                                      float x, float y, float z, int data,
                                                      std::shared_ptr<LivingEntity> ent) {
    const BlockState* state
        = Block::getStateForPlacement(level, pos, dir, x, y, z, data, ent)->setValue(VARIANT, Half::BOTTOM);
    if (!this->isFullSize() && (dir == Direction::DOWN || (y > 0.5f && dir != Direction::UP))) {
        state = state->setValue(VARIANT, Half::TOP);
    }
    return state;
}

bool HalfSlabBlock::isSilkTouchable() {
    return false;
}
