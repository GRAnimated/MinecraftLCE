#pragma once

#include "net/minecraft/world/entity/ai/attributes/AttributeInstance.h"
#include <unordered_map>

class BaseAttributeMap;

class ModifiableAttributeInstance : public AttributeInstance {
public:
    ModifiableAttributeInstance(BaseAttributeMap*, Attribute*);
    ~ModifiableAttributeInstance() override;
    Attribute* getAttribute() override;
    double getBaseValue() override;
    void setBaseValue(double) override;
    double getValue() override;
    std::unordered_set<AttributeModifier*>* getModifiers(int) override;
    void getModifiers(std::unordered_set<AttributeModifier*>&) override;
    bool hasModifier(AttributeModifier*) override;
    AttributeModifier* getModifier(eMODIFIER_ID) override;
    void addModifiers(std::unordered_set<AttributeModifier*>*) override;
    void addModifier(AttributeModifier*) override;
    void removeModifier(AttributeModifier*) override;
    void removeModifier(eMODIFIER_ID) override;
    void removeModifiers() override;
    void setDirty();

private:
    double calculateValue();
    void getAppliedModifiers(int, std::unordered_set<AttributeModifier*>&);
    BaseAttributeMap* m_parent;
    Attribute* m_attribute;
    std::unordered_set<AttributeModifier*> m_modifiers[3];
    std::unordered_map<eMODIFIER_ID, AttributeModifier*> m_modifiersById;
    double m_baseValue;
    bool m_dirty;
    double m_cachedValue;
};
