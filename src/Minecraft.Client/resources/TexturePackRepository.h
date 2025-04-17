#pragma once

class File;
class Minecraft;

class TexturePackRepository {
public:
    TexturePackRepository(File, Minecraft*);

    void addDebugPacks();
    bool getSelected();

    unsigned char padding[0xA8];
};