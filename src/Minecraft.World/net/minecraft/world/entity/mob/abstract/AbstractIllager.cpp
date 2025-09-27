#include "AbstractIllager.h"
#include "net/minecraft/network/syncher/EntityDataSerializers.h"

void AbstractIllager::staticCtor() {
    sAccessor = SynchedEntityData::defineId(eAbstractIllager, eMonster,
                                            EntityDataSerializers::sBYTE_EntityDataSerializer);
}
