#include "com/mojang/nbt/ListTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"

#include <ostream>

ListTag::ListTag() {}

ListTag::ListTag(int id) : m_tagId(id) {}

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
