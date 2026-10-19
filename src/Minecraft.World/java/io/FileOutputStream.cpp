#include "java/io/FileOutputStream.h"

#include "java/io/File.h"

bool WriteFile(nn::fs::FileHandle*, const void*, unsigned int, unsigned int*, _OVERLAPPED*);

FileOutputStream::FileOutputStream(const File& file) {
    m_file = reinterpret_cast<nn::fs::FileHandle*>(-1);
    if (!file.exists() || !isDirectory(file.m_name)) {
        char buffer[256];
        m_file = CreateFileA(wstringtofilename(file.getPath(), buffer), 0x40000000, 0, nullptr, 4, 0x80,
                             nullptr);
    }
}

FileOutputStream::~FileOutputStream() {
    if (m_file != reinterpret_cast<nn::fs::FileHandle*>(-1))
        CloseHandle(m_file);
}

// name guessed
// NON_MATCHING | score: 600 (lower is better)
void FileOutputStream::write(unsigned int value) {
    const unsigned char byte = static_cast<unsigned char>(value);
    unsigned int count;
    WriteFile(m_file, &byte, 1, &count, nullptr);
}

// name guessed
void FileOutputStream::write(arrayWithLength<unsigned char> bytes) {
    unsigned int count;
    WriteFile(m_file, bytes.m_data, bytes.m_length, &count, nullptr);
}

// name guessed
void FileOutputStream::write(arrayWithLength<unsigned char> bytes, unsigned int offset, unsigned int length) {
    unsigned int count;
    WriteFile(m_file, &bytes[offset], length, &count, nullptr);
}

void FileOutputStream::close() {
    CloseHandle(m_file);
    m_file = reinterpret_cast<nn::fs::FileHandle*>(-1);
}

void FileOutputStream::flush() {}
