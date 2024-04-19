#pragma once

enum eMinecraftColour {};

class Biome {
public:
    void setNameAndDescription(int, int);
    void setPreviewColor(eMinecraftColour);
    void setWaterSkyColor(eMinecraftColour, eMinecraftColour);
};