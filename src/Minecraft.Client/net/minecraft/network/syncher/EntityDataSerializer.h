#pragma once

#include "net/minecraft/network/syncher/EntityDataAccessor.h"
#include "net/minecraft/network/syncher/EntityDataSerializerEnum.h"
#include <unordered_map>

class DataInputStream;
class DataOutputStream;
class EntityDataAccessor_Base;
class ItemInstance;
class BlockState;
class Rotations;
class BlockPos;
class Direction;
class CompoundTag;

template <typename T>
class EntityDataSerializer {
public:
    EntityDataSerializer(EntityDataSerializerEnum::EEntityDataSerializer type) : m_type(type) {}
    virtual void write(DataOutputStream*, T) const = 0;
    virtual T read(DataInputStream*) const = 0;
    virtual EntityDataAccessor_Base* createAccessor(int) = 0;
    virtual T copy(T) const = 0;
    virtual EntityDataAccessor_Base* getOrCreateStoredAccessor(int);

    std::unordered_map<int, EntityDataAccessor<T>*> m_accessors;
    EntityDataSerializerEnum::EEntityDataSerializer m_type;
};
