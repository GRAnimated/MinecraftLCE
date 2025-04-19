#pragma once
#include <string>

class DataOutputStream;
class ConsoleSaveFile;

class RegionFileCache {
public:
    DataOutputStream *_getChunkDataOutputStream(ConsoleSaveFile *save, const std::wstring &, int, int, bool);
    // only exists on Switch
    static DataOutputStream *getChunkDataOutputStream(ConsoleSaveFile *save, const std::wstring &unk, int x, int z, bool unk2) { return sInstance->_getChunkDataOutputStream(save, unk, x, z, unk2) };

    static RegionFileCache *sInstance;
};