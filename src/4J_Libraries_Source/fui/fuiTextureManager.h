#pragma once

class fuiBitmap;
class fuiFile;

class fuiTextureManager {
public:
    void removeManagedTexture(fuiFile *file, fuiBitmap *texture);
};