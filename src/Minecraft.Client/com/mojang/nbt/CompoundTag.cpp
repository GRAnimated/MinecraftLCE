#include "com/mojang/nbt/CompoundTag.h"

#include "com/mojang/nbt/ByteArrayTag.h"
#include "com/mojang/nbt/ByteTag.h"
#include "com/mojang/nbt/FloatTag.h"
#include "com/mojang/nbt/IntTag.h"
#include "com/mojang/nbt/ListTag.h"
#include "com/mojang/nbt/LongTag.h"
#include "com/mojang/nbt/ShortTag.h"
#include "com/mojang/nbt/StringTag.h"
#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"
#include "java/io/File.h"
#include <memory>
#include <stdexcept>

CompoundTag::CompoundTag() = default;
// NON_MATCHING | score: 1853 (lower is better)
CompoundTag::~CompoundTag() {
    for (const auto& child : m_childTags)
        delete child.second;
}

// NON_MATCHING | score: 2304 (lower is better)
void CompoundTag::write(DataOutput* output) {
    for (const auto& child : m_childTags) {
        u8 id = child.second->getId();
        output->writeByte(id);
        if (id != TAG_End) {
            output->writeUTF(child.first);
            child.second->write(output);
        }
    }
    output->writeByte(TAG_End);
}

// NON_MATCHING | score: 2625 (lower is better)
void CompoundTag::load(DataInput* input, int depth) {
    if (depth > 512)
        return;
    for (const auto& child : m_childTags)
        delete child.second;
    m_childTags.clear();
    for (u8 id = Tag::readType(input); id != TAG_End; id = Tag::readType(input)) {
        std::wstring name = input->readUTF();
        std::unique_ptr<Tag> child(Tag::newTag(id));
        child->load(input, depth + 1);
        put(name, child.release());
    }
}

std::wstring CompoundTag::toString() {
    return formatwstr(L"%zd entries", m_childTags.size());
}
u8 CompoundTag::getId() {
    return TAG_Compound;
}
// The original CompoundTag printer is empty (0x71000e6968).
void CompoundTag::print(const std::wstring&, char*, std::wostream&) {}
bool CompoundTag::isEmpty() const {
    return m_childTags.empty();
}

// NON_MATCHING | score: 1334 (lower is better)
bool CompoundTag::equals(Tag* other) {
    if (!Tag::equals(other))
        return false;
    auto compound = static_cast<CompoundTag*>(other);
    if (m_childTags.size() != compound->m_childTags.size())
        return false;
    for (const auto& child : m_childTags) {
        Tag* value = compound->get(child.first);
        if (!value || !child.second->equals(value))
            return false;
    }
    return true;
}

CompoundTag* CompoundTag::copy() {
    CompoundTag* result = new CompoundTag();
    for (const auto& child : m_childTags)
        result->put(std::wstring(child.first.c_str()), child.second->copy());
    return result;
}

void CompoundTag::stripEmptyChildren() {
    for (auto it = m_childTags.begin(); it != m_childTags.end();) {
        Tag* child = it->second;
        child->stripEmptyChildren();
        if (child->isEmpty()) {
            delete it->second;
            it = m_childTags.erase(it);
        } else {
            ++it;
        }
    }
}

// name guessed
void CompoundTag::remove(const std::wstring& name) {
    auto it = m_childTags.find(name);
    if (it != m_childTags.end()) {
        m_childTags.erase(it);
    }
}

Tag* CompoundTag::get(const std::wstring& name) {
    auto it = m_childTags.find(name);
    return it == m_childTags.end() ? nullptr : it->second;
}
bool CompoundTag::contains(const std::wstring& name) {
    return m_childTags.find(name) != m_childTags.end();
}
// name guessed
u8 CompoundTag::getTagType(const std::wstring& name) const {
    auto it = m_childTags.find(name);
    return it == m_childTags.end() ? TAG_End : it->second->getId();
}
// NON_MATCHING | score: 1310 (lower is better)
bool CompoundTag::contains(const std::wstring& name, int type) {
    u8 id = getTagType(name);
    return id == type || (type == 99 && id >= TAG_Byte && id <= TAG_Double);
}

CompoundTag* CompoundTag::getCompound(const std::wstring& name) {
    return contains(name, TAG_Compound) ? static_cast<CompoundTag*>(m_childTags[name]) : new CompoundTag();
}
// name guessed
// NON_MATCHING | score: 50 (lower is better)
ListTag* CompoundTag::getList(const std::wstring& name, int type) {
    if (getTagType(name) == TAG_List) {
        auto list = static_cast<ListTag*>(m_childTags[name]);
        if (list->isEmpty() || list->getElementType() == type)
            return list;
    }
    return new ListTag(0);
}
// name guessed
// NON_MATCHING | score: 4187 (lower is better)
const ListTag* CompoundTag::fjSafeGetListTag(const std::wstring& name, int type) const {
    static const ListTag empty;
    auto it = m_childTags.find(name);
    if (it != m_childTags.end() && it->second->getId() == TAG_List) {
        auto list = static_cast<ListTag*>(it->second);
        if (list->isEmpty() || list->getElementType() == type)
            return list;
    }
    return &empty;
}

bool CompoundTag::getBoolean(const std::wstring& name) {
    return getByte(name) != 0;
}
byte CompoundTag::getByte(const std::wstring& name) {
    return contains(name, 99) ? static_cast<NumericTag*>(m_childTags[name])->getAsByte() : 0;
}
short CompoundTag::getShort(const std::wstring& name) {
    return contains(name, 99) ? static_cast<NumericTag*>(m_childTags[name])->getAsShort() : 0;
}
int CompoundTag::getInt(const std::wstring& name) {
    return contains(name, 99) ? static_cast<NumericTag*>(m_childTags[name])->getAsInt() : 0;
}
// name guessed
float CompoundTag::getFloat(const std::wstring& name) {
    return contains(name, 99) ? static_cast<NumericTag*>(m_childTags[name])->getAsFloat() : 0;
}
std::wstring CompoundTag::getString(const std::wstring& name) {
    return contains(name, TAG_String) ? m_childTags[name]->getAsString() : L"";
}
// NON_MATCHING | score: 720 (lower is better)
arrayWithLength<u8> CompoundTag::getByteArray(const std::wstring& name) {
    return contains(name, TAG_Byte_Array) ? static_cast<ByteArrayTag*>(get(name))->m_data :
                                            arrayWithLength<u8>();
}

void erease_if_exists(const std::unordered_map<std::wstring, Tag*>& map, const std::wstring& key, Tag* tag) {
    map.size();
    key.length();
    delete tag;
}
void CompoundTag::put(const std::wstring& name, Tag* tag) {
    Tag* old = get(name);
    if (old != tag)
        erease_if_exists(m_childTags, name, old);
    // Retain the original virtual type query before insertion.
    tag->getId();
    m_childTags[name] = tag;
}
void CompoundTag::putBoolean(const std::wstring& name, bool value) {
    putByte(name, value);
}
void CompoundTag::putByte(const std::wstring& name, byte value) {
    erease_if_exists(m_childTags, name, get(name));
    m_childTags[name] = new ByteTag(value);
}
void CompoundTag::putShort(const std::wstring& name, short value) {
    erease_if_exists(m_childTags, name, get(name));
    m_childTags[name] = new ShortTag(value);
}
void CompoundTag::putInt(const std::wstring& name, int value) {
    erease_if_exists(m_childTags, name, get(name));
    m_childTags[name] = new IntTag(value);
}
// name guessed
void CompoundTag::putLong(const std::wstring& name, long long value) {
    erease_if_exists(m_childTags, name, get(name));
    m_childTags[name] = new LongTag(value);
}
// name guessed
void CompoundTag::putFloat(const std::wstring& name, float value) {
    erease_if_exists(m_childTags, name, get(name));
    m_childTags[name] = new FloatTag(value);
}
void CompoundTag::putString(const std::wstring& name, const std::wstring& value) {
    erease_if_exists(m_childTags, name, get(name));
    m_childTags[name] = new StringTag(value);
}
void CompoundTag::putByteArray(const std::wstring& name, arrayWithLength<u8> value) {
    erease_if_exists(m_childTags, name, get(name));
    m_childTags[name] = new ByteArrayTag(value, true);
}

// name guessed
std::vector<std::wstring>* CompoundTag::getAllKeys() {
    auto keys = new std::vector<std::wstring>();
    for (const auto& child : m_childTags)
        keys->push_back(child.first);
    return keys;
}

// name guessed
std::unordered_map<std::wstring, Tag*>* CompoundTag::getAllTags() {
    return &m_childTags;
}
