#pragma once
#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include <string>
#include <unordered_map>
#include <vector>

class BufferedImage;
class TextureAtlasSprite;
class Texture;

class TextureAtlas : public IconRegister {
public:
    TextureAtlas(int type, const std::wstring& fileName, const std::wstring& path, BufferedImage* image,
                 bool);

    virtual ~TextureAtlas() override;
    virtual TextureAtlasSprite* registerIcon(const std::wstring& name) override;
    virtual int getIconType() override;

    void addIcon(bool terrain, int y, int x, const std::wstring& id);
    void addIconWithName(bool terrain, int y, int x, const std::wstring& id, const std::wstring& name);
    void addIconSize(bool terrain, int y, int x, const std::wstring& id, int sizeX, int sizeY);
    void stitch();
    void loadUVs();

    Texture* getStitchedTexture();

    int mIconType;
    std::wstring mFileName;
    std::wstring mPath;
    std::wstring string40;
    bool idk;
    std::unordered_map<std::wstring, TextureAtlasSprite*> mTextureAtlasSprites;
    BufferedImage* mBufferedImage;
    TextureAtlasSprite* mMissingAtlasSprite;
    Texture* mStitchedTexture;
    std::vector<TextureAtlasSprite*> mAtlasSprites;
};
