#pragma once

struct fuiSymbol {
    char m_name[64];
    int m_objectType;
    int m_objectIndex;
};

static_assert(sizeof(fuiSymbol) == 0x48, "FUI on-disk symbol layout");
