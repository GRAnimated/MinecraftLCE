#include "net/minecraft/client/particle/ParticleType.h"

#include "net/minecraft/client/particle/ParticleTypes.h"
#include "net/minecraft/world/level/LevelListener.h"

ParticleType* ParticleTypes::EXPLODE = new ParticleType("explode", ePARTICLE_TYPE_Explode, true, 0);
ParticleType* ParticleTypes::SPIT = new ParticleType("spit", ePARTICLE_TYPE_Spit, true, 0);
ParticleType* ParticleTypes::BUBBLE = new ParticleType("bubble", ePARTICLE_TYPE_Bubble, false, 0);
ParticleType* ParticleTypes::SPLASH = new ParticleType("splash", ePARTICLE_TYPE_Splash, false, 0);
ParticleType* ParticleTypes::WAKE = new ParticleType("wake", ePARTICLE_TYPE_Wake, false, 0);
ParticleType* ParticleTypes::DROPLET = new ParticleType("droplet", ePARTICLE_TYPE_Droplet, false, 0);
ParticleType* ParticleTypes::SUSPENDED = new ParticleType("suspended", ePARTICLE_TYPE_Suspended, false, 0);
ParticleType* ParticleTypes::DEPTHSUSPEND
    = new ParticleType("depthsuspend", ePARTICLE_TYPE_Depthsuspend, false, 0);
ParticleType* ParticleTypes::CRIT = new ParticleType("crit", ePARTICLE_TYPE_Crit, false, 0);
ParticleType* ParticleTypes::MAGIC_CRIT = new ParticleType("magicCrit", ePARTICLE_TYPE_MagicCrit, false, 0);
ParticleType* ParticleTypes::SMOKE = new ParticleType("smoke", ePARTICLE_TYPE_Smoke, false, 0);
ParticleType* ParticleTypes::LARGE_SMOKE
    = new ParticleType("largesmoke", ePARTICLE_TYPE_LargeSmoke, false, 0);
ParticleType* ParticleTypes::SPELL = new ParticleType("spell", ePARTICLE_TYPE_Spell, false, 0);
ParticleType* ParticleTypes::INSTANT_SPELL
    = new ParticleType("instantSpell", ePARTICLE_TYPE_InstantSpell, false, 0);

ParticleType::ParticleType(const std::string name, ePARTICLE_TYPE id, bool unk1, int unk2) {
    this->mName = name;
    this->mId = id;
    this->mUnk1 = unk1;
    this->mUnk2 = unk2;
}

ePARTICLE_TYPE ParticleType::getId() const {
    return this->mId;
}
