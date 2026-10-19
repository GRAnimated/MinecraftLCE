#include "net/minecraft/world/level/block/state/IntegerProperty.h"

// name guessed
const std::vector<Boxed*>& IntegerProperty::getPossibleValues() const {
    return m_allowedValues;
}

// name guessed
int IntegerProperty::getValueCount() const {
    return m_allowedValues.size();
}

// name guessed
Boxed* IntegerProperty::getValueAtIndex(unsigned int index) const {
    return m_allowedValues.at(index);
}

// name guessed
unsigned int IntegerProperty::getIndexForValue(Boxed* value) const {
    unsigned int index = 0;
    for (auto it = m_allowedValues.begin(); it != m_allowedValues.end(); ++it, ++index) {
        if (*value != static_cast<const Boxed*>(*it))
            return index;
    }
    return 0;
}
