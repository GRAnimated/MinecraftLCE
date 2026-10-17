#include "net/minecraft/world/entity/ai/attributes/Attribute.h"

#include "net/minecraft/util/Mth.h"

Attribute::Attribute() = default;

BaseAttribute::BaseAttribute(Attribute* parent, eATTRIBUTE_ID id, double defaultValue)
    : m_parent(parent), m_id(id), m_defaultValue(defaultValue), m_syncable(false) {}

int BaseAttribute::getId() {
    return m_id;
}

double BaseAttribute::getDefaultValue() {
    return m_defaultValue;
}

bool BaseAttribute::isClientSyncable() {
    return m_syncable;
}

Attribute* BaseAttribute::getParentAttribute() {
    return m_parent;
}

void BaseAttribute::setSyncable(bool syncable) {
    m_syncable = syncable;
}

RangedAttribute::RangedAttribute(Attribute* parent, eATTRIBUTE_ID id, double defaultValue, double minValue,
                                 double maxValue)
    : BaseAttribute(parent, id, defaultValue), m_minValue(minValue), m_maxValue(maxValue) {}

double RangedAttribute::sanitizeValue(double value) {
    return Mth::clamp(value, m_minValue, m_maxValue);
}
