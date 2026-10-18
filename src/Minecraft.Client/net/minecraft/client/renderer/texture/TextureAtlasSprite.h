#pragma once

#include <string>

class TextureAtlasSprite {
public:
    TextureAtlasSprite(const std::wstring& id, const std::wstring& name, float u0, float v0, float u1,
                       float v1);

    static TextureAtlasSprite* create(const std::wstring&);

    virtual ~TextureAtlasSprite();
    virtual int getX() const;
    virtual int getY() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual float getU0(bool) const;
    virtual float getU1(bool) const;
    virtual float getU(double) const;
    virtual float getV0(bool) const;
    virtual float getV1(bool) const;
    virtual float getV(double) const;
    virtual std::wstring getName() const;
    virtual int getSourceWidth() const;
    virtual int getSourceHeight() const;
    virtual void cycleFrames();
    virtual int getFrames();
    virtual int getFlags() const;
    virtual void setFlags(int);
    virtual void freeFrameTextures();
    virtual bool hasOwnData();

    void adjustUV(float&, float&);
    void initUVs(float u0, float v0, float u1, float v1);

    char m_filler[0x60 - 8];
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    float m_u0;
    float m_u1;
    float m_v0;
    float m_v1;
    char m_gap80[0x10];
};

static_assert(sizeof(TextureAtlasSprite) == 0x90, "TextureAtlasSprite size");
