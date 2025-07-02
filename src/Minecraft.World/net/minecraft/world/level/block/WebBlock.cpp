#include "Minecraft.World/level/block/WebBlock.h"

#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.World/eINSTANCEOF.h"
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/item/Item.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/item/Items.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/RenderShape.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameDef.h"
#include "Minecraft.World/level/material/Material.h"
#include "Minecraft.World/phys/AABB.h"

WebBlock::WebBlock() : Block(Material::CLOTH) {
    DerivedInit();
}

bool WebBlock::isCubeShaped(const BlockState* blockState) {
    return false;
}

RenderShape WebBlock::getRenderShape(const BlockState* blockState) {
    return RenderShape_CROSS;
}

int WebBlock::getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                                const Direction* direction) {
    return 8;
}

AABB* WebBlock::getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return AABB::sCrossShape;
}

bool WebBlock::isSolidRender(const BlockState* blockState) const {
    return false;
}

Item* WebBlock::getResource(const BlockState* blockState, Random*, int) {
    return Items::STRING;
}

int WebBlock::getRenderLayer() {
    return 0;
}

void WebBlock::entityInside(Level* level, const BlockPos& pos, const BlockState* blockState,
                            const std::shared_ptr<Entity>& entity) {
    entity->makeStuckInWeb();
    if (entity->GetType() == eFireworksRocketEntity) {
        if (Minecraft::GetInstance()->GetMiniGame()->HasFeatureDirectionalFireworks())
            entity->mCollision = true;
    }
}

void WebBlock::playerDestroy(Level* level, std::shared_ptr<Player> player, const BlockPos& pos,
                             const BlockState* blockState, std::shared_ptr<BlockEntity> blockEntity,
                             not_null_ptr<ItemInstance> itemInstance) {
    if (!level->mIsLocal && itemInstance->getItem() == Items::SHEARS) {
        ItemInstance* drop = new ItemInstance(Item::byBlock(this), true);
        popResource(level, pos, drop);
    } else {
        Block::playerDestroy(level, player, pos, blockState, blockEntity, itemInstance);
    }
}

bool WebBlock::isSilkTouchable() {
    return true;
}
