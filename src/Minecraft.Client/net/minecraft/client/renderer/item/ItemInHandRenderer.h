#pragma once

#include "net/minecraft/world/InteractionHand.h"
#include "types.h"
#include <memory>

class Minecraft;
class Tesselator;
class LocalPlayer;
class ItemInstance;
class LivingEntity;
class HumanoidArm;

class ItemInHandRenderer {
public:
    enum eItemRenderMode {};

    ItemInHandRenderer(Minecraft*);
    float calculateMapTilt(float);
    void renderItem3D(Tesselator*, float, float, float, float, int, int, float,
                      ItemInHandRenderer::eItemRenderMode);
    void renderArmWithItem(std::shared_ptr<LocalPlayer> player, float partialTicks, float a4,
                           InteractionHand::EInteractionHand hand, float swingProgress,
                           not_null_ptr<ItemInstance> item, float equippedProgress);
    void renderItem(std::shared_ptr<LivingEntity> ent, not_null_ptr<ItemInstance> item, int a4, bool a5,
                    int a6, bool a7);
    void renderPlayerArm(float, float, const HumanoidArm*);
    void renderTwoHandedMap(float, float, float);
    void renderOneHandedMap(float, const HumanoidArm*, float, not_null_ptr<ItemInstance>);
    void applyItemArmTransform(const HumanoidArm*, float);
    void applyEatTransform(float, const HumanoidArm*, not_null_ptr<ItemInstance>);
    void applyItemArmAttackTransform(const HumanoidArm*, float);

    Minecraft* mMinecraft;
    not_null_ptr<ItemInstance> mMainHandItem;
    not_null_ptr<ItemInstance> mOffHandItem;
    char filler[40];
};
