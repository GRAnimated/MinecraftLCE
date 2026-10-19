#pragma once

#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"

class Attribute {
public:
    Attribute();
    virtual ~Attribute();
    virtual int getId() = 0;
    virtual double sanitizeValue(double) = 0;
    virtual double getDefaultValue() = 0;
    virtual bool isClientSyncable() = 0;
    virtual Attribute* getParentAttribute() = 0;
    virtual void setSyncable(bool) = 0;
};

class BaseAttribute : public Attribute {
public:
    BaseAttribute(Attribute*, eATTRIBUTE_ID, double);
    ~BaseAttribute() override;
    int getId() override;
    double getDefaultValue() override;
    bool isClientSyncable() override;
    Attribute* getParentAttribute() override;
    void setSyncable(bool) override;

private:
    Attribute* m_parent;
    eATTRIBUTE_ID m_id;
    double m_defaultValue;
    bool m_syncable;
};

class RangedAttribute : public BaseAttribute {
public:
    static RangedAttribute* ATTACK_DAMAGE;
    static RangedAttribute* ATTACK_SPEED;

    RangedAttribute(Attribute*, eATTRIBUTE_ID, double, double, double);
    ~RangedAttribute() override;

    double sanitizeValue(double) override;

private:
    double m_minValue;
    double m_maxValue;
};
