#include "net/minecraft/network/syncher/SynchedEntityData.h"

int SynchedEntityData::defineIdInternal(eINSTANCEOF a1, eINSTANCEOF a2) {
    auto it = SynchedEntityData::sIdMap.find(a1);
    if (it != SynchedEntityData::sIdMap.end()) {
        return it->second + 1;
    }

    it = SynchedEntityData::sIdMap.find(a2);
    if (it != SynchedEntityData::sIdMap.end()) {
        return it->second + 1;
    }

    return 0;
}
