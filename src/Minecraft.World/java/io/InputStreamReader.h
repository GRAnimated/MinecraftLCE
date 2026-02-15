#pragma once

#include "DataInputStream.h"
#include "java/io/Reader.h"

class InputStreamReader : public Reader {
public:
    InputStreamReader(InputStream* stream);

    virtual ~InputStreamReader();
    void close() override;
    void read() override;
    void read(wchar_t*, unsigned int, unsigned int) override;

private:
    DataInputStream* m_stream;
};
