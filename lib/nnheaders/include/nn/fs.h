/**
 * @file fs.h
 * @brief Filesystem implementation.
 */

#pragma once

#include <nn/account.h>
#include <nn/types.h>

namespace nn {
typedef u64 ApplicationId;

namespace fs {
using namespace ams::fs;

typedef u64 UserId;

constexpr s32 PathLengthMax = 0x300;

struct DirectoryEntry {
    char name[PathLengthMax + 1];
    char _x302[3];
    u8 type;
    char _x304;
    s64 fileSize;
};

struct FileHandle {
    void* handle;
};

struct DirectoryHandle {
    void* handle;
};

enum DirectoryEntryType { DirectoryEntryType_Directory, DirectoryEntryType_File };

enum OpenMode {
    OpenMode_Read = 1 << 0,
    OpenMode_Write = 1 << 1,
    OpenMode_Append = 1 << 2,

    OpenMode_ReadWrite = OpenMode_Read | OpenMode_Write
};

enum OpenDirectoryMode {
    OpenDirectoryMode_Directory = 1 << 0,
    OpenDirectoryMode_File = 1 << 1,
    OpenDirectoryMode_All = OpenDirectoryMode_Directory | OpenDirectoryMode_File,
};

struct ReadOption {
    u32 value;

    static const ReadOption None;
};
inline constexpr const ReadOption ReadOption::None = {0};

enum WriteOptionFlag {
    WriteOptionFlag_Flush = 1 << 0,
};

struct WriteOption {
    int flags;

    static WriteOption CreateOption(int flags) {
        WriteOption op;
        op.flags = flags;
        return op;
    }
};

// ROM
Result QueryMountRomCacheSize(size_t* size);
Result QueryMountRomCacheSize(size_t* size, nn::ApplicationId);
Result QueryMountAddOnContentCacheSize(size_t* size, int id);
Result MountRom(const char* name, void* cache, size_t cache_size);
Result MountAddOnContent(const char* name, int id, void* cache, size_t cache_size);
bool CanMountRomForDebug();
Result CanMountRom(nn::ApplicationId);
Result QueryMountRomOnFileCacheSize(u64*, FileHandle);
Result MountRomOnFile(const char*, FileHandle, void*, u64);

// SAVE
Result EnsureSaveData(const nn::account::Uid&);
Result MountSaveData(const char*, UserId);
Result MountSaveDataForDebug(const char*);
Result CommitSaveData(const char* path);

// FILE
Result GetEntryType(DirectoryEntryType* type, const char* path);
Result CreateFile(const char* filepath, s64 size);
Result OpenFile(FileHandle* out, const char* path, s32 mode);
Result SetFileSize(FileHandle fileHandle, s64 filesize);
void CloseFile(FileHandle fileHandle);
Result FlushFile(FileHandle fileHandle);
Result DeleteFile(const char* filepath);
Result RenameFile(const char* filepath, const char* newPath);
Result ReadFile(u64* outSize, FileHandle handle, s64 offset, void* buffer, u64 bufferSize,
                const ReadOption& option);
Result ReadFile(u64* outSize, FileHandle handle, s64 offset, void* buffer, u64 bufferSize);
Result ReadFile(FileHandle handle, s64 offset, void* buffer, u64 bufferSize);
Result ReadFile(FileHandle handle, s64 offset, void* buffer, u64 bufferSize,
                const ReadOption& option);
Result WriteFile(FileHandle handle, s64 fileOffset, const void* buff, u64 size,
                 const WriteOption& option);
Result GetFileSize(s64* size, FileHandle fileHandle);

// DIRECTORY
// there are three open modes; dir, file, all
Result OpenDirectory(DirectoryHandle* handle, const char* path, s32 openMode);
void CloseDirectory(DirectoryHandle directoryHandle);
Result ReadDirectory(s64* out, DirectoryEntry* entries, DirectoryHandle directoryHandle,
                     s64 maxEntryCount);
Result GetDirectoryEntryCount(s64* out, DirectoryHandle directoryHandle);

Result CreateDirectory(const char* directorypath);
Result DeleteDirectory(const char* path);
Result DeleteDirectoryRecursively(const char* path);
Result RenameDirectory(const char* path, const char* newPath);

// SD
Result MountSdCard(const char* mountPoint);
Result MountSdCardForDebug(const char*);
bool IsSdCardInserted();
Result FormatSdCard();
Result FormatSdCardDryRun();
bool IsExFatSupported();

Result MountHost(const char* mount, const char* path);
Result MountHostRoot();
Result UnmountHostRoot();

Result Unmount(const char* mountPoint);

// BCAT
Result MountBcatSaveData(const char*, ApplicationId);
Result CreateBcatSaveData(ApplicationId, s64);

}  // namespace fs
}  // namespace nn
