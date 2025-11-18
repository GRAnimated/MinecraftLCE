#include "net/minecraft/world/entity/mob/abstract/AbstractChestedHorse.h"
#include "net/minecraft/network/syncher/EntityDataSerializers.h"
#include "net/minecraft/network/syncher/SynchedEntityData.h"
#include "net/minecraft/world/eINSTANCEOF.h"

void AbstractChestedHorse::staticCtor() {
    sAccessor = SynchedEntityData::defineId(eAbstractChestedHorse, eAbstractHorse,
                                            EntityDataSerializers::sBOOLEAN_EntityDataSerializer);
}
