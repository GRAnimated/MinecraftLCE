#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"

void AttributeModifier::_init(int id, std::wstring name, double amount, int operation) {
    m_amount = amount;
    m_operation = operation;
    m_name = name;
    m_id = static_cast<eATTRIBUTE_ID>(id);
    m_serialize = true;
}

AttributeModifier::AttributeModifier(double amount, int operation) {
    _init(0, m_name, amount, operation);
}

AttributeModifier::AttributeModifier(eATTRIBUTE_ID id, double amount, int operation) {
    _init(id, m_name, amount, operation);
}

AttributeModifier::AttributeModifier(eATTRIBUTE_ID id, double amount, int operation, bool serialize) {
    _init(id, m_name, amount, operation);
    m_serialize = serialize;
}

eATTRIBUTE_ID AttributeModifier::getId() {
    return m_id;
}

bool AttributeModifier::isSerializable() {
    return m_serialize;
}

void AttributeModifier::setSerialize(bool serialize) {
    m_serialize = serialize;
}

bool AttributeModifier::equals(AttributeModifier* other) {
    if (this == other)
        return true;
    if (other != nullptr)
        return m_id == other->m_id;
    return false;
}
