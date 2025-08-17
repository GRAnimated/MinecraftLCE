#pragma once

class Reader {
    public:
    virtual void close() = 0;
    virtual void read() = 0;
    virtual void read(wchar_t *, unsigned int, unsigned int) = 0;
};
