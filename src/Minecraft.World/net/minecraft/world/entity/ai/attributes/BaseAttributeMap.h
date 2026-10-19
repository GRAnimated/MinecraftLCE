#pragma once

#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"
#include <vector>

class Attribute;
class AttributeInstance;

/** Recovered virtual prefix for pointer dispatch; the object's storage is still unreconstructed.
 */
class BaseAttributeMap {
public:
    virtual ~BaseAttributeMap();
    virtual AttributeInstance* getInstance(Attribute*);
    virtual AttributeInstance* getInstance(eATTRIBUTE_ID);
    virtual AttributeInstance* registerAttribute(Attribute*);
    virtual AttributeInstance* createAttributeInstance(Attribute*) = 0;
    virtual void getAttributes(std::vector<AttributeInstance*>&);
    virtual void onAttributeModified(AttributeInstance*);
};
