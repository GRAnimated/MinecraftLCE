#pragma once

struct fuiBitmap;
struct fuiFile;

struct fuiTextureManager {
    void removeManagedTexture(fuiFile* file, fuiBitmap* texture);
};
