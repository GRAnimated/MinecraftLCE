#include "net/minecraft/world/level/block/BlockTooltipDataHolder.h"

BlockTooltipDataHolder::BlockTooltipDataHolder(std::shared_ptr<MultiplayerLocalPlayer> player,
                                               MultiPlayerLevel* level,
                                               not_null_ptr<ItemInstance> itemInstance,
                                               const BlockState* state, BlockPos pos,
                                               InteractionResult::EInteractionResult interactionResult,
                                               bool allowedToUse, bool itemInstanceEmpty, bool allowedToMine,
                                               bool belowBuildHeight) {
    this->mPlayer = player;
    this->mLevel = level;
    this->mItemInstance = itemInstance;
    this->mBlockState = state;
    this->mPos = pos;
    this->mInteractionResult = interactionResult;
    this->mPlayerAllowedToUse = allowedToUse;
    this->mItemInstanceEmpty = itemInstanceEmpty;
    this->mPlayerAllowedToMine = allowedToMine;
    this->mBelowBuildHeight = belowBuildHeight;
}
