#include "net/minecraft/nbt/ByteArrayTag.h"
#include "net/minecraft/nbt/ByteTag.h"
#include "net/minecraft/nbt/CompoundTag.h"
#include "net/minecraft/nbt/DoubleTag.h"
#include "net/minecraft/nbt/EndTag.h"
#include "net/minecraft/nbt/FloatTag.h"
#include "net/minecraft/nbt/IntArrayTag.h"
#include "net/minecraft/nbt/IntTag.h"
#include "net/minecraft/nbt/ListTag.h"
#include "net/minecraft/nbt/LongTag.h"
#include "net/minecraft/nbt/ShortTag.h"
#include "net/minecraft/nbt/StringTag.h"
#include "net/minecraft/tags/Tag.h"
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
