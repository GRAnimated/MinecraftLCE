#pragma once

class EntityRenderDispatcher;
class Textures;
class ItemColors;

class ItemRenderer {
    public:
    ItemRenderer(EntityRenderDispatcher *dispatcher, Textures *textures, ItemColors *colors);
};