#pragma once

#include "net/minecraft/client/renderer/block/model/ItemTransforms.h"
#include "types.h"
#include <memory>

class EntityRenderDispatcher;
class Textures;
class ItemColors;
class ItemInstance;
class LivingEntity;
class TextureAtlasSprite;

class ItemRenderer {
public:
    ItemRenderer(EntityRenderDispatcher* dispatcher, Textures* textures, ItemColors* colors);

    void renderStatic(const not_null_ptr<ItemInstance>&, std::shared_ptr<LivingEntity>,
                      ItemTransforms::TransformType, float, bool, TextureAtlasSprite*);

    char padding80[80];
    bool mBool;
    char padding7[7];
};
