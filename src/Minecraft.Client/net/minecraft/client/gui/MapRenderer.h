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

        MapRenderer* m_mapRenderer;
        std::shared_ptr<MapItemSavedData> m_savedData;
        int m_mapTextureId = -1;
        arrayWithLength<int> m_mapPixels;
        bool m_createdTexture = 0;
    };

    MapRenderer(Font*, Options*, Textures*);

    MapInstance* getMapInstance(const std::shared_ptr<MapItemSavedData>& savedData);
    void render(const std::shared_ptr<MapItemSavedData>& savedData, const std::shared_ptr<Player>& player);

    static int sMaterialColorPalette[256];
    static bool sColoursNeedReload;
    static void reloadColours();

    Textures* m_textures;
    std::unordered_map<std::wstring, MapInstance*> m_maps;
    Options* m_options;
    Font* m_font;
};
