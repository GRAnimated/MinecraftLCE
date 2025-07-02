#pragma once

class FloatBuffer;

class GlStateManager {
public:
    enum TexGen {};
    class BooleanState {
        BooleanState(int);
    };
    class TextureState {
        TextureState();
    };
    static void pushMatrix();
    static void translatef(float, float, float);
    static void rotatef(float, float, float, float);
    static void popMatrix();
    static void matrixMode(int);
    static void scalef(float, float, float);
    static void enableRescaleNormal();
    static void color4f(float, float, float, float);
    static void disableRescaleNormal();
    static void enableColorMaterial();
    static void disableColorMaterial();
    static void disableTexture();
    static void shadeModel(int);
    static void enableBlend();
    static void blendFunc(int, int);
    static void disableAlphaTest();
    static void depthMask(bool);
    static void disableCull();
    static void disableBlend();
    static void enableTexture();
    static void enableAlphaTest();
    static void disableLighting();
    static void depthFunc(int);
    static void enableLighting();
    static void alphaFunc(int, float);
    static void bindTexture(int);
    static void getMatrix(int, FloatBuffer*);
    static void loadIdentity();
    static void clear(int);
    static void disableFog();
    static void cullFace(int);
    static void enableDepthTest();
    static void colorMask(bool, bool, bool, bool);
    static void ortho(double, double, double, double, double, double);
    static void disableDepthTest();
    static void disableLight(int);
    static void enableTexGen(GlStateManager::TexGen);
    static void disableTexGen(GlStateManager::TexGen);
    static void texGenMode(GlStateManager::TexGen, int);
    static void texGenParam(GlStateManager::TexGen, int, FloatBuffer*);
    static void activeTexture(int);
    static void clearDepth(double);
    static void staticCtor();
    static void disableClientState(int);
    static void newList(int, int);
    static void endList(int);
};