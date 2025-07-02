#include "NX/Platform.h"
#include "java/io/ByteArrayInputStream.h"

ByteArrayInputStream::ByteArrayInputStream(arrayWithLength<unsigned char> array, unsigned int start,
                                           unsigned int length) {
    mLength = std::min(start + length, array.length);
    mCurrentPos = start;
    mNextPos = start;
    mBuffer = array;
}

ByteArrayInputStream::ByteArrayInputStream(arrayWithLength<unsigned char> array) {
    mLength = array.length;
    mCurrentPos = 0;
    mNextPos = 0;
    mBuffer = array;
}

ByteArrayInputStream::~ByteArrayInputStream() {
    delete[] mBuffer.data;
}

int ByteArrayInputStream::read() {
    if (mNextPos < mLength)
        return mBuffer[mNextPos++];
    return -1;
}

int ByteArrayInputStream::read(arrayWithLength<unsigned char> array) {
    return read(array, 0, array.length);
}

int ByteArrayInputStream::read(arrayWithLength<unsigned char> array, unsigned int start,
                               unsigned int length) {
    if (mNextPos == mLength)
        return -1;

    int amount = std::min(length, mLength - mNextPos);
    XMemCpy(&array[start], &mBuffer[mNextPos], amount);
    mNextPos += amount;

    return amount;
}

void ByteArrayInputStream::close() {}

long long ByteArrayInputStream::skip(long long amount) {
    int newPos = mNextPos + amount;

    if (newPos > mLength)
        newPos = mLength;

    int difference = newPos - mNextPos;
    mNextPos = newPos;

    return difference;
}
