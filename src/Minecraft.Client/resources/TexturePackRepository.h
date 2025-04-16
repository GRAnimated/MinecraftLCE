#pragma once

class File;
class Minecraft;

class TexturePackRepository {
    public:
    TexturePackRepository(File, Minecraft *);

    void addDebugPacks();
};