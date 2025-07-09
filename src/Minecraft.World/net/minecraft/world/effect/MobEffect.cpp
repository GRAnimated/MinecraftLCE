#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/effect/MobEffects.h"

// MobEffect::MobEffect(bool harmful, eMinecraftColour color) {}
// void MobEffect::applyEffectTick(std::shared_ptr<LivingEntity>, int) {}
// void MobEffect::applyInstantenousEffect(std::shared_ptr<Entity>, std::shared_ptr<LivingEntity>, int, double) {}
// void MobEffect::addAttributeModifier(Attribute*, eMODIFIER_ID, double, int) {}
// void MobEffect::getAttributeModifiers() {}
// void MobEffect::removeAttributeModifiers(std::shared_ptr<LivingEntity>, BaseAttributeMap*, int) {}
// void MobEffect::addAttributeModifiers(std::shared_ptr<LivingEntity>, BaseAttributeMap*, int) {}
// void MobEffect::getAttributeModifierValue(int, AttributeModifier*) {}

bool MobEffect::isDurationEffectTick(int tick, int amplifier) {
  int interval;

  if (this == MobEffects::REGENERATION) {
    interval = 50 >> amplifier;
    if (interval < 1) {
      return true;
    }
    return (tick % interval) == 0;
  }

  if (this == MobEffects::POISON) {
    interval = 25 >> amplifier;
    if (interval < 1) {
      return true;
    }
    return (tick % interval) == 0;
  }

  if (this == MobEffects::WITHER) {
    interval = 40 >> amplifier;
    if (interval < 1) {
      return true;
    }
    return (tick % interval) == 0;
  }

  return this == MobEffects::HUNGER;
}

void MobEffect::setIcon(EMobEffectIcon icon) {
  mIcon = icon;
}

void MobEffect::setDurationModifier(double durationModifier) {
  mDurationModifier = durationModifier;
}

void MobEffect::setDescriptionId(int descriptionId) {
  mDescriptionId = descriptionId;
}

void MobEffect::setBeneficial() {
  mBeneficial = true;
}

bool MobEffect::isInstantenous() {
  return false;
}

bool MobEffect::isHarmful() {
  return mHarmful;
}

bool MobEffect::isBeneficial() const {
  return mBeneficial;
}

bool MobEffect::hasIcon() {
  return mIcon != MobEffect::EMobEffectIcon::Unknown;
}

MobEffect::EMobEffectIcon MobEffect::getIcon() {
  return mIcon;
}

double MobEffect::getDurationModifier() const {
  return mDurationModifier;
}

int MobEffect::getDescriptionId() {
  return mDescriptionId;
}

eMinecraftColour MobEffect::getColor() const {
  return mColor;
}
