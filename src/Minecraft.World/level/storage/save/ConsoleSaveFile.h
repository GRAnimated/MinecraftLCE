#pragma once
#include "Minecraft.Client/ByteOrder.h"
#include "Minecraft.Client/ESavePlatform.h"
#include "Minecraft.World/level/storage/LevelStorage.h"
#include "Minecraft.Core/io/File.h"
#include "Minecraft.Core/io/FileEntry.h"

class ConsoleSaveFile {
public:
    virtual ~ConsoleSaveFile();
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3() = 0;
    virtual void vf_4() = 0;
    virtual void vf_5() = 0;
    virtual void closeHandle(FileEntry* entry) = 0;
    virtual void finalizeWrite() = 0;
    virtual void tick();
    virtual bool doesFileExist(ConsoleSavePath path) = 0;
    virtual unsigned long vf_11() = 0;
    virtual unsigned int getSizeOnDisk() = 0;
    virtual std::wstring getFilename() = 0;                            // may be u16string (:abyss:)
    virtual void* getFilesWithPrefix(const std::wstring& prefix) = 0;  // unk return type
    virtual void vf_15() = 0;
    virtual void vf_16() = 0;
    virtual void vf_17() = 0;
    virtual void vf_18() = 0;
    virtual int getSaveVersion() = 0;
    virtual int getOriginalSaveVersion() = 0;
    virtual void LockSaveAccess() = 0;
    virtual void ReleaseSaveAccess() = 0;
    virtual ESavePlatform getSavePlatform() = 0;
    virtual bool isSaveEndianDifferent() = 0;
    virtual void setLocalPlatform() = 0;
    virtual void setPlatform(ESavePlatform platform) = 0;
    virtual ByteOrder getSaveEndian() = 0;
    virtual ByteOrder getLocalEndian() = 0;
    virtual void setEndian(ByteOrder order) = 0;
    virtual void ConvertRegionFile(File regionFile) = 0;
    virtual void ConvertToLocalPlatform() = 0;
    virtual void* getWritePointer(FileEntry* entry);
    virtual void refreshFromLevelgen();
};
