#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include <string>
#include <unordered_map>

class Textures;
class Options;
class Font;
class Player;
class MapItemSavedData;

class MapRenderer {
public:
    class MapInstance {
    public:
        MapInstance(MapRenderer* holder, const std::shared_ptr<MapItemSavedData>& savedData);

        void fjUpdateWithRenderContext();
        void draw(const std::shared_ptr<Player>& player);

        MapRenderer* mMapRenderer;
        std::shared_ptr<MapItemSavedData> mSavedData;
        int mMapTextureId = -1;
        arrayWithLength<int> mMapPixels;
        bool mCreatedTexture = 0;
    };

    MapRenderer(Font*, Options*, Textures*);

    MapInstance* getMapInstance(const std::shared_ptr<MapItemSavedData>& savedData);
    void render(const std::shared_ptr<MapItemSavedData>& savedData, const std::shared_ptr<Player>& player);

    static int sMaterialColorPalette[256];
    static bool sColoursNeedReload;
    static void reloadColours();

    Textures* mTextures;
    std::unordered_map<std::wstring, MapInstance*> mMaps;
    Options* mOptions;
    Font* mFont;
};
