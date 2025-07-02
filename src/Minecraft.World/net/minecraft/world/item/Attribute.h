#pragma once

#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"

class Attribute {
public:
    virtual ~Attribute();
    virtual int getId();
    virtual double sanitizeValue(double) = 0;
    virtual double getDefaultValue() = 0;
    virtual bool isClientSyncable() = 0;
    virtual Attribute* getParentAttribute() = 0;
    virtual void setSyncable(bool) = 0;
};

class BaseAttribute : public Attribute {
public:
    double getDefaultValue() override;
    bool isClientSyncable() override;
    Attribute* getParentAttribute() override;
    void setSyncable(bool) override;
};

class RangedAttribute : public BaseAttribute {
public:
    static RangedAttribute* ATTACK_DAMAGE;
    static RangedAttribute* ATTACK_SPEED;

    RangedAttribute(Attribute*, eATTRIBUTE_ID, double, double, double);

    double sanitizeValue(double) override;
};