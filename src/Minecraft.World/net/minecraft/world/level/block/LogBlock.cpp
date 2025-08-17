#include "net/minecraft/world/level/block/LogBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/BlockPosIterator.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/LeafBlock.h"
#include "net/minecraft/world/level/block/Rotation.h"
#include "net/minecraft/world/level/block/SoundType.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/material/Material.h"

LogBlock::LogAxis* X = new LogBlock::LogAxis(L"x");
LogBlock::LogAxis* Y = new LogBlock::LogAxis(L"y");
LogBlock::LogAxis* Z = new LogBlock::LogAxis(L"z");
LogBlock::LogAxis* NONE = new LogBlock::LogAxis(L"none");

LogBlock::LogAxis* VALUES[4] = {X, Y, Z, NONE};

const unsigned int LogBlock::DESCRIPTION_IDS[6]
    = {0xB851C01, StringIDs::SpruceWood, StringIDs::BirchWood, StringIDs::JungleWood, StringIDs::AcaciaWood};

LogBlock::LogBlock() : RotatedPillarBlock(Material::WOOD) {
    this->setDestroyTime(2.0f);
    this->setSoundType(SoundType::WOOD);
}

void LogBlock::blockStaticCtor() {
    LogBlock::LOG_AXIS = EnumProperty<LogAxis*>::create(L"axis", typeid(LogBlock::LogAxis),
                                                        LogBlock::LogAxis::VALUES, PREDICATE);
}

const BlockState* LogBlock::rotate(const BlockState* state, Rotation* rotation) {
    // why switch case here, 4J whyyyy
    switch (rotation->getType()) {
    case 1:
    case 3:
        switch (state->getValue<LogBlock::LogAxis*>(LOG_AXIS)->getId()) {
        case 0:
            return state->setValue(LOG_AXIS, LogBlock::LogAxis::Z);
        case 2:
            return state->setValue(LOG_AXIS, LogBlock::LogAxis::X);
        default:
            return state;
        }

    default:
        return state;
    }
}

void LogBlock::onRemove(Level* level, const BlockPos& pos, const BlockState* state) {
    if (level->hasChunksAt(pos.offset(-5, -5, -5), pos.offset(5, 5, 5))) {
        BlockPosIterator* it = BlockPos::between(pos.offset(-4, -4, -4), pos.offset(4, 4, 4));
        while (it->hasNext()) {
            BlockPos blockPos = *it->next();
            const BlockState* blockState = level->getBlockState(blockPos);

            if (blockState->getBlock()->getMaterial() == Material::LEAVES
                && !blockState->getValue<bool>(LeafBlock::CHECK_DECAY)) {
                level->setBlock(blockPos, blockState->setValue(LeafBlock::CHECK_DECAY, true), 4, false);
            }
        }
        delete it;
    }
}

const BlockState* LogBlock::getStateForPlacement(Level*, const BlockPos&, const Direction* direction, float,
                                                 float, float, int data, std::shared_ptr<LivingEntity>) {
    return this->getBlockState(data)->setValue(LOG_AXIS, LogAxis::fromAxis(direction->getAxis()));
}

unsigned int LogBlock::getDescriptionId(int data) {
    const BlockState* state = data == -1 ? this->defaultBlockState() : this->getBlockState(data);
    return LogBlock::DESCRIPTION_IDS[this->getWoodType(state)];
}

void LogBlock::registerIcons(IconRegister* iconReg) {
    for (int i = 0; i < 6; ++i) {
        this->type_textures[i] = iconReg->registerIcon(this->getIconName() + L"_" + LOG_VARIANTS[i]);
        this->top_textures[i] = iconReg->registerIcon(this->getIconName() + L"_" + LOG_VARIANTS[i] + L"_top");
    }
}

TextureAtlasSprite* LogBlock::getTypeTexture(const BlockState* state) {
    return type_textures[this->getWoodType(state)];
}

TextureAtlasSprite* LogBlock::getTopTexture(const BlockState* state) {
    return top_textures[this->getWoodType(state)];
}

// NON_MATCHING
Direction::Axis* LogBlock::getAxis(const BlockState* state) {
    switch (state->getValue<LogAxis*>(LOG_AXIS)->getId()) {
    case 0:
        return Direction::Axis::X;
    case 1:
        return Direction::Axis::Y;
    case 2:
        return Direction::Axis::Z;
    default:
        return nullptr;
    }
}
