#pragma once

enum eMinecraftColour {};
class MobCategory;

class Biome {
public:
    void setNameAndDescription(int, int);
    void setPreviewColor(eMinecraftColour);
    void setWaterSkyColor(eMinecraftColour, eMinecraftColour);

    void getMobs(MobCategory*);
};