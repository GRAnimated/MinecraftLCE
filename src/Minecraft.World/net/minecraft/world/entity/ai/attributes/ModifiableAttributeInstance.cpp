#include "net/minecraft/world/entity/ai/attributes/ModifiableAttributeInstance.h"

#include "net/minecraft/world/entity/ai/attributes/Attribute.h"
#include "net/minecraft/world/entity/ai/attributes/BaseAttributeMap.h"

// name guessed
AttributeInstance::AttributeInstance() = default;

// name guessed
// NON_MATCHING | score: 1540 (lower is better)
ModifiableAttributeInstance::ModifiableAttributeInstance(BaseAttributeMap* parent, Attribute* attribute)
    : m_parent(parent), m_attribute(attribute), m_dirty(true), m_cachedValue(0) {
    m_baseValue = attribute->getDefaultValue();
}

// name guessed
Attribute* ModifiableAttributeInstance::getAttribute() {
    return m_attribute;
}

// name guessed
double ModifiableAttributeInstance::getBaseValue() {
    return m_baseValue;
}

// name guessed
void ModifiableAttributeInstance::setDirty() {
    m_dirty = true;
    m_parent->onAttributeModified(this);
}

// name guessed
void ModifiableAttributeInstance::setBaseValue(double value) {
    if (getBaseValue() == value)
        return;
    m_baseValue = value;
    setDirty();
}

// name guessed
std::unordered_set<AttributeModifier*>* ModifiableAttributeInstance::getModifiers(int operation) {
    return &m_modifiers[operation];
}

// name guessed
void ModifiableAttributeInstance::getModifiers(std::unordered_set<AttributeModifier*>& result) {
    for (int operation = 0; operation < 3; ++operation) {
        for (const auto& modifier : m_modifiers[operation])
            result.insert(modifier);
    }
}

// name guessed
AttributeModifier* ModifiableAttributeInstance::getModifier(eMODIFIER_ID id) {
    auto found = m_modifiersById.find(id);
    return found == m_modifiersById.end() ? nullptr : found->second;
}

// name guessed
bool ModifiableAttributeInstance::hasModifier(AttributeModifier* modifier) {
    return m_modifiersById.find(static_cast<eMODIFIER_ID>(modifier->getId())) != m_modifiersById.end();
}

// name guessed
// NON_MATCHING | score: 90 (lower is better)
void ModifiableAttributeInstance::addModifiers(std::unordered_set<AttributeModifier*>* modifiers) {
    for (AttributeModifier* modifier : *modifiers)
        addModifier(modifier);
}

// name guessed
double ModifiableAttributeInstance::getValue() {
    if (m_dirty) {
        m_cachedValue = calculateValue();
        m_dirty = false;
    }
    return m_cachedValue;
}

// name guessed
void ModifiableAttributeInstance::getAppliedModifiers(int operation,
                                                      std::unordered_set<AttributeModifier*>& result) {
    result.clear();
    for (const auto& modifier : *getModifiers(operation))
        result.insert(modifier);
    for (Attribute* parent = m_attribute->getParentAttribute(); parent != nullptr;
         parent = parent->getParentAttribute()) {
        AttributeInstance* instance = m_parent->getInstance(parent);
        if (instance != nullptr) {
            for (const auto& modifier : *instance->getModifiers(operation))
                result.insert(modifier);
        }
    }
}

// name guessed
double ModifiableAttributeInstance::calculateValue() {
    double base = getBaseValue();
    std::unordered_set<AttributeModifier*> modifiers;
    getAppliedModifiers(0, modifiers);
    for (AttributeModifier* modifier : modifiers)
        base += modifier->getAmount();
    getAppliedModifiers(1, modifiers);
    double value = base;
    for (AttributeModifier* modifier : modifiers)
        value += base * modifier->getAmount();
    getAppliedModifiers(2, modifiers);
    for (AttributeModifier* modifier : modifiers)
        value *= modifier->getAmount() + 1.0;
    return m_attribute->sanitizeValue(value);
}
