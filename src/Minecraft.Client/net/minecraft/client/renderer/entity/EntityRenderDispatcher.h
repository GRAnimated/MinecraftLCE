#pragma once

class Textures;
class ItemRenderer;

class EntityRenderDispatcher {
public:
    EntityRenderDispatcher(Textures* textures, ItemRenderer* renderer);

    unsigned char padding[0xE0];
};