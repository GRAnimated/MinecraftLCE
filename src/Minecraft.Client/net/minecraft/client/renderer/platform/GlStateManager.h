#pragma once

class FloatBuffer;

class GlStateManager {
public:
    class Color {
    public:
        Color(float r, float g, float b, float a);
        Color();

        float m_r;
        float m_g;
        float m_b;
        float m_a;
    };
    class BooleanState {
    public:
        BooleanState(int);

        void disable();
        void enable();
        void setEnabled(bool enabled);

        int m_state;
        bool m_enabled;
    };

    // See https://docs.gl/gl2/glTexGen
    enum TexGen { S, T, R, Q };
    class TexGenCoord {
    public:
        TexGenCoord(int coord, int state);

        BooleanState* m_enabled;
        int m_coord;
        int m_ode;
    };
    class TexGenState {
    public:
        TexGenState();

        TexGenCoord* m_s;
        TexGenCoord* m_t;
        TexGenCoord* m_r;
        TexGenCoord* m_q;
    };

    class TextureState {
    public:
        TextureState();

        BooleanState* m_enabled;
        int m_texture;
    };
    class ClearState {
    public:
        ClearState();

        double m_depth;
        Color* m_color;
        int m_stencil;
    };

    class ColorMask {
    public:
        ColorMask();

        bool m_red = true;
        bool m_green = true;
        bool m_blue = true;
        bool m_alpha = true;
    };

    class DepthState {
    public:
        DepthState();

        BooleanState* m_ode;
        bool m_ask;
        int m_func;
    };

    class CullState {
    public:
        CullState();

        BooleanState* m_enabled;
        int m_ode;
    };

    class FogState {
    public:
        FogState();

        BooleanState* m_enabled;
        int m_ode;
        float m_intenisty;
        float m_start;
        float m_end;
    };

    class AlphaState {
    public:
        AlphaState();

        BooleanState* m_ode;
        int m_func;
        float m_reference;
    };

    class BlendState {
    public:
        BlendState();

        BooleanState* m_ode;
        int m_srcRgb;
        int m_dstRgb;
        int m_srcAlpha;
        int m_dstAlpha;
    };

    class ColorMaterialState {
    public:
        ColorMaterialState();

        BooleanState* m_enabled;
        int m_face;
        int m_ode;
    };

    static TexGenState* TEX_GEN;
    static ClearState* CLEAR;
    static ColorMask* COLOR_MASK;
    static DepthState* DEPTH;
    static BooleanState* LIGHT_ENABLE[8];
    static CullState* CULL;
    static FogState* FOG;
    static TextureState* TEXTURES[8];
    static AlphaState* ALPHA;
    static BooleanState* LIGHTING;
    static BlendState* BLEND;
    static Color* COLOR;
    static BooleanState* RESCALE_NORMAL;
    static ColorMaterialState* COLOR_MATERIAL;
    static int sActiveTexture;
    static int sShadeModel;

    static void staticCtor();
    static void translatef(float x, float y, float z);
    static void rotatef(float angle, float x, float y, float z);
    static void scalef(float x, float y, float z);
    static void color4f(float r, float g, float b, float a);
    static void pushMatrix();
    static void popMatrix();
    static void matrixMode(int mode);
    static void disableRescaleNormal();
    static void enableRescaleNormal();
    static void disableColorMaterial();
    static void enableColorMaterial();
    static void shadeModel(int);
    static void disableBlend();
    static void enableBlend();
    static void blendFunc(int, int);
    static void disableTexture();
    static void enableTexture();
    static void disableLighting();
    static void enableLighting();
    static void disableAlphaTest();
    static void enableAlphaTest();
    static void alphaFunc(int func, float reference);
    static void bindTexture(int texture);
    static void getMatrix(int, FloatBuffer*);
    static void loadIdentity();
    static void clear(int mask);
    static void disableFog();
    static void enableFog();
    static void disableCull();
    static void cullFace(int);
    static void colorMask(bool r, bool g, bool b, bool a);
    static void ortho(double b, double t, double l, double r, double n, double f);
    static void disableDepthTest();
    static void enableDepthTest();
    static void depthMask(bool flag);
    static void depthFunc(int func);
    static void clearDepth(double clear);
    static void disableLight(int);
    static void enableTexGen(GlStateManager::TexGen coord);
    static void disableTexGen(GlStateManager::TexGen coord);
    static void texGenMode(GlStateManager::TexGen coord, int);
    static void texGenParam(GlStateManager::TexGen coord, int, FloatBuffer*);
    static void activeTexture(int);
    static void disableClientState(int);
    static void newList(int list, int mode);
    static void endList(int);
    static void disableState(int state);
    static void enableState(int state);
    static TexGenCoord* getTexGen(GlStateManager::TexGen coord);
    static int genTexture();
    static void deleteTexture(int texture);
};
