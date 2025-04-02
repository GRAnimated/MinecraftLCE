#pragma once
#include <memory>
#include "types.h"

class Minecraft;
class Tesselator;
class LocalPlayer;
class InteractionHand{
public:
enum EInteractionHand{};
};
class ItemInstance;

class ItemInHandRenderer{
public:
    enum eItemRenderMode{};

    ItemInHandRenderer(Minecraft*);
    float calculateMapTilt(float);
    void renderItem3D(Tesselator *, float, float, float, float, int, int, float, ItemInHandRenderer::eItemRenderMode);
    void renderArmWithItem(std::shared_ptr<LocalPlayer> player, float partialTicks, float a4, InteractionHand::EInteractionHand hand, float swingProgress, not_null_ptr<ItemInstance> item, float equippedProgress);
};