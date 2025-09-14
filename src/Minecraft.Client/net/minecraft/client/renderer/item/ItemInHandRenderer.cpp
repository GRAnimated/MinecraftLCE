#include "net/minecraft/client/renderer/item/ItemInHandRenderer.h"

#include "NX/Render/RendererCore.h"
#include "com/mojang/blaze3d/platform/GlStateManager.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/util/HumanoidArm.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/InteractionHand.h"
#include "net/minecraft/world/entity/player/LocalPlayer.h"
#include "net/minecraft/world/entity/player/MultiplayerLocalPlayer.h"
#include "net/minecraft/world/item/BowItem.h"
#include "net/minecraft/world/item/Items.h"

const float xTranslates[2] = {-0.3f, 0.3f};
const float armTransformX[2] = {-0.56f, 0.56f};

void ItemInHandRenderer::applyItemArmTransform(const HumanoidArm* arm, float equippedProgress) {
    GlStateManager::translatef(armTransformX[HumanoidArm::RIGHT == arm], (equippedProgress * -0.6f) + -0.52f,
                               -0.72f);
}

// NON_MATCHING: most random shit just to match other
void ItemInHandRenderer::renderItem(std::shared_ptr<LivingEntity> ent, not_null_ptr<ItemInstance> item,
                                    int a4, bool a5, int a6, bool a7) {
    this->mOffHandItem->setCount(1);
    ent->setArrowCount(a4);
    item->setCount(a5);
    ent->setArrowCount(a7);
}

void ItemInHandRenderer::applyItemArmAttackTransform(const HumanoidArm* arm, float swingProgress) {
    int i = arm == HumanoidArm::RIGHT ? 1 : -1;
    float f = Mth::sin(swingProgress * swingProgress * Mth::PI);
    GlStateManager::rotatef(i * (45.0f + f * -20.0f), 0.0f, 1.0f, 0.0f);
    float f1 = Mth::sin(Mth::sqrt(swingProgress) * Mth::PI);
    GlStateManager::rotatef(i * f1 * -20.0f, 0.0f, 0.0f, 1.0f);
    GlStateManager::rotatef(f1 * -80.0f, 1.0f, 0.0f, 0.0f);
    GlStateManager::rotatef(i * -45.0f, 0.0f, 1.0f, 0.0f);
}

void ItemInHandRenderer::renderArmWithItem(std::shared_ptr<LocalPlayer> player, float partialTicks, float a4,
                                           InteractionHand::EInteractionHand hand, float swingProgress,
                                           not_null_ptr<ItemInstance> item, float equippedProgress) {
    const HumanoidArm* arm
        = hand == InteractionHand::MAIN_HAND ? player->getMainArm() : player->getMainArm()->getOpposite();

    float x = 0.0f, y = 0.0f;
    bool smth = false;

    if (player) {
        if (player->mItemRendererThingy == 1 || player->mItemRendererThingy == 2) {
            y = 0.08f;
            smth = true;
        } else if (player->mItemRendererThingy == 3 || player->mItemRendererThingy == 4
                   || !Renderer::sInstance->IsWidescreen()) {
            x = xTranslates[arm == HumanoidArm::LEFT];
        }
    }

    GlStateManager::pushMatrix();
    if (item->isEmpty()) {
        if (hand == InteractionHand::MAIN_HAND && !player->isInvisible()) {
            GlStateManager::translatef(x, y, 0.0f);
            this->renderPlayerArm(equippedProgress, swingProgress, arm);
        }
    } else if (item->getItem() == Items::FILLED_MAP) {
        if (smth)
            GlStateManager::translatef(0.0f, 0.0f, -0.3f);
        if (hand != InteractionHand::MAIN_HAND || !mOffHandItem->isEmpty()) {
            GlStateManager::translatef(x, y, 0.0f);
            this->renderOneHandedMap(equippedProgress, arm, swingProgress, item);
        } else {
            this->renderTwoHandedMap(a4, equippedProgress, swingProgress);
        }
    } else {
        bool right_arm = arm == HumanoidArm::RIGHT;

        if (player->isUsingItem() && player->getUsedItemHand() == hand) {
            int i = right_arm ? 1 : -1;

            switch (item->getUseAnimation()) {
            case 0:
                GlStateManager::translatef(x, y, 0.0f);
                this->applyItemArmTransform(arm, equippedProgress);
                break;
            case 1:
            case 2:
                this->applyEatTransform(partialTicks, arm, item);
                this->applyItemArmTransform(arm, equippedProgress);
                break;
            case 3:
                this->applyItemArmTransform(arm, equippedProgress);
                if (item->getItem() != Items::WOODEN_SWORD && item->getItem() != Items::STONE_SWORD
                    && item->getItem() != Items::IRON_SWORD && item->getItem() != Items::GOLDEN_SWORD
                    && item->getItem() != Items::DIAMOND_SWORD) {
                    break;
                }
                GlStateManager::translatef(i * -0.2f, 0.08f, 0.0f);
                GlStateManager::rotatef(-80.0f, 1.0f, 0.0f, 0.0f);
                GlStateManager::rotatef(i * 10.0f, 0.0f, 1.0f, 0.0f);
                GlStateManager::rotatef(i * 60.0f, 0.0f, 0.0f, 1.0f);
                break;
            case 4:
                GlStateManager::translatef(x, y, 0.0f);
                this->applyItemArmTransform(arm, equippedProgress);
                GlStateManager::translatef(i * -0.27857f, 0.18344f, 0.15732f);
                GlStateManager::rotatef(-13.935f, 1.0f, 0.0f, 0.0f);
                GlStateManager::rotatef(i * 35.3f, 0.0f, 1.0f, 0.0f);
                GlStateManager::rotatef(i * -9.785f, 0.0f, 0.0f, 1.0f);
                float a
                    = item->getUseDuration()
                      - (this->mMinecraft->mLocalPlayer->getUseItemRemainingTicks() - partialTicks + 1.0f);
                float b = a / BowItem::GetMaxBowDuration();
                b = (b * b + b * 2.0f) / 3.0f;

                if (b > 1.0f) {
                    b = 1.0f;
                }

                if (b > 0.1f) {
                    float c = Mth::sin((a - 0.1f) * 1.3f);
                    float d = b - 0.1f;
                    float e = c * d;
                    GlStateManager::translatef(e * 0.0f, e * 0.004f, e * 0.0f);
                }

                GlStateManager::translatef(b * 0.0f, b * 0.0f, b * 0.04f);
                GlStateManager::scalef(1.0f, 1.0f, 1.0f + b * 0.2f);
                GlStateManager::rotatef(i * 45.0f, 0.0f, -1.0f, 0.0f);
                break;
            }
        } else {
            if (swingProgress == 0.0f)
                GlStateManager::translatef(x, y, 0.0f);

            float a = -0.4f * Mth::sin(Mth::sqrt(swingProgress) * Mth::PI);
            float b = 0.2f * Mth::sin(Mth::sqrt(swingProgress) * (Mth::PI * 2.0f));
            float c = -0.2f * Mth::sin(swingProgress * Mth::PI);
            int i = right_arm ? 1 : -1;
            GlStateManager::translatef(i * a, b, c);
            this->applyItemArmTransform(arm, equippedProgress);
            this->applyItemArmAttackTransform(arm, swingProgress);
        }
        this->renderItem(player, item, right_arm ? 4 : 3, !right_arm, 0, true);
    }
    GlStateManager::popMatrix();
}
