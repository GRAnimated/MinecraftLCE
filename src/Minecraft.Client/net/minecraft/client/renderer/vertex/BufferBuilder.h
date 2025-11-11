#pragma once

#include "NX/Render/C4JRender.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"

class VertexFormat;

// TODO: figure those out
extern "C" bool globalEnableFlag;  // DAT_71017c2158 not sure what this is
extern "C" bool DAT_71017c2159;

// TODO: this is a placeHolder, move this to somewhere else, and implement it
class MemoryTracker {
public:
    static void* createIntBuffer(int size);
};

class BufferBuilder {
public:
    struct Bounds {
        void initBounds();  // on WII U this code is inlined so we have no symbol, this is my guess

        void addBounds(BufferBuilder::Bounds&);
        void addVert(float, float, float);
        float bounds[6];
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

    arrayWithLength<int>* mVertexData;
    arrayWithLength<uchar>* field_8;
    int mVertexCount;
    float mTexU;
    float mTexV;
    union {  // yea i know, i also hate this
        int dword_1c;
        struct {
            short short_1c;
            short short_1e;
        };
    };
    int mPackedColor;
    bool mHasColor;
    bool mHasTex;
    char byte_26;
    bool mHasNormal;
    uint32_t mBufferIndex;
    bool mUseCompactVerts;
    bool mUseProjectedTex;
    char gap_2E[2];
    int dword_30;
    C4JRender::eVertexType mVertType;  // i suspect this is used as size in bytes of a vertex, beacuse it's
                                       // used often with useCompactVerts
    bool mHasBoneIndex;
    char byte_39;
    char gap_3A[2];
    uint32_t dword_3c;
    bool mNoColor;
    char gap_41[3];
    C4JRender::ePrimitiveType mPrimitiveMode;
    float mXo;  // i'm not sure but i assume those are offsets !?
    float mYo;
    float mZo;
    float dword_54;
    float dword_58;
    float dword_5c;
    uint32_t mPackedNormal;
    int mBoneIndex;
    int mBucket;
    bool mHasBegun;  // meh name
    bool mIsMipmapEnabled;
    char byte_6e;
    char gap_6F;
    void* field_70;
    int field_78;
    int field_7c;
    int mBufferSize;
    void* gap[13];
    int unk;
    Bounds mBounds;
};

ASSERT_SIZEOF(BufferBuilder, 0x110)
