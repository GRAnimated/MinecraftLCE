#pragma once

class StatsCounter {
public:
    StatsCounter();

    void clear();
    void parse(void*);

    unsigned char padding[0x60];
};
