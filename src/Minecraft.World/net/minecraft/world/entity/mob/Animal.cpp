#include "net/minecraft/world/entity/mob/FlyingAnimal.h"
#include "net/minecraft/network/syncher/EntityDataSerializers.h"

void Animal::staticCtor() {
    sAccessor
        = SynchedEntityData::defineId(eAnimal, eAgableMob, EntityDataSerializers::sINT_EntityDataSerializer);
}
