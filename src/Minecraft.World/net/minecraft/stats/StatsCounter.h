#pragma once

class StatsCounter {
public:
    StatsCounter();

    void clear();
    void parse(void*);

    unsigned char m_padding[0x60];
};
