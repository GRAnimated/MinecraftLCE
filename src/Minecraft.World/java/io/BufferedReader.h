#pragma once

#include "java/io/Reader.h"
#include <string>

class BufferedReader : public Reader {
public:
    BufferedReader(Reader* reader);

    virtual ~BufferedReader();
    void close() override;
    void read() override;
    void read(wchar_t*, unsigned int, unsigned int) override;
    std::wstring readLine();

    void bufferMore();

public:
    Reader* m_reader;
    char* m_buffer;
    void* m_unk2;
    unsigned int m_unk4;
};
