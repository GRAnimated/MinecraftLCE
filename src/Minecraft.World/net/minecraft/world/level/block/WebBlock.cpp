#include "net/minecraft/world/level/block/WebBlock.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/phys/AABB.h"

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
        if (Minecraft::GetInstance()->GetMiniGame()->HasFeatureDirectionalFireworks()) {
            entity->m_hasCollision = true;
        }
    }
}

void WebBlock::playerDestroy(Level* level, std::shared_ptr<Player> player, const BlockPos& pos,
                             const BlockState* blockState, std::shared_ptr<BlockEntity> blockEntity,
                             not_null_ptr<ItemInstance> itemInstance) {
    if (!level->m_isLocal && itemInstance->getItem() == Items::SHEARS) {
        ItemInstance* drop = new ItemInstance(Item::byBlock(this), true);
        popResource(level, pos, drop);
    } else {
        Block::playerDestroy(level, player, pos, blockState, blockEntity, itemInstance);
    }
}

bool WebBlock::isSilkTouchable() {
    return true;
}
