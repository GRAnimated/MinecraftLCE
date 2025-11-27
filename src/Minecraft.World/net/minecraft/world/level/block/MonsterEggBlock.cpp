#include "net/minecraft/world/level/block/MonsterEggBlock.h"

#include "net/minecraft/client/ui/StringIDs.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/monster/Silverfish.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/GameRules.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/StoneBrickBlock.h"
#include "net/minecraft/world/level/material/Material.h"
#include <memory>
#include <string>

MonsterEggBlock::Variant* MonsterEggBlock::Variant::STONE
    = new MonsterEggBlock::Variant(0, L"stone", StringIDs::SilverfishStone);
MonsterEggBlock::Variant* MonsterEggBlock::Variant::COBBLESTONE
    = new MonsterEggBlock::Variant(1, L"cobblestone", StringIDs::SilverfishCobblestone);
MonsterEggBlock::Variant* MonsterEggBlock::Variant::STONE_BRICK
    = new MonsterEggBlock::Variant(2, L"stone_brick", StringIDs::SilverfishMossyStoneBrick);
MonsterEggBlock::Variant* MonsterEggBlock::Variant::MOSSY_BRICK
    = new MonsterEggBlock::Variant(3, L"mossy_brick", StringIDs::SilverfishMossyStoneBrick);
MonsterEggBlock::Variant* MonsterEggBlock::Variant::CRACKED_BRICK
    = new MonsterEggBlock::Variant(4, L"cracked_brick", StringIDs::SilverfishCrackedStoneBrick);
MonsterEggBlock::Variant* MonsterEggBlock::Variant::CHISELED_BRICK
    = new MonsterEggBlock::Variant(5, L"chiseled_brick", StringIDs::SilverfishChiseledStoneBrick);

MonsterEggBlock::Variant* MonsterEggBlock::Variant::VARIANTS[6]
    = {Variant::STONE,       Variant::COBBLESTONE,   Variant::STONE_BRICK,
       Variant::MOSSY_BRICK, Variant::CRACKED_BRICK, Variant::CHISELED_BRICK};

MonsterEggBlock::MonsterEggBlock() : Block(Material::CLAY) {
    this->DerivedInit();
    this->setDestroyTime(0.0);
}

void MonsterEggBlock::blockStaticCtor() {
    VARIANT = EnumProperty<Variant*>::create(L"variant", typeid(Variant), Variant::VARIANTS, PREDICATE);
}

const BlockState* MonsterEggBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(VARIANT, Variant::byData(data));
}

int MonsterEggBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

int MonsterEggBlock::getResourceCount(Random* random) {
    return 0;
}

void MonsterEggBlock::spawnResources(Level* level, const BlockPos& pos, const BlockState* state, float chance,
                                     int fortune) {
    if (!level->mIsLocal) {
        if (!level->getGameRules()->getBoolean(5)
            || level->countInstanceOf(eMonster, false, nullptr, nullptr) >= 70
            || level->countInstanceOf(eSilverfish, true, nullptr, nullptr) >= 15) {
            return;
        }

        std::shared_ptr<Silverfish> silverfish = std::shared_ptr<Silverfish>(new Silverfish(level));
        silverfish->moveTo(pos.getX() + 0.5, pos.getY(), pos.getZ() + 0.5, 0.0f, 0.0f);
        level->addEntity(silverfish);
        silverfish->spawnAnim();
    }
}

not_null_ptr<ItemInstance> MonsterEggBlock::getSilkTouchItemInstance(const BlockState* state) {
    ItemInstance* item;
    switch (state->getValue<Variant*>(VARIANT)->getData()) {
    case 1:
        item = new ItemInstance(Blocks::COBBLESTONE);
        break;
    case 2:
        item = new ItemInstance(Blocks::STONEBRICK);
        break;
    case 3:
        item = new ItemInstance(Blocks::STONEBRICK, 1, StoneBrickBlock::Variant::MOSSY->getData());
        break;
    case 4:
        item = new ItemInstance(Blocks::STONEBRICK, 1, StoneBrickBlock::Variant::CRACKED->getData());
        break;
    case 5:
        item = new ItemInstance(Blocks::STONEBRICK, 1, StoneBrickBlock::Variant::CHISELED->getData());
        break;
    default:
        item = new ItemInstance(Blocks::STONE);
        break;
    }
    return item;
}
not_null_ptr<ItemInstance> MonsterEggBlock::getCloneItemInstance(Level*, const BlockPos&,
                                                                 const BlockState* state) {
    return new ItemInstance(this, 1, state->getBlock()->convertBlockStateToLegacyData(state));
}

void MonsterEggBlock::registerIcons(IconRegister* iconReg) {
    // wow
}

TextureAtlasSprite* MonsterEggBlock::getTexture(const Direction* dir, const BlockState* state) {
    const Variant* variant = state->getValue<Variant*>(VARIANT);

    if (variant == Variant::STONE) {
        Block* block = Blocks::STONE;
        return block->getTexture(dir);
    } else if (variant == Variant::COBBLESTONE) {
        Block* block = Blocks::COBBLESTONE;
        return block->getTexture(dir);
    } else if (variant == Variant::STONE_BRICK) {
        Block* block = Blocks::STONEBRICK;
        return block->getTexture(dir);
    } else if (variant == Variant::MOSSY_BRICK) {
        const BlockState* modifiedState = Blocks::STONEBRICK->defaultBlockState()->setValue(
            StoneBrickBlock::VARIANT, StoneBrickBlock::Variant::MOSSY);
        return Blocks::STONEBRICK->getTexture(dir, modifiedState);
    } else if (variant == Variant::CRACKED_BRICK) {
        const BlockState* modifiedState = Blocks::STONEBRICK->defaultBlockState()->setValue(
            StoneBrickBlock::VARIANT, StoneBrickBlock::Variant::CRACKED);
        return Blocks::STONEBRICK->getTexture(dir, modifiedState);
    } else if (variant == Variant::CHISELED_BRICK) {
        const BlockState* modifiedState = Blocks::STONEBRICK->defaultBlockState()->setValue(
            StoneBrickBlock::VARIANT, StoneBrickBlock::Variant::CHISELED);
        return Blocks::STONEBRICK->getTexture(dir, modifiedState);
    }
    return nullptr;
}

// NON_MATCHING: static array handling is generated differently
BlockStateDefinition* MonsterEggBlock::createBlockStateDefinition() {
    static const Property* properties[1]{VARIANT};
    return new BlockStateDefinition(this, properties);
}
