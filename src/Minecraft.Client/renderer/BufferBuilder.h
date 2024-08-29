#pragma once

class C4JRender {
public:
    enum eVertexType {};
    enum ePixelShaderType {};
};
class VertexFormat;

class BufferBuilder {
public:
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
    void blockRainQuad(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float,
                       float, float, float, int);
};