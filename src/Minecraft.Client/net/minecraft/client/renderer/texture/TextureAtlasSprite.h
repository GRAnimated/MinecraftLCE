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

    char m_filler[0x90 - 8];
};
