#include "net/minecraft/nbt/EndTag.h"

void EndTag::write(DataOutput*) {}

void EndTag::load(DataInput*, int) {}

std::wstring EndTag::toString() {
    return L"END";
}

u8 EndTag::getId() {
    return TAG_End;
}

bool EndTag::equals(Tag* other) {
    return Tag::equals(other);
}

Tag* EndTag::copy() {
    return new EndTag();
}
