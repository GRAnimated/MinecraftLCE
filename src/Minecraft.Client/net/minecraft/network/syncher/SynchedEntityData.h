#pragma once

#include "net/minecraft/network/syncher/EntityDataAccessor.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include <unordered_map>

template <typename T>
class EntityDataAccessor;

template <typename T>
class EntityDataSerializer;

class Entity;

class SynchedEntityData {
public:
    static std::unordered_map<eINSTANCEOF, int> sIdMap;

    SynchedEntityData(Entity*);

    /// @return The index of the newly added IDs
    static int defineIdInternal(eINSTANCEOF, eINSTANCEOF);

    template <typename T>
    void createDateItem(const EntityDataAccessor<T>*, T);  // date

    template <typename T>
    static EntityDataAccessor<T>* defineId(eINSTANCEOF a1, eINSTANCEOF a2, EntityDataSerializer<T>* s) {
        int i = defineIdInternal(a1, a2);
        sIdMap[a1] = i;

        if (s)
            return reinterpret_cast<EntityDataAccessor<T>*>(s->createAccessor(i));
        else
            return nullptr;
    }

    static void defineId(eINSTANCEOF a1, eINSTANCEOF a2) {
        // defineId<bool>(a1, a2, nullptr);
    }

    void* padding[0x101];
};
