#pragma once

#include "net/minecraft/client/model/models/PlayerModel.h"

class EntityRenderer;
class Textures;
class ItemRenderer;

class EntityRenderDispatcher {
public:
    EntityRenderDispatcher(Textures* textures, ItemRenderer* renderer);

    EntityRenderer* getPlayerRenderer(EPlayerModelType);

    unsigned char padding[0xE0];
};
