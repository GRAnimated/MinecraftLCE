#include "com/mojang/nbt/ListTag.h"
#include "com/mojang/nbt/NumericTag.h"

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
