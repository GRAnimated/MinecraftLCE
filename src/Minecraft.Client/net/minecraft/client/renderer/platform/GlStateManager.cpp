#include "net/minecraft/client/renderer/platform/GlStateManager.h"

#include "NX/Render/RendererCore.h"

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
    this->m_r = r;
    this->m_g = g;
    this->m_b = b;
    this->m_a = a;
}

GlStateManager::Color::Color() {
    this->m_r = 1.0f;
    this->m_g = 1.0f;
    this->m_b = 1.0f;
    this->m_a = 1.0f;
}

GlStateManager::BooleanState::BooleanState(int state) {
    this->m_enabled = false;
    this->m_state = state;
}

void GlStateManager::BooleanState::disable() {
    this->setEnabled(false);
}

void GlStateManager::BooleanState::enable() {
    this->setEnabled(true);
}

void GlStateManager::BooleanState::setEnabled(bool enabled) {
    this->m_enabled = enabled;
    if (enabled)
        GlStateManager::enableState(this->m_state);
    else
        GlStateManager::disableState(this->m_state);
}

GlStateManager::TexGenCoord::TexGenCoord(int coord, int state) {
    this->m_coord = coord;
    this->m_enabled = new BooleanState(state);
    this->m_ode = -1;
}

GlStateManager::TexGenState::TexGenState() {
    this->m_s = new TexGenCoord(0, 0);
    this->m_t = new TexGenCoord(1, 1);
    this->m_r = new TexGenCoord(2, 3);
    this->m_q = new TexGenCoord(3, 2);
}

GlStateManager::TextureState::TextureState() {
    this->m_enabled = new BooleanState(1);
    this->m_texture = 0;
}

GlStateManager::ClearState::ClearState() {
    this->m_depth = 1.0;
    this->m_color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
    this->m_stencil = 0;
}

GlStateManager::ColorMask::ColorMask() {}

GlStateManager::DepthState::DepthState() {
    this->m_ode = new BooleanState(5);
    this->m_ask = true;
    this->m_func = 4;
}

GlStateManager::CullState::CullState() {
    this->m_enabled = new BooleanState(3);
    this->m_ode = 1;
}

GlStateManager::FogState::FogState() {
    this->m_enabled = new BooleanState(6);
    this->m_ode = 2;
    this->m_intenisty = 1.0f;
    this->m_start = 0.0f;
    this->m_end = 1.0f;
}

GlStateManager::AlphaState::AlphaState() {
    this->m_ode = new BooleanState(4);
    this->m_func = 8;
    this->m_reference = -1.0f;
}

GlStateManager::BlendState::BlendState() {
    this->m_ode = new BooleanState(2);
    this->m_srcRgb = 2;
    this->m_dstRgb = 1;
    this->m_srcAlpha = 2;
    this->m_dstAlpha = 1;
}

GlStateManager::ColorMaterialState::ColorMaterialState() {
    this->m_enabled = new BooleanState(0);
    this->m_face = 2;
    this->m_ode = 0;
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
    GlStateManager::COLOR->m_r = r;
    GlStateManager::COLOR->m_g = g;
    GlStateManager::COLOR->m_b = b;
    GlStateManager::COLOR->m_a = a;
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
    GlStateManager::COLOR_MATERIAL->m_enabled->disable();
}

void GlStateManager::enableColorMaterial() {
    GlStateManager::COLOR_MATERIAL->m_enabled->enable();
}

void GlStateManager::shadeModel(int shadeModel) {
    if (GlStateManager::sShadeModel != shadeModel)
        GlStateManager::sShadeModel = shadeModel;
}

void GlStateManager::disableBlend() {
    GlStateManager::BLEND->m_ode->disable();
}

void GlStateManager::enableBlend() {
    GlStateManager::BLEND->m_ode->enable();
}

void GlStateManager::blendFunc(int sfactor, int dfactor) {
    GlStateManager::BLEND->m_srcRgb = sfactor;
    GlStateManager::BLEND->m_dstRgb = dfactor;
    Renderer::sInstance->StateSetBlendFunc(sfactor, dfactor);
}

void GlStateManager::disableTexture() {
    GlStateManager::TEXTURES[sActiveTexture]->m_enabled->disable();
}

void GlStateManager::enableTexture() {
    GlStateManager::TEXTURES[sActiveTexture]->m_enabled->enable();
}

void GlStateManager::disableLighting() {
    GlStateManager::LIGHTING->disable();
}

void GlStateManager::enableLighting() {
    GlStateManager::LIGHTING->enable();
}

void GlStateManager::disableAlphaTest() {
    GlStateManager::ALPHA->m_ode->disable();
}

void GlStateManager::enableAlphaTest() {
    GlStateManager::ALPHA->m_ode->enable();
}

void GlStateManager::alphaFunc(int func, float reference) {
    GlStateManager::ALPHA->m_func = func;
    GlStateManager::ALPHA->m_reference = reference;
    Renderer::sInstance->StateSetAlphaFunc(func, reference);
}

void GlStateManager::bindTexture(int texture) {
    GlStateManager::TEXTURES[sActiveTexture]->m_texture = texture;
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
    GlStateManager::FOG->m_enabled->disable();
}

void GlStateManager::enableFog() {
    GlStateManager::FOG->m_enabled->enable();
}

void GlStateManager::disableCull() {
    GlStateManager::CULL->m_enabled->disable();
}

void GlStateManager::cullFace(int mode) {
    GlStateManager::CULL->m_ode = mode;
    Renderer::sInstance->StateSetFaceCullCW(mode == 1);
}

void GlStateManager::colorMask(bool r, bool g, bool b, bool a) {
    GlStateManager::COLOR_MASK->m_red = r;
    GlStateManager::COLOR_MASK->m_green = g;
    GlStateManager::COLOR_MASK->m_blue = b;
    GlStateManager::COLOR_MASK->m_alpha = a;
    Renderer::sInstance->StateSetWriteEnable(r, g, b, a);
}

void GlStateManager::ortho(double b, double t, double l, double r, double n, double f) {
    Renderer::sInstance->MatrixOrthogonal(b, t, l, r, n, f);
}

void GlStateManager::disableDepthTest() {
    GlStateManager::DEPTH->m_ode->disable();
}

void GlStateManager::enableDepthTest() {
    GlStateManager::DEPTH->m_ode->enable();
}

void GlStateManager::depthMask(bool flag) {
    GlStateManager::DEPTH->m_ask = flag;
    Renderer::sInstance->StateSetDepthMask(flag);
}

void GlStateManager::depthFunc(int func) {
    GlStateManager::DEPTH->m_func = func;
    Renderer::sInstance->StateSetDepthFunc(func);
}

void GlStateManager::clearDepth(double depth) {
    GlStateManager::CLEAR->m_depth = depth;
}

void GlStateManager::disableLight(int light) {
    GlStateManager::LIGHT_ENABLE[light - 8]->disable();
}

void GlStateManager::enableTexGen(GlStateManager::TexGen coord) {
    GlStateManager::getTexGen(coord)->m_enabled->enable();
}

void GlStateManager::disableTexGen(GlStateManager::TexGen coord) {
    GlStateManager::getTexGen(coord)->m_enabled->disable();
}

void GlStateManager::texGenMode(GlStateManager::TexGen coord, int mode) {
    GlStateManager::TexGenCoord* texGenCoord = GlStateManager::getTexGen(coord);
    if (mode != texGenCoord->m_ode)
        texGenCoord->m_ode = mode;
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
        return GlStateManager::TEX_GEN->m_s;
    case T:
        return GlStateManager::TEX_GEN->m_t;
    case R:
        return GlStateManager::TEX_GEN->m_r;
    case Q:
        return GlStateManager::TEX_GEN->m_q;
    default:
        return GlStateManager::TEX_GEN->m_s;
    }
}
