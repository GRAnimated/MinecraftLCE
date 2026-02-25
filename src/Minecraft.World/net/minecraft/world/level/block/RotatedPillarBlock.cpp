#include "net/minecraft/world/level/block/RotatedPillarBlock.h"

#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/block/Rotation.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/material/Material.h"

void RotatedPillarBlock::blockStaticCtor() {
    AXIS = EnumProperty<Direction::Axis*>::create(L"axis", typeid(Direction::Axis), Direction::Axis::VALUES,
                                                  Direction::Axis::PREDICATE);
}

RotatedPillarBlock::RotatedPillarBlock(Material* material) : Block(material, material->getColor()) {}

RotatedPillarBlock::RotatedPillarBlock(Material* material, const MaterialColor* color)
    : Block(material, color) {}

const BlockState* RotatedPillarBlock::getBlockState(int data) {
    Direction::Axis* axis = Direction::Axis::Y;
    int unmask = data & 0xC;

    if (unmask == 4) {
        axis = Direction::Axis::X;
    } else if (unmask == 8) {
        axis = Direction::Axis::Z;
    }

    return this->defaultBlockState()->setValue(AXIS, axis);
}

int RotatedPillarBlock::convertBlockStateToLegacyData(const BlockState* state) {
    int result = 0;
    Direction::Axis* axis = state->getValue<Direction::Axis*>(AXIS);
    if (axis == Direction::Axis::X)
        result = 4;
    else if (axis == Direction::Axis::Z)
        result = 8;
    return result;
}

const BlockState* RotatedPillarBlock::rotate(const BlockState* state, Rotation* rotation) {
    // why switch case here, 4J whyyyy
    switch (rotation->getType()) {
    case 1:
    case 3:
        switch (state->getValue<Direction::Axis*>(AXIS)->getId()) {
        case 0:
            return state->setValue(AXIS, Direction::Axis::Z);

        case 2:
            return state->setValue(AXIS, Direction::Axis::X);

        default:
            return state;
        }

    default:
        return state;
    }
}

RenderShape RotatedPillarBlock::getRenderShape(const BlockState*) {
    return RenderShape_ROTATEDPILLARBLOCK;
}

const BlockState* RotatedPillarBlock::getStateForPlacement(Level* level, const BlockPos& pos,
                                                           const Direction* direction, float x, float y,
                                                           float z, int data,
                                                           std::shared_ptr<LivingEntity> placer) {
    return Block::getStateForPlacement(level, pos, direction, x, y, z, data, placer)
        ->setValue(AXIS, direction->getAxis());
}

not_null_ptr<ItemInstance> RotatedPillarBlock::getSilkTouchItemInstance(const BlockState*) {
    return new ItemInstance(Item::byBlock(this));
}

TextureAtlasSprite* RotatedPillarBlock::getTexture(const Direction* direction, const BlockState* state) {
    Direction::Axis* axis = this->getAxis(state);
    if ((axis == Direction::Axis::Y && (Direction::UP == direction || Direction::DOWN == direction))
        || (axis == Direction::Axis::X && (Direction::EAST == direction || Direction::WEST == direction))
        || (axis == Direction::Axis::Z && (Direction::NORTH == direction || Direction::SOUTH == direction))) {
        return this->getTopTexture(state);
    } else {
        return this->getTypeTexture(state);
    }
}

BlockStateDefinition* RotatedPillarBlock::createBlockStateDefinition() {
    static const Property* properties[] = {AXIS};
    return new BlockStateDefinition(this, properties);
}

TextureAtlasSprite* RotatedPillarBlock::getTypeTexture(const BlockState*) {
    return this->m_texture;
}

TextureAtlasSprite* RotatedPillarBlock::getTopTexture(const BlockState*) {
    return this->m_topTexture;
}
