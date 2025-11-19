#include "net/minecraft/client/particle/ParticleType.h"

#include "net/minecraft/world/level/LevelListener.h"

ParticleType ParticleType::EXPLODE = ParticleType("explode", ePARTICLE_TYPE_Explode, true, 0);
ParticleType ParticleType::SPIT = ParticleType("spit", ePARTICLE_TYPE_Spit, true, 0);
ParticleType ParticleType::BUBBLE = ParticleType("bubble", ePARTICLE_TYPE_Bubble, false, 0);
ParticleType ParticleType::SPLASH = ParticleType("splash", ePARTICLE_TYPE_Splash, false, 0);
ParticleType ParticleType::WAKE = ParticleType("wake", ePARTICLE_TYPE_Wake, false, 0);
ParticleType ParticleType::DROPLET = ParticleType("droplet", ePARTICLE_TYPE_Droplet, false, 0);
ParticleType ParticleType::SUSPENDED = ParticleType("suspended", ePARTICLE_TYPE_Suspended, false, 0);
ParticleType ParticleType::DEPTHSUSPEND = ParticleType("depthsuspend", ePARTICLE_TYPE_Depthsuspend, false, 0);
ParticleType ParticleType::CRIT = ParticleType("crit", ePARTICLE_TYPE_Crit, false, 0);
ParticleType ParticleType::MAGIC_CRIT = ParticleType("magicCrit", ePARTICLE_TYPE_MagicCrit, false, 0);
ParticleType ParticleType::SMOKE = ParticleType("smoke", ePARTICLE_TYPE_Smoke, false, 0);
ParticleType ParticleType::LARGE_SMOKE = ParticleType("largesmoke", ePARTICLE_TYPE_LargeSmoke, false, 0);
ParticleType ParticleType::SPELL = ParticleType("spell", ePARTICLE_TYPE_Spell, false, 0);
ParticleType ParticleType::INSTANT_SPELL
    = ParticleType("instantSpell", ePARTICLE_TYPE_InstantSpell, false, 0);

ParticleType::ParticleType(const std::string name, ePARTICLE_TYPE id, bool unk1, int unk2) {
    mName = name;
    mId = id;
    mUnk1 = unk1;
    mUnk2 = unk2;
}

ePARTICLE_TYPE ParticleType::getId() const {
    return mId;
}
