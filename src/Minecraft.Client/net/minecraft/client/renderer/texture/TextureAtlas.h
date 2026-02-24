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

    ~TextureAtlas() override;
    TextureAtlasSprite* registerIcon(const std::wstring& name) override;
    int getIconType() override;

    void addIcon(bool terrain, int y, int x, const std::wstring& id);
    void addIconWithName(bool terrain, int y, int x, const std::wstring& id, const std::wstring& name);
    void addIconSize(bool terrain, int y, int x, const std::wstring& id, int sizeX, int sizeY);
    void stitch();
    void loadUVs();

    Texture* getStitchedTexture();

    int m_iconType;
    std::wstring m_fileName;
    std::wstring m_path;
    std::wstring m_string40;
    bool m_idk;
    std::unordered_map<std::wstring, TextureAtlasSprite*> m_textureAtlasSprites;
    BufferedImage* m_bufferedImage;
    TextureAtlasSprite* m_missingAtlasSprite;
    Texture* m_stitchedTexture;
    std::vector<TextureAtlasSprite*> m_atlasSprites;
};
