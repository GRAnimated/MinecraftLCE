#pragma once

class File;
class DataFixerUpper;

class McRegionLevelStorageSource {
public:
    McRegionLevelStorageSource(File file, DataFixerUpper* dfu);

    unsigned char padding[40];
};