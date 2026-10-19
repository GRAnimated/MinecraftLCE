#include "net/minecraft/world/entity/ai/attributes/Attribute.h"

#include "net/minecraft/util/Mth.h"

// name guessed
Attribute::Attribute() = default;

// name guessed
BaseAttribute::BaseAttribute(Attribute* parent, eATTRIBUTE_ID id, double defaultValue)
    : m_parent(parent), m_id(id), m_defaultValue(defaultValue), m_syncable(false) {}

// name guessed
int BaseAttribute::getId() {
    return m_id;
}

// name guessed
double BaseAttribute::getDefaultValue() {
    return m_defaultValue;
}

// name guessed
bool BaseAttribute::isClientSyncable() {
    return m_syncable;
}

// name guessed
Attribute* BaseAttribute::getParentAttribute() {
    return m_parent;
}

// name guessed
void BaseAttribute::setSyncable(bool syncable) {
    m_syncable = syncable;
}

RangedAttribute::RangedAttribute(Attribute* parent, eATTRIBUTE_ID id, double defaultValue, double minValue,
                                 double maxValue)
    : BaseAttribute(parent, id, defaultValue), m_minValue(minValue), m_maxValue(maxValue) {}

// name guessed
double RangedAttribute::sanitizeValue(double value) {
    return Mth::clamp(value, m_minValue, m_maxValue);
}
