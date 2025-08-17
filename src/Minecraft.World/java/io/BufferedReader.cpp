#include "BufferedReader.h"
#include "cstring"

BufferedReader::BufferedReader(Reader* reader) {
    this->mUnk2 = nullptr;
    this->mReader = reader;

    this->mUnk4 = 64;

    this->mBuffer = new char[0x100];
    memset(this->mBuffer, 0, static_cast<size_t>(this->mUnk4) * 4);  // uhhh should this be casted???

    bufferMore();
}
