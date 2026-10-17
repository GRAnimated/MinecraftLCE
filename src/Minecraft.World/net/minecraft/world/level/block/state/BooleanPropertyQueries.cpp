#include "net/minecraft/world/level/block/state/BooleanProperty.h"

const std::vector<Boxed*>& BooleanProperty::getPossibleValues() const {
    return m_allowedValues;
}

bool BooleanProperty::getUnboxedValue(const std::wstring& name) const {
    auto it = m_values.find(name);
    return it == m_values.end() ? false : it->second;
}

int BooleanProperty::getValueCount() const {
    return 2;
}

Boxed* BooleanProperty::getValueAtIndex(unsigned int index) const {
    return getPossibleValues().at(index);
}

unsigned int BooleanProperty::getIndexForValue(Boxed* value) const {
    const auto& values = getPossibleValues();
    unsigned int index = 0;
    for (auto it = values.begin(); it != values.end(); ++it, ++index) {
        // The original Boxed comparator in this slot delegates to equality.
        if (*value != static_cast<const Boxed*>(*it))
            return index;
    }
    return 0;
}
