#include "Minecraft.Core/io/BufferedOutputStream.h"

#include "Minecraft.World/ArrayWithLength.h"

BufferedOutputStream::BufferedOutputStream(OutputStream* outputStream, int bufferSize) {
    mOutputStream = outputStream;
    mBuffer = arrayWithLength<unsigned char>(bufferSize, true);
    mSize = 0;
}

BufferedOutputStream::~BufferedOutputStream() {
    delete mBuffer.data;
    mBuffer.data = nullptr;
}

void BufferedOutputStream::write(unsigned int byte) {
    mBuffer[mSize++] = byte;
    if (mSize == mBuffer.length) {
        flush();
    }
}

void BufferedOutputStream::write(arrayWithLength<unsigned char> array) {
    write(array, 0, array.length);
}

void BufferedOutputStream::write(arrayWithLength<unsigned char> array, unsigned int start,
                                 unsigned int length) {
    if (length >= mBuffer.length) {
        flush();
        mOutputStream->write(array, start, length);
        return;
    }
    for (unsigned int i = 0; i < length; ++i) {
        write(array[start + i]);
    }
}

void BufferedOutputStream::close() {
    flush();
    mOutputStream->close();
}

void BufferedOutputStream::flush() {
    mOutputStream->write(mBuffer, 0, mSize);
    mSize = 0;
}
