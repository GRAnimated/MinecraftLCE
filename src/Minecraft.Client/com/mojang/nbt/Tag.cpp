#include "com/mojang/nbt/Tag.h"

#include "com/mojang/nbt/ByteArrayTag.h"
#include "com/mojang/nbt/ByteTag.h"
#include "com/mojang/nbt/CompoundTag.h"
#include "com/mojang/nbt/DoubleTag.h"
#include "com/mojang/nbt/EndTag.h"
#include "com/mojang/nbt/FloatTag.h"
#include "com/mojang/nbt/IntArrayTag.h"
#include "com/mojang/nbt/IntTag.h"
#include "com/mojang/nbt/ListTag.h"
#include "com/mojang/nbt/LongTag.h"
#include "com/mojang/nbt/ShortTag.h"
#include "com/mojang/nbt/StringTag.h"
#include <ostream>

void Tag::print(const std::wstring& name, char* prefix, std::wostream& output) {
    output << prefix;

    const wchar_t* tagTypeName = getTagTypeName(getId());

    output << tagTypeName;

    if (!name.empty()) {
        output << L"(\"" << name << L"\")";
    }

    output << L": ";

    std::wstring tagValueStr = toString();

    output << tagValueStr << std::endl;
}

bool Tag::equals(Tag* other) {
    if (other)
        return this->getId() == other->getId();
    return false;
}

void Tag::stripEmptyChildren() {}

bool Tag::isEmpty() const {
    return false;
}

std::wstring Tag::getAsString() {
    return toString();
}

Tag* Tag::newTag(u8 id) {
    switch (id) {
    case 0:
        return new EndTag();
    case 1:
        return new ByteTag();
    case 2:
        return new ShortTag();
    case 3:
        return new IntTag();
    case 4:
        return new LongTag();
    case 5:
        return new FloatTag();
    case 6:
        return new DoubleTag();
    case 7:
        return new ByteArrayTag();
    case 8:
        return new StringTag();
    case 9:
        return new ListTag(0);
    case 10:
        return new CompoundTag();
    case 11:
        return new IntArrayTag();
    }
    return nullptr;
}

// NON_MATCHING: Our switch case doesn't get optimized
const wchar_t* Tag::getTagTypeName(u8 id) {
    switch (id) {
    case TAG_End:
        return L"TAG_End";
    case TAG_Byte:
        return L"TAG_Byte";
    case TAG_Short:
        return L"TAG_Short";
    case TAG_Int:
        return L"TAG_Int";
    case TAG_Long:
        return L"TAG_Long";
    case TAG_Float:
        return L"TAG_Float";
    case TAG_Double:
        return L"TAG_Double";
    case TAG_Byte_Array:
        return L"TAG_Byte_Array";
    case TAG_String:
        return L"TAG_String";
    case TAG_List:
        return L"TAG_List";
    case TAG_Compound:
        return L"TAG_Compound";
    case TAG_Int_Array:
        return L"TAG_Int_Array";
    case 99:
        return L"Any Numeric Tag";
    }

    return L"UNKNOWN";
}
