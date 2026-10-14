#pragma once

#include "java/io/File.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include <cstddef>
#include <unordered_map>

class DataInputStream;

struct ArchiveEntry {
    std::wstring name;
    int offset = 0;
    int length = 0;
    bool compressed = false;
};

class ArchiveFile : public File {
public:
    explicit ArchiveFile(File file);
    ~ArchiveFile();
    ArchiveFile(const ArchiveFile&) = delete;
    ArchiveFile& operator=(const ArchiveFile&) = delete;

    bool hasFile(const std::wstring& name);
    arrayWithLength<unsigned char> getFile(const std::wstring& name);
    void readHeader(DataInputStream* input);

    unsigned char* m_data;
    bool m_inMemory;
    std::unordered_map<std::wstring, ArchiveEntry*> m_entries;
};

static_assert(sizeof(ArchiveEntry) == 0x28, "Original archive entry layout");
static_assert(sizeof(ArchiveFile) == 0x50, "Original archive layout");
static_assert(offsetof(ArchiveFile, m_data) == 0x18, "Original archive buffer offset");
static_assert(offsetof(ArchiveFile, m_inMemory) == 0x20, "Original archive mode offset");
static_assert(offsetof(ArchiveFile, m_entries) == 0x28, "Original archive index offset");
