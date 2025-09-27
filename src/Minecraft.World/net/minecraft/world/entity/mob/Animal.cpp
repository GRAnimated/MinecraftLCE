#include "net/minecraft/network/syncher/EntityDataSerializers.h"
#include "net/minecraft/world/entity/mob/Animal.h"

void Animal::staticCtor() {
    sAccessor
        = SynchedEntityData::defineId(eAnimal, eAgableMob, EntityDataSerializers::sINT_EntityDataSerializer);
}
