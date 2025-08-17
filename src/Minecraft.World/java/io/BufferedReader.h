#pragma once
#include "Reader.h"
#include <string>

class BufferedReader : public Reader {
public:
    BufferedReader(Reader *reader);

    virtual ~BufferedReader();
    void close() override;
    void read() override;
    void read(wchar_t*, unsigned int, unsigned int) override;
    std::wstring readLine();

    void bufferMore();

public:
    Reader *mReader;
    char *mBuffer;
    void *mUnk2;
    unsigned int mUnk4;
};
