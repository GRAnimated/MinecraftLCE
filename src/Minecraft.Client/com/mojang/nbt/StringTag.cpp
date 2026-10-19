#include "com/mojang/nbt/StringTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"

// NON_MATCHING | score: 815 (lower is better)
StringTag::StringTag() = default;
// name guessed
// NON_MATCHING | score: 290 (lower is better)
StringTag::StringTag(const std::wstring& value) : m_data(value) {}
StringTag::~StringTag() = default;
void StringTag::write(DataOutput* output) {
    output->writeUTF(m_data);
}
// NON_MATCHING | score: 5 (lower is better)
void StringTag::load(DataInput* input, int) {
    m_data = input->readUTF();
}
std::wstring StringTag::toString() {
    return m_data;
}
u8 StringTag::getId() {
    return TAG_String;
}
// NON_MATCHING | score: 4759 (lower is better)
bool StringTag::equals(Tag* other) {
    return Tag::equals(other) && m_data == static_cast<StringTag*>(other)->m_data;
}
Tag* StringTag::copy() {
    return new StringTag(m_data);
}
bool StringTag::isEmpty() const {
    return m_data.empty();
}
std::wstring StringTag::getAsString() {
    return m_data;
}
