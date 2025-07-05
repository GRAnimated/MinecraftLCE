#pragma once

class EntityRenderDispatcher;
class Textures;
class ItemColors;

class ItemRenderer {
public:
    ItemRenderer(EntityRenderDispatcher* dispatcher, Textures* textures, ItemColors* colors);

    unsigned char padding[0x58];
};
