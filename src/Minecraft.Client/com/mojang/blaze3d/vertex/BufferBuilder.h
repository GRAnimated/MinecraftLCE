#pragma once

#include "net/minecraft/client/renderer/C4JRender.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"

class VertexFormat;

class BufferBuilder {
public:
    struct Bounds {
        void addBounds(BufferBuilder::Bounds&);

        float bounds[6];
    };

    BufferBuilder(int);

    void clear();
    void begin(int);
    void begin();
    void normal(float, float, float);
    void tex(float, float);
    // void Bounds::addVert(float, float, float);
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
    void setMipmapEnable(bool);
    void bucket(int);
    void hasMaxVertices();
    void setVertexFormat(const VertexFormat*);
    void blockRainQuad(float, float, float, float, float, float, float, float, float, float, float, float,
                       float, float, float, float, float, float, float, float, float, float, float, float,
                       float, float, float, float, int);

    arrayWithLength<int> field_0;
    arrayWithLength<int> field_10;
    int dword_20;
    short word_24;
    short word_26;
    int dword_28;
    short word_2c;
    char gap_2E[2];
    void* qword_30;
    char byte_38;
    char byte_39;
    char gap_3A[2];
    int dword_3c;
    char byte_40;
    char gap_41[3];
    int dword_44;
    void* qword_48;
    void* qword_50;
    void* qword_58;
    void* qword_60;
    int dword_68;
    char byte_6c;
    char byte_6d;
    char byte_6e;
    char gap_6F;
    arrayWithLength<int> field_70;
    int dword_80;
    void* gap[13];
    int unk;
    Bounds mBounds;
};

ASSERT_SIZEOF(BufferBuilder, 0x110)
