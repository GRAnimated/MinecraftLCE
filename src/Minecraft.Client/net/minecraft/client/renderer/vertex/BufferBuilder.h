#pragma once

#include "NX/Render/C4JRender.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"

class VertexFormat;

class BufferBuilder {
public:
    struct Bounds {
        void initBounds();  // on WII U this code is inlined so we have no symbol, this is my guess

        void addBounds(BufferBuilder::Bounds&);
        void addVert(float, float, float);
        float m_bounds[6];
    };

    BufferBuilder(int);

    void sub_710063830c();
    void clear();
    void begin(int type);
    void begin();
    void normal(float, float, float);
    void tex(float, float);
    void finaliseShaders();
    void end();
    void vertexNoBounds(float, float, float);
    void vertex(float, float, float);
    void vertexUV(float, float, float, float, float);
    void useCompactVertices(bool);
    void useProjectedTexture(bool);
    void setVertexAndPixelShader(C4JRender::eVertexType, C4JRender::ePixelShaderType);
    void useDefaultShaders();
    void tex2(int);
    void color(int, int, int, int);
    void color(int, int, int);
    void color(float, float, float);
    void color(float, float, float, float);
    void boneIndex(int);
    void vertexUVSkinned(float, float, float, float, float, int);
    void vertexDouble(double, double, double);
    void color(int);
    void color(int, int);
    void noColor();
    void offset(float, float, float);
    void addOffset(float, float, float);
    bool setMipmapEnable(bool);
    void bucket(int);
    int hasMaxVertices();
    void setVertexFormat(const VertexFormat*);
    void blockRainQuad(float, float, float, float, float, float, float, float, float, float, float, float,
                       float, float, float, float, float, float, float, float, float, float, float, float,
                       float, float, float, float, int);

    arrayWithLength<int>* m_vertexData;
    arrayWithLength<uchar>* m_field8;
    int m_vertexCount;
    float m_texU;
    float m_texV;
    union {  // yea i know, i also hate this
        int m_dword1c;
        struct {
            short m_short1c;
            short m_short1e;
        };
    };
    int m_packedColor;
    bool m_hasColor;
    bool m_hasTex;
    char m_byte26;
    bool m_hasNormal;
    uint32_t m_bufferIndex;
    bool m_useCompactVerts;
    bool m_useProjectedTex;
    char m_gap2E[2];
    int m_dword30;
    C4JRender::eVertexType m_vertType;  // i suspect this is used as size in bytes of a vertex, beacuse it's
                                        // used often with useCompactVerts
    bool m_hasBoneIndex;
    char m_byte39;
    char m_gap3A[2];
    uint32_t m_dword3c;
    bool m_noColor;
    char m_gap41[3];
    C4JRender::ePrimitiveType m_primitiveMode;
    float m_xo;  // i'm not sure but i assume those are offsets !?
    float m_yo;
    float m_zo;
    float m_dword54;
    float m_dword58;
    float m_dword5c;
    uint32_t m_packedNormal;
    int m_boneIndex;
    int m_bucket;
    bool m_hasBegun;  // meh name
    bool m_isMipmapEnabled;
    char m_byte6e;
    char m_gap6F;
    void* m_field70;
    int m_field78;
    int m_field7c;
    int m_bufferSize;
    void* m_gap[13];
    int m_unk;
    Bounds m_bounds;

    static bool TRIANGLE_MODE;
    static bool VBO_MODE;
};

ASSERT_SIZEOF(BufferBuilder, 0x110)
