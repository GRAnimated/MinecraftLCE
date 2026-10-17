#include "com/mojang/nbt/ListTag.h"

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
