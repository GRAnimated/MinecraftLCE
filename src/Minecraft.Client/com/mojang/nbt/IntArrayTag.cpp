#include "com/mojang/nbt/IntArrayTag.h"
#include "net/minecraft/world/ArrayWithLength.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"
#include "net/minecraft/core/System.h"
#include <cstring>

IntArrayTag::IntArrayTag() {
    mData = arrayWithLength<int>();  // it's already initialized in the header...
}

IntArrayTag::IntArrayTag(arrayWithLength<int> data) {
    mData = data;
}

void IntArrayTag::write(DataOutput* outputStream) {
    outputStream->writeInt(mData.length);
    for (unsigned int i = 0; i < mData.length; i++) {
        outputStream->writeInt(mData[i]);
    }
}

void IntArrayTag::load(DataInput* inputStream, int) {
    int size = inputStream->readInt();

    // create a copy of the data
    int* data = mData.data;
    if (data)
        delete data;

    mData = arrayWithLength<int>(size, true);

    for (int i = 0; i < size; i++) {
        mData[i] = inputStream->readInt();
    }
}

std::wstring IntArrayTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"[%d bytes]", mData.length);
    return buffer;
}

u8 IntArrayTag::getId() {
    return TAG_Int_Array;
}

bool IntArrayTag::equals(Tag* other) {
    if (!Tag::equals(other))
        return false;

    IntArrayTag* otherCasted = (IntArrayTag*)other;
    int* data = mData.data;

    if (!data)
        return otherCasted->mData.data == nullptr;

    unsigned int length = mData.length;
    if (length == otherCasted->mData.length)
        return memcmp(data, otherCasted->mData.data, sizeof(int) * length) == 0;

    return false;
}

Tag* IntArrayTag::copy() {
    arrayWithLength<int> data = arrayWithLength<int>(mData.length, true);  // copy
    System::arraycopy(mData, 0, &data, 0, mData.length);
    return new IntArrayTag(data);
}
