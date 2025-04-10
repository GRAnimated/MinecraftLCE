#pragma once

#include "types.h"

class AABB;
class Entity;
class Culler;
class ResourceLocation;
class BlockState;
class BlockPos;
class TexturePack;
class ModelDefinition;
class EntityRenderDispatcher;

class EntityRenderer {
    EntityRenderer(EntityRenderDispatcher*);
    virtual ~EntityRenderer();
    virtual void shouldRender(SharedEntity&, Culler*, double, double, double);
    virtual void shouldRender(SharedEntity&, Culler*, double);
    virtual void render(SharedEntity&, double, double, double, float, float);
    virtual void render(AABB*, double, double, double);
    virtual void renderName(SharedEntity&, double, double, double);
    virtual void shouldShowName(SharedEntity&);
    virtual void renderNameTags(SharedEntity&, double, double, double, std::wstring const&, double, int);
    virtual void bindTexture(SharedEntity&);
    virtual void bindTexture(ResourceLocation const*);
    virtual void bindTexture(std::wstring const&, int);
    virtual void bindTexture(std::wstring const&, std::wstring const&);
    virtual void getTextureLocation(SharedEntity&);
    virtual void renderFlame(SharedEntity&, double, double, double, float);
    virtual void renderShadow(SharedEntity&, double, double, double, float, float);
    virtual void getLevel();
    virtual void renderBlockShadow(BlockState const*, double, double, double, BlockPos const&, float, float,
                                   double, double, double);
    virtual void postRender(SharedEntity&, double, double, double, float, float, bool);
    virtual void getFont();
    virtual void renderNameTag(SharedEntity&, std::wstring const&, double, double, double, int, int);
    virtual void hasSecondPass();
    virtual void renderSecondPass(SharedEntity&, double, double, double, float, float);
    virtual void setupForTexturePack(TexturePack*);
    virtual void SetItemFrame(bool);
    virtual void getModel();
    virtual void getModelName();
    virtual void createModel(ModelDefinition const&);

    EntityRenderDispatcher* mDispatcher;
    int field_10;
    float field_14;
    void* field_18;
    void* field_20;
    void* field_28;
};