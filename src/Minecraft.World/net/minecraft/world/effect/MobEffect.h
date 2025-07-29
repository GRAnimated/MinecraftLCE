#pragma once

#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include "net/minecraft/world/level/material/MaterialColor.h"

class Attribute;
class AttributeModifier;
class BaseAttributeMap;

enum class eMODIFIER_ID { Unknown = 0 };

class MobEffect {
public:
    enum EMobEffectIcon {
        Unknown = 0,
        Blindness = 1,
        FireResistance = 2,
        Haste = 3,
        Hunger = 4,
        Invisibility = 5,
        JumpBoost = 6,
        MiningFatigue = 7,
        Nausea = 8,
        NightVision = 9,
        Poison = 10,
        Regeneration = 11,
        Resistance = 12,
        Slowness = 13,
        Speed = 14,
        Strength = 15,
        WaterBreathing = 16,
        Weakness = 17,
        Wither = 18,
        HealthBoost = 19,
        Absorption = 20,
        Glowing = 21,
        Levitation = 22,
        Luck = 23,
        Unluck = 24
    };

    virtual void applyEffectTick(const std::shared_ptr<LivingEntity>&, int);
    virtual void applyInstantenousEffect(std::shared_ptr<Entity>, std::shared_ptr<LivingEntity>, int, double);
    virtual bool isDurationEffectTick(int, int);
    virtual bool isInstantenous();
    virtual double getDurationModifier() const;
    virtual void setBeneficial();
    virtual bool isBeneficial() const;
    virtual eMinecraftColour getColor() const;
    virtual void addAttributeModifier(Attribute*, eMODIFIER_ID, double, int);
    virtual void getAttributeModifiers();
    virtual void removeAttributeModifiers(std::shared_ptr<LivingEntity>, BaseAttributeMap*, int);
    virtual void addAttributeModifiers(std::shared_ptr<LivingEntity>, BaseAttributeMap*, int);
    virtual void getAttributeModifierValue(int, AttributeModifier*);
    virtual ~MobEffect();

    static int getId(MobEffect*);
    static MobEffect* byId(int id);

    MobEffect(bool harmful, eMinecraftColour color);
    void setIcon(EMobEffectIcon icon);
    void setDurationModifier(double durationModifier);
    void setDescriptionId(int descriptionId);
    bool isHarmful();
    bool hasIcon();
    EMobEffectIcon getIcon();
    int getDescriptionId();

    char unknown[40];
    int mDescriptionId;
    EMobEffectIcon mIcon;
    bool mHarmful;
    double mDurationModifier;
    bool mBeneficial;
    eMinecraftColour mColor;
};
