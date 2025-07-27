#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/item/InteractionResultHolder.h"
class ItemInstance;
class MultiplayerLocalPlayer;
class MultiPlayerLevel;
class BlockState;

class BlockTooltipDataHolder {
public:
    BlockTooltipDataHolder(std::shared_ptr<MultiplayerLocalPlayer> player, MultiPlayerLevel* level,
                           not_null_ptr<ItemInstance> itemInstance, const BlockState* state, BlockPos pos,
                           InteractionResult::EInteractionResult interactionResult, bool allowedToUse,
                           bool itemInstanceEmpty, bool allowedToMine, bool belowBuildHeight);

    std::shared_ptr<MultiplayerLocalPlayer> mPlayer;
    MultiPlayerLevel* mLevel;
    not_null_ptr<ItemInstance> mItemInstance;
    const BlockState* mBlockState;
    BlockPos mPos;
    InteractionResult::EInteractionResult mInteractionResult;
    bool mPlayerAllowedToUse;
    bool mPlayerAllowedToMine;
    bool mItemInstanceEmpty;
    bool mBelowBuildHeight;
};