#include "com/mojang/nbt/ListTag.h"

#include "net/minecraft/core/io/DataInput.h"
#include "net/minecraft/core/io/DataOutput.h"

#include <ostream>

ListTag::ListTag() {}

ListTag::ListTag(int id) : mTagId(id) {}

// NON_MATCHING: Missing block of assembly in the mData loop
void ListTag::write(DataOutput* outputStream) {
    if (mData.size() < 1) {
        mTagId = mData[0]->getId();
    } else {
        mTagId = TAG_End;
    }

    outputStream->writeByte(mTagId);

    for (auto& tag : mData) {
        tag->write(outputStream);
    }
}

void ListTag::load(DataInput* inputStream, int inputSize) {
    if (inputSize <= 512) {
        mTagId = inputStream->readChar();
        int size = inputStream->readInt();
        Tag::deleteElements(mData);
        mData.clear();

        for (int i = 0; i < size; ++i) {
            Tag* tag = Tag::newTag(mTagId);
            tag->load(inputStream, inputSize);
            mData.push_back(tag);
        }
    }
}

std::wstring ListTag::toString() {
    static wchar_t buffer[64];
    swprintf(buffer, 64, L"%zd entries of type %ls", mData.size(), Tag::getTagTypeName(mTagId));
    return buffer;
}

u8 ListTag::getId() {
    return TAG_List;
}

// NON_MATCHING: Unfinished
void ListTag::print(const std::wstring& name, char* prefix, std::wostream& output) {
    Tag::print(name, prefix, output);

    output << prefix << "{" << std::endl;

    // finish this
}

// NON_MATCHING: Fuck my shitty life because the pseudocode is unreadable
bool ListTag::equals(Tag* other) {
    if (!Tag::equals(other))
        return false;

    ListTag* otherCasted = (ListTag*)other;
    if (this->mTagId != otherCasted->mTagId)
        return false;

    if (this->mData.size() != otherCasted->mData.size())
        return false;

    for (size_t i = 0; i < mData.size(); ++i) {
        if (!mData[i]->equals(otherCasted->mData[i]))
            return false;
    }

    return true;
}

// NON_MATCHING: b.eq vs b.hs in std for loop
Tag* ListTag::copy() {
    ListTag* copy = new ListTag(0);
    copy->mTagId = mTagId;

    for (auto& tag : mData) {
        copy->mData.push_back(tag->copy());
    }

    return copy;
}
