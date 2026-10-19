#pragma once

#include <unordered_set>

#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"

class Attribute;
enum class eMODIFIER_ID : unsigned int;

/** Slot order follows the Switch AttributeInstance and ModifiableAttributeInstance tables.
 */
class AttributeInstance {
public:
    AttributeInstance();
    virtual ~AttributeInstance();
    virtual Attribute* getAttribute() = 0;
    virtual double getBaseValue() = 0;
    virtual void setBaseValue(double) = 0;
    virtual double getValue() = 0;
    virtual std::unordered_set<AttributeModifier*>* getModifiers(int) = 0;
    virtual void getModifiers(std::unordered_set<AttributeModifier*>&) = 0;
    virtual bool hasModifier(AttributeModifier*) = 0;
    virtual AttributeModifier* getModifier(eMODIFIER_ID) = 0;
    virtual void addModifiers(std::unordered_set<AttributeModifier*>*) = 0;
    virtual void addModifier(AttributeModifier*) = 0;
    virtual void removeModifier(AttributeModifier*) = 0;
    virtual void removeModifier(eMODIFIER_ID) = 0;
    virtual void removeModifiers() = 0;
};
