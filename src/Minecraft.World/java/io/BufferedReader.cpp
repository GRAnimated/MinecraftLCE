#include "BufferedReader.h"
#include "cstring"

BufferedReader::BufferedReader(Reader* reader) {
    this->m_unk2 = nullptr;
    this->m_reader = reader;

    this->m_unk4 = 64;

    this->m_buffer = new char[0x100];
    memset(this->m_buffer, 0, static_cast<size_t>(this->m_unk4) * 4);  // uhhh should this be casted???

    bufferMore();
}
