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

    std::shared_ptr<MultiplayerLocalPlayer> m_player;
    MultiPlayerLevel* m_level;
    not_null_ptr<ItemInstance> m_itemInstance;
    const BlockState* m_blockState;
    BlockPos m_pos;
    InteractionResult::EInteractionResult m_interactionResult;
    bool m_playerAllowedToUse;
    bool m_playerAllowedToMine;
    bool m_itemInstanceEmpty;
    bool m_belowBuildHeight;
};
