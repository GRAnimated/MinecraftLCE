#include "java/io/ByteArrayOutputStream.h"

#include "net/minecraft/client/platform/NX/Platform.h"

ByteArrayOutputStream::ByteArrayOutputStream() {
    mSize = 0;
    mBuffer = arrayWithLength<unsigned char>(0x20, true);
}

ByteArrayOutputStream::ByteArrayOutputStream(unsigned int size) {
    mSize = 0;
    mBuffer = arrayWithLength<unsigned char>(size, true);
}

ByteArrayOutputStream::~ByteArrayOutputStream() {
    delete[] mBuffer.data;
}

void ByteArrayOutputStream::write(unsigned int byte) {
    if (mSize + 1 >= mBuffer.length)
        mBuffer.resize(mBuffer.length * 2);

    mBuffer[mSize] = byte;
    mSize++;
}

void ByteArrayOutputStream::write(arrayWithLength<unsigned char> array) {
    write(array, 0, array.length);
}

void ByteArrayOutputStream::write(arrayWithLength<unsigned char> array, unsigned int start,
                                  unsigned int length) {
    if (mSize + length >= mBuffer.length)
        mBuffer.resize(std::max(mSize + length + 1, mBuffer.length * 2));

    XMemCpy(&mBuffer[mSize], &array[start], length);

    mSize += length;
}

void ByteArrayOutputStream::close() {}

arrayWithLength<unsigned char> ByteArrayOutputStream::toByteArray() {
    return arrayWithLength<unsigned char>::createFromOther(mBuffer);
}
