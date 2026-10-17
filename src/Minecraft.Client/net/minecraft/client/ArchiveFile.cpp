#include "net/minecraft/client/ArchiveFile.h"

#include "java/io/ByteArrayInputStream.h"
#include "java/io/DataInputStream.h"
#include "java/io/FileInputStream.h"
#include "net/minecraft/client/Compression.h"
#include <cstring>

[[noreturn]] void archiveLoadError(void*, const wchar_t*,
                                   ...) asm("_ZN20CConsoleMinecraftApp14FatalLoadErrorEPKwz");

ArchiveFile::ArchiveFile(File file) : File(), m_data(nullptr), m_inMemory(false) {
    File::operator=(file);
    if (!file.exists())
        archiveLoadError(nullptr, L"Unable to open archive %ls", file.getPath().c_str());
    FileInputStream fileInput(file);
    arrayWithLength<unsigned char> bytes(static_cast<unsigned int>(file.length()), true);
    fileInput.read(bytes, 0, static_cast<unsigned int>(file.length()));
    ByteArrayInputStream buffer(bytes);
    DataInputStream input(&buffer);
    m_data = bytes.m_data;
    m_inMemory = true;
    readHeader(&input);
    input.close();
    fileInput.close();
    buffer.reset();
}

ArchiveFile::~ArchiveFile() {
    delete[] m_data;
    for (auto& item : m_entries)
        delete item.second;
}

void ArchiveFile::readHeader(DataInputStream* input) {
    const int count = input->readInt();
    for (int i = 0; i < count; ++i) {
        ArchiveEntry* entry = new ArchiveEntry;
        entry->name = input->readUTF();
        entry->offset = input->readInt();
        entry->length = input->readInt();
        if (entry->name[0] == L'*') {
            entry->name = entry->name.substr(1);
            entry->compressed = true;
        }
        m_entries.insert(std::make_pair(entry->name, entry));
    }
}

bool ArchiveFile::hasFile(const std::wstring& name) {
    return m_entries.find(name) != m_entries.end();
}

arrayWithLength<unsigned char> ArchiveFile::getFile(const std::wstring& name) {
    const auto found = m_entries.find(name);
    if (found == m_entries.end()) {
        archiveLoadError(nullptr, L"Missing %ls in archive %ls", name.c_str(), getPath().c_str());
    }
    const ArchiveEntry* entry = found->second;
    arrayWithLength<unsigned char> bytes;
    if (m_inMemory) {
        bytes = arrayWithLength<unsigned char>(entry->length, true);
        std::memcpy(bytes.m_data, m_data + entry->offset, entry->length);
    } else {
        char filename[256];
        auto* file
            = CreateFileA(wstringtofilename(getPath(), filename), 0x80000000, 0, nullptr, 3, 0x80, nullptr);
        if (file == reinterpret_cast<nn::fs::FileHandle*>(-1))
            archiveLoadError(file, L"Unable to reopen archive %ls", getPath().c_str());
        SetFilePointer(file, entry->offset, nullptr, 0);
        bytes = arrayWithLength<unsigned char>(new unsigned char[entry->length], entry->length);
        unsigned int count = 0;
        if (!ReadFile(file, bytes.m_data, bytes.m_length, &count, nullptr))
            archiveLoadError(nullptr, L"Unable to read %ls from archive", name.c_str());
        CloseHandle(file);
    }
    if (entry->compressed && bytes.m_data) {
        ByteArrayInputStream buffer(bytes);
        DataInputStream input(&buffer);
        unsigned int size = input.readInt();
        input.close();
        buffer.reset();
        unsigned char* decoded = new unsigned char[size];
        Compression::getCompression()->Decompress(decoded, &size, bytes.m_data + 4, bytes.m_length - 4);
        delete[] bytes.m_data;
        bytes = arrayWithLength<unsigned char>(decoded, size);
    }
    return bytes;
}
