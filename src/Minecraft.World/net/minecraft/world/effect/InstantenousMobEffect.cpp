#include "net/minecraft/world/effect/MobEffectTypes.h"

// name guessed
InstantenousMobEffect::InstantenousMobEffect(bool harmful, eMinecraftColour color)
    : MobEffect(harmful, color) {}

// name guessed
bool InstantenousMobEffect::isInstantenous() {
    return true;
}

// name guessed
bool InstantenousMobEffect::isDurationEffectTick(int tick, int) {
    return tick > 0;
}
