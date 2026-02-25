#include "net/minecraft/world/level/block/BlockTooltipDataHolder.h"

BlockTooltipDataHolder::BlockTooltipDataHolder(std::shared_ptr<MultiplayerLocalPlayer> player,
                                               MultiPlayerLevel* level,
                                               not_null_ptr<ItemInstance> itemInstance,
                                               const BlockState* state, BlockPos pos,
                                               InteractionResult::EInteractionResult interactionResult,
                                               bool allowedToUse, bool itemInstanceEmpty, bool allowedToMine,
                                               bool belowBuildHeight) {
    this->m_player = player;
    this->m_level = level;
    this->m_itemInstance = itemInstance;
    this->m_blockState = state;
    this->m_pos = pos;
    this->m_interactionResult = interactionResult;
    this->m_playerAllowedToUse = allowedToUse;
    this->m_itemInstanceEmpty = itemInstanceEmpty;
    this->m_playerAllowedToMine = allowedToMine;
    this->m_belowBuildHeight = belowBuildHeight;
}
