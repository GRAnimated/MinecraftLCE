#include "Minecraft.Client/renderer/GlStateManager.h"
#include "Minecraft.Client/renderer/Renderer.h"

/*
    A lot of names were taken from OpenGL docs
    If you want to know about specific function, great reference will be said docs
*/

GlStateManager::TexGenState* GlStateManager::TEX_GEN = new GlStateManager::TexGenState();
GlStateManager::ClearState* GlStateManager::CLEAR = new GlStateManager::ClearState();
GlStateManager::ColorMask* GlStateManager::COLOR_MASK = new GlStateManager::ColorMask();
GlStateManager::DepthState* GlStateManager::DEPTH = new GlStateManager::DepthState();
GlStateManager::BooleanState* GlStateManager::LIGHT_ENABLE[8];
GlStateManager::CullState* GlStateManager::CULL = new GlStateManager::CullState();
GlStateManager::FogState* GlStateManager::FOG = new GlStateManager::FogState();
GlStateManager::TextureState* GlStateManager::TEXTURES[8];
GlStateManager::AlphaState* GlStateManager::ALPHA = new GlStateManager::AlphaState();
GlStateManager::BooleanState* GlStateManager::LIGHTING = new GlStateManager::BooleanState(7);
GlStateManager::BlendState* GlStateManager::BLEND = new GlStateManager::BlendState();
GlStateManager::Color* GlStateManager::COLOR = new GlStateManager::Color();
GlStateManager::BooleanState* GlStateManager::RESCALE_NORMAL = new GlStateManager::BooleanState(0);
GlStateManager::ColorMaterialState* GlStateManager::COLOR_MATERIAL = new GlStateManager::ColorMaterialState();
int GlStateManager::sActiveTexture;
int GlStateManager::sShadeModel;

GlStateManager::Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

GlStateManager::Color::Color() {
    this->r = 1.0f;
    this->g = 1.0f;
    this->b = 1.0f;
    this->a = 1.0f;
}

GlStateManager::BooleanState::BooleanState(int state) {
    this->enabled = false;
    this->state = state;
}

void GlStateManager::BooleanState::disable() {
    this->setEnabled(false);
}

void GlStateManager::BooleanState::enable() {
    this->setEnabled(true);
}

void GlStateManager::BooleanState::setEnabled(bool enabled) {
    this->enabled = enabled;
    if (enabled)
        GlStateManager::enableState(this->state);
    else
        GlStateManager::disableState(this->state);
}

GlStateManager::TexGenCoord::TexGenCoord(int coord, int state) {
    this->coord = coord;
    this->enabled = new BooleanState(state);
    this->mode = -1;
}

GlStateManager::TexGenState::TexGenState() {
    this->s = new TexGenCoord(0, 0);
    this->t = new TexGenCoord(1, 1);
    this->r = new TexGenCoord(2, 3);
    this->q = new TexGenCoord(3, 2);
}

GlStateManager::TextureState::TextureState() {
    this->enabled = new BooleanState(1);
    this->texture = 0;
}

GlStateManager::ClearState::ClearState() {
    this->depth = 1.0;
    this->color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
    this->stencil = 0;
}

GlStateManager::ColorMask::ColorMask() {}

GlStateManager::DepthState::DepthState() {
    this->mode = new BooleanState(5);
    this->mask = true;
    this->func = 4;
}

GlStateManager::CullState::CullState() {
    this->enabled = new BooleanState(3);
    this->mode = 1;
}

GlStateManager::FogState::FogState() {
    this->enabled = new BooleanState(6);
    this->mode = 2;
    this->intenisty = 1.0f;
    this->start = 0.0f;
    this->end = 1.0f;
}

GlStateManager::AlphaState::AlphaState() {
    this->mode = new BooleanState(4);
    this->func = 8;
    this->reference = -1.0f;
}

GlStateManager::BlendState::BlendState() {
    this->mode = new BooleanState(2);
    this->srcRgb = 2;
    this->dstRgb = 1;
    this->srcAlpha = 2;
    this->dstAlpha = 1;
}

GlStateManager::ColorMaterialState::ColorMaterialState() {
    this->enabled = new BooleanState(0);
    this->face = 2;
    this->mode = 0;
}

void GlStateManager::staticCtor() {
    for (int i = 0; i < 8; i++)
        GlStateManager::LIGHT_ENABLE[i] = new GlStateManager::BooleanState(i + 8);

    for (int i = 0; i < 8; i++)
        GlStateManager::TEXTURES[i] = new GlStateManager::TextureState();
}

void GlStateManager::translatef(float x, float y, float z) {
    Renderer::sInstance->MatrixTranslate(x, y, z);
}

void GlStateManager::rotatef(float angle, float x, float y, float z) {
    Renderer::sInstance->MatrixRotate(angle * 0.017453f, x, y, z);
}

void GlStateManager::scalef(float x, float y, float z) {
    Renderer::sInstance->MatrixScale(x, y, z);
}

void GlStateManager::color4f(float r, float g, float b, float a) {
    GlStateManager::COLOR->r = r;
    GlStateManager::COLOR->g = g;
    GlStateManager::COLOR->b = b;
    GlStateManager::COLOR->a = a;
    Renderer::sInstance->StateSetColour(r, g, b, a);
}

void GlStateManager::pushMatrix() {
    Renderer::sInstance->MatrixPush();
}

void GlStateManager::popMatrix() {
    Renderer::sInstance->MatrixPop();
}

void GlStateManager::matrixMode(int mode) {
    Renderer::sInstance->MatrixMode(mode);
}

void GlStateManager::disableRescaleNormal() {
    GlStateManager::RESCALE_NORMAL->disable();
}

void GlStateManager::enableRescaleNormal() {
    GlStateManager::RESCALE_NORMAL->enable();
}

void GlStateManager::disableColorMaterial() {
    GlStateManager::COLOR_MATERIAL->enabled->disable();
}

void GlStateManager::enableColorMaterial() {
    GlStateManager::COLOR_MATERIAL->enabled->enable();
}

void GlStateManager::shadeModel(int shadeModel) {
    if (GlStateManager::sShadeModel != shadeModel)
        GlStateManager::sShadeModel = shadeModel;
}

void GlStateManager::disableBlend() {
    GlStateManager::BLEND->mode->disable();
}

void GlStateManager::enableBlend() {
    GlStateManager::BLEND->mode->enable();
}

void GlStateManager::blendFunc(int sfactor, int dfactor) {
    GlStateManager::BLEND->srcRgb = sfactor;
    GlStateManager::BLEND->dstRgb = dfactor;
    Renderer::sInstance->StateSetBlendFunc(sfactor, dfactor);
}

void GlStateManager::disableTexture() {
    GlStateManager::TEXTURES[sActiveTexture]->enabled->disable();
}

void GlStateManager::enableTexture() {
    GlStateManager::TEXTURES[sActiveTexture]->enabled->enable();
}

void GlStateManager::disableLighting() {
    GlStateManager::LIGHTING->disable();
}

void GlStateManager::enableLighting() {
    GlStateManager::LIGHTING->enable();
}

void GlStateManager::disableAlphaTest() {
    GlStateManager::ALPHA->mode->disable();
}

void GlStateManager::enableAlphaTest() {
    GlStateManager::ALPHA->mode->enable();
}

void GlStateManager::alphaFunc(int func, float reference) {
    GlStateManager::ALPHA->func = func;
    GlStateManager::ALPHA->reference = reference;
    Renderer::sInstance->StateSetAlphaFunc(func, reference);
}

void GlStateManager::bindTexture(int texture) {
    GlStateManager::TEXTURES[sActiveTexture]->texture = texture;
    Renderer::sInstance->TextureBind(texture);
}

// this requires FloatBuffer shit, not bothered now
// void GlStateManager::getMatrix(int, FloatBuffer*);

void GlStateManager::loadIdentity() {
    Renderer::sInstance->MatrixSetIdentity();
}

void GlStateManager::clear(int mask) {
    Renderer::sInstance->Clear(mask);
}

void GlStateManager::disableFog() {
    GlStateManager::FOG->enabled->disable();
}

void GlStateManager::enableFog() {
    GlStateManager::FOG->enabled->enable();
}

void GlStateManager::disableCull() {
    GlStateManager::CULL->enabled->disable();
}

void GlStateManager::cullFace(int mode) {
    GlStateManager::CULL->mode = mode;
    Renderer::sInstance->StateSetFaceCullCW(mode == 1);
}

void GlStateManager::colorMask(bool r, bool g, bool b, bool a) {
    GlStateManager::COLOR_MASK->red = r;
    GlStateManager::COLOR_MASK->green = g;
    GlStateManager::COLOR_MASK->blue = b;
    GlStateManager::COLOR_MASK->alpha = a;
    Renderer::sInstance->StateSetWriteEnable(r, g, b, a);
}

void GlStateManager::ortho(double b, double t, double l, double r, double n, double f) {
    Renderer::sInstance->MatrixOrthogonal(b, t, l, r, n, f);
}

void GlStateManager::disableDepthTest() {
    GlStateManager::DEPTH->mode->disable();
}

void GlStateManager::enableDepthTest() {
    GlStateManager::DEPTH->mode->enable();
}

void GlStateManager::depthMask(bool flag) {
    GlStateManager::DEPTH->mask = flag;
    Renderer::sInstance->StateSetDepthMask(flag);
}

void GlStateManager::depthFunc(int func) {
    GlStateManager::DEPTH->func = func;
    Renderer::sInstance->StateSetDepthFunc(func);
}

void GlStateManager::clearDepth(double depth) {
    GlStateManager::CLEAR->depth = depth;
}

void GlStateManager::disableLight(int light) {
    GlStateManager::LIGHT_ENABLE[light - 8]->disable();
}

void GlStateManager::enableTexGen(GlStateManager::TexGen coord) {
    GlStateManager::getTexGen(coord)->enabled->enable();
}

void GlStateManager::disableTexGen(GlStateManager::TexGen coord) {
    GlStateManager::getTexGen(coord)->enabled->disable();
}

void GlStateManager::texGenMode(GlStateManager::TexGen coord, int mode) {
    GlStateManager::TexGenCoord* texGenCoord = GlStateManager::getTexGen(coord);
    if (mode != texGenCoord->mode)
        texGenCoord->mode = mode;
}

// Requires more lmfao
// void GlStateManager::texGenParam(GlStateManager::TexGen coord, int, FloatBuffer*) {}

void GlStateManager::activeTexture(int texture) {
    sActiveTexture = texture;
}

void GlStateManager::disableClientState(int) {}

void GlStateManager::newList(int list, int mode) {
    Renderer::sInstance->CBuffStart(list, false);
}

void GlStateManager::endList(int) {  // there's no param in glEndList
    Renderer::sInstance->CBuffEnd();
}

void GlStateManager::enableState(int state) {
    switch ((int)state) {
    case 2:
        Renderer::sInstance->StateSetBlendEnable(true);
        break;
    case 3:
        Renderer::sInstance->StateSetFaceCull(true);
        break;
    case 4:
        Renderer::sInstance->StateSetAlphaTestEnable(true);
        break;
    case 5:
        Renderer::sInstance->StateSetDepthTestEnable(true);
        break;
    case 6:
        Renderer::sInstance->StateSetFogEnable(true);
        break;
    case 7:
        Renderer::sInstance->StateSetLightingEnable(true);
        break;
    case 8:
        Renderer::sInstance->StateSetLightEnable(0, true);
        break;
    case 9:
        Renderer::sInstance->StateSetLightEnable(1, true);
        break;
    default:
        return;
    }
}

void GlStateManager::disableState(int state) {
    switch ((int)state) {
    case 1:
        Renderer::sInstance->TextureBind(-1);
        break;
    case 2:
        Renderer::sInstance->StateSetBlendEnable(0);
        break;
    case 3:
        Renderer::sInstance->StateSetFaceCull(0);
        break;
    case 4:
        Renderer::sInstance->StateSetAlphaTestEnable(0);
        break;
    case 5:
        Renderer::sInstance->StateSetDepthTestEnable(0);
        break;
    case 6:
        Renderer::sInstance->StateSetFogEnable(0);
        break;
    case 7:
        Renderer::sInstance->StateSetLightingEnable(0);
        break;
    case 8:
        Renderer::sInstance->StateSetLightEnable(0, 0);
        break;
    case 9:
        Renderer::sInstance->StateSetLightEnable(1, 0);
        break;
    default:
        return;
    }
}

GlStateManager::TexGenCoord* GlStateManager::getTexGen(GlStateManager::TexGen coord) {
    switch (coord) {
    case S:  // why??? it doesn't match without this case
        return GlStateManager::TEX_GEN->s;
    case T:
        return GlStateManager::TEX_GEN->t;
    case R:
        return GlStateManager::TEX_GEN->r;
    case Q:
        return GlStateManager::TEX_GEN->q;
    default:
        return GlStateManager::TEX_GEN->s;
    }
}