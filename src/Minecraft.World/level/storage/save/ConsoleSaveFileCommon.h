#pragma once
#include "ConsoleSaveFile.h"

class ConsoleSaveFileCommon : public ConsoleSaveFile {
public:
    ~ConsoleSaveFileCommon() override;
    void closeHandle(FileEntry* entry) override;
    void finalizeWrite() override;
    bool doesFileExist(ConsoleSavePath path) override;
    unsigned int getSizeOnDisk() override;
    std::wstring getFilename() override;
    void* getFilesWithPrefix(const std::wstring& prefix) override;
    void vf_16() override;
    void vf_17() override;
    void vf_18() override;
    int getSaveVersion() override;
    int getOriginalSaveVersion() override;
    void LockSaveAccess() override;
    void ReleaseSaveAccess() override;
    ESavePlatform getSavePlatform() override;
    bool isSaveEndianDifferent() override;
    void setLocalPlatform() override;
    void setPlatform(ESavePlatform platform) override;
    ByteOrder getSaveEndian() override;
    ByteOrder getLocalEndian() override;
    void setEndian(ByteOrder order) override;
    void ConvertRegionFile(File regionFile) override;
    void ConvertToLocalPlatform() override;
    void* getWritePointer(FileEntry* entry) override;
    void refreshFromLevelgen() override;
    virtual void vf_32() = 0;
    virtual void vf_33() = 0;
    virtual bool isLocalEndianDifferent(ESavePlatform platform);
    virtual bool fjHasRegionFile(const File& regionFile);  // return type guessed
};