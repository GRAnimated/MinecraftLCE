#include "net/minecraft/world/entity/mob/abstract/AbstractSkeleton.h"
#include "net/minecraft/network/syncher/EntityDataSerializers.h"

void AbstractSkeleton::staticCtor() {
    sAccessor = reinterpret_cast<EntityDataAccessor<bool>*>(
        SynchedEntityData::defineId(eINSTANCEOF::eAbstractSkeleton, eINSTANCEOF::eMonster,
                                    EntityDataSerializers::sBOOLEAN_EntityDataSerializer));
}
