#include "net/minecraft/world/entity/mob/Animal.h"

#include "net/minecraft/network/syncher/EntityDataSerializers.h"

void Animal::staticCtor() {
    sAccessor
        = SynchedEntityData::defineId(eAnimal, eAgableMob, EntityDataSerializers::sINT_EntityDataSerializer);
}