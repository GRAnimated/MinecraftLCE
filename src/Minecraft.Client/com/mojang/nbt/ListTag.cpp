#include "com/mojang/nbt/ListTag.h"

#include "com/mojang/nbt/NumericTag.h"

#include "com/mojang/nbt/CompoundTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"

#include <ostream>

ListTag::ListTag() : m_tagId(TAG_End) {}

ListTag::ListTag(int id) : m_tagId(id) {}

// NON_MATCHING | score: 1697 (lower is better)
ListTag::~ListTag() {
    for (Tag* tag : m_data)
        delete tag;
}

// name guessed
// NON_MATCHING | score: 1095 (lower is better)
void ListTag::add(Tag* tag) {
    if (tag->getId() == TAG_End)
        return;
    u8 id = tag->getId();
    if (m_tagId != TAG_End && m_tagId != id) {
        if (!m_data.empty())
            return;
        id = tag->getId();
    }
    m_tagId = id;
    m_data.push_back(tag);
}

// name guessed
// NON_MATCHING | score: 200 (lower is better)
size_t ListTag::size() const {
    return m_data.size();
}

// name guessed
// NON_MATCHING | score: 1545 (lower is better)
CompoundTag* ListTag::getCompound(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < m_data.size() && m_data[index]->getId() == TAG_Compound)
        return static_cast<CompoundTag*>(m_data[index]);
    return new CompoundTag();
}

bool ListTag::isEmpty() const {
    return m_data.empty();
}

void ListTag::stripEmptyChildren() {
    for (auto it = m_data.begin(); it != m_data.end();) {
        if ((*it)->isEmpty()) {
            delete *it;
            it = m_data.erase(it);
        } else {
            ++it;
        }
    }
}

void ListTag::write(DataOutput* outputStream) {
    if (m_data.empty()) {
        m_tagId = TAG_End;
    } else {
        m_tagId = m_data[0]->getId();
    }

    outputStream->writeByte(m_tagId);
    outputStream->writeInt(this->m_data.size());

    for (auto tag : m_data) {
        tag->write(outputStream);
    }
}

void ListTag::load(DataInput* inputStream, int inputSize) {
    if (inputSize <= 512) {
        m_tagId = inputStream->readChar();
        int size = inputStream->readInt();
        Tag::deleteElements(m_data);
        m_data.clear();

        for (int i = 0; i < size; ++i) {
            Tag* tag = Tag::newTag(m_tagId);
            tag->load(inputStream, inputSize);
            m_data.push_back(tag);
        }
    }
}

std::wstring ListTag::toString() {
    static wchar_t buffer[64];
    swprintf(buffer, 64, L"%zd entries of type %ls", m_data.size(), Tag::getTagTypeName(m_tagId));
    return buffer;
}

u8 ListTag::getId() {
    return TAG_List;
}

// NON_MATCHING | score: 6191 (lower is better)
void ListTag::print(const std::wstring& name, char* prefix, std::wostream& output) {
    Tag::print(name, prefix, output);

    output << prefix << "{" << std::endl;

    // finish this
}

// NON_MATCHING | score: 3610 (lower is better)
bool ListTag::equals(Tag* other) {
    if (!Tag::equals(other))
        return false;

    ListTag* otherCasted = (ListTag*)other;
    if (this->m_tagId != otherCasted->m_tagId)
        return false;

    if (this->m_data.size() != otherCasted->m_data.size())
        return false;

    for (size_t i = 0; i < m_data.size(); ++i) {
        if (!m_data[i]->equals(otherCasted->m_data[i]))
            return false;
    }

    return true;
}

Tag* ListTag::copy() {
    ListTag* copy = new ListTag(0);
    copy->m_tagId = m_tagId;

    for (auto&& tag : m_data) {
        Tag* copied = tag->copy();  // you either do this or modify vector code, because for whatever
                                    // reason push_back(value_type&& __x) has different comparision
        copy->m_data.push_back(copied);
    }

    return copy;
}

// name guessed
int ListTag::getInt(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < m_data.size()) {
        Tag* tag = m_data.at(index);
        if (tag->getId() == TAG_Int)
            return static_cast<NumericTag*>(tag)->getAsInt();
    }
    return 0;
}

double ListTag::getDouble(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < m_data.size()) {
        Tag* tag = m_data.at(index);
        if (tag->getId() == TAG_Double)
            return static_cast<NumericTag*>(tag)->getAsDouble();
    }
    return 0.0;
}

// name guessed
void ListTag::set(int index, Tag* tag) {
    u8 id = tag->getId();
    if (index < 0 || id == TAG_End || static_cast<size_t>(index) >= m_data.size())
        return;
    u8 type = m_tagId;
    id = tag->getId();
    if (type == TAG_End) {
        m_tagId = id;
    } else if (type != id) {
        if (index != 0 || m_data.end() != m_data.begin())
            return;
        m_tagId = tag->getId();
    }
    Tag* old = m_data[index];
    if (old != tag) {
        delete old;
        m_data[index] = tag;
    }
}
