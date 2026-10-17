#include "java/io/FileInputStream.h"

#include "java/io/File.h"

// The target supplies no usable app object at these call sites. Keep its
// argument registers and ABI symbol without constructing a host app singleton.
[[noreturn]] void fileLoadError(nn::fs::FileHandle*, const wchar_t*,
                                ...) asm("_ZN20CConsoleMinecraftApp14FatalLoadErrorEPKwz");

FileInputStream::FileInputStream(const File& file) {
    m_eof = false;
    char buffer[256];
    const char* filename = wstringtofilename(file.getPath(), buffer);
    m_file = CreateFileA(filename, 0x80000000, 0, nullptr, 3, 0x80, nullptr);
    if (m_file == reinterpret_cast<nn::fs::FileHandle*>(-1))
        fileLoadError(m_file, L"<FileInputStream@%d> Failed to open %ls", 0x34, file.getPath().c_str());
}

FileInputStream::~FileInputStream() {
    if (m_file != reinterpret_cast<nn::fs::FileHandle*>(-1))
        CloseHandle(m_file);
}

int FileInputStream::read() {
    if (m_eof)
        return -1;
    unsigned char value = 0;
    unsigned int count;
    if (!ReadFile(m_file, &value, 1, &count, nullptr))
        fileLoadError(reinterpret_cast<nn::fs::FileHandle*>(0), L"<FileInputStream@%d> Failed to read", 0x58);
    if (count != 0)
        return value;
    m_eof = true;
    return -1;
}

int FileInputStream::read(arrayWithLength<unsigned char> bytes) {
    if (m_eof)
        return -1;
    unsigned int count;
    if (!ReadFile(m_file, bytes.m_data, bytes.m_length, &count, nullptr))
        fileLoadError(reinterpret_cast<nn::fs::FileHandle*>(0), L"<FileInputStream@%d> Failed to read array",
                      0x7f);
    if (count != 0)
        return count;
    m_eof = true;
    return -1;
}

int FileInputStream::read(arrayWithLength<unsigned char> bytes, unsigned int offset, unsigned int length) {
    if (m_eof)
        return -1;
    unsigned int count;
    const int result = ReadFile(m_file, &bytes[offset], length, &count, nullptr);
    if (!result)
        fileLoadError(reinterpret_cast<nn::fs::FileHandle*>(0),
                      L"<FileInputStream@%d> Failed to read special", 0xac);
    // Ghidra loses the returned count on this path; ARM64 execution confirms
    // that the offset overload also returns the number of bytes read.
    if (count != 0)
        return count;
    m_eof = true;
    return -1;
}

void FileInputStream::close() {
    if (m_file != reinterpret_cast<nn::fs::FileHandle*>(-1)) {
        CloseHandle(m_file);
        m_file = reinterpret_cast<nn::fs::FileHandle*>(-1);
    }
}

long long FileInputStream::skip(long long amount) {
    return 0;
}

unsigned int FileInputStream::filesize() {
    if (m_file != reinterpret_cast<nn::fs::FileHandle*>(-1))
        return GetFileSize(m_file, nullptr);
    return 0;
}
