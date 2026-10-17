#include "net/minecraft/world/effect/MobEffect.h"

#include "net/minecraft/world/entity/ai/attributes/AttributeInstance.h"
#include "net/minecraft/world/entity/ai/attributes/BaseAttributeMap.h"

MobEffect* MobEffect::addAttributeModifier(Attribute* attribute, eMODIFIER_ID id, double amount,
                                           int operation) {
    AttributeModifier* modifier = new AttributeModifier(static_cast<eATTRIBUTE_ID>(id), amount, operation);
    m_attributeModifiers.insert(std::make_pair(attribute, modifier));
    return this;
}

void MobEffect::removeAttributeModifiers(const std::shared_ptr<LivingEntity>&, BaseAttributeMap* attributes,
                                         int) {
    for (const auto& entry : m_attributeModifiers) {
        AttributeInstance* instance = attributes->getInstance(entry.first);
        if (instance != nullptr)
            instance->removeModifier(entry.second);
    }
}

void MobEffect::addAttributeModifiers(const std::shared_ptr<LivingEntity>&, BaseAttributeMap* attributes,
                                      int amplifier) {
    for (const auto& entry : m_attributeModifiers) {
        AttributeInstance* instance = attributes->getInstance(entry.first);
        if (instance != nullptr) {
            AttributeModifier* modifier = entry.second;
            instance->removeModifier(modifier);
            instance->addModifier(new AttributeModifier(
                modifier->getId(), getAttributeModifierValue(amplifier, modifier), modifier->getOperation()));
        }
    }
}
