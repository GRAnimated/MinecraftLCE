#pragma once

template <typename T>
class EntityDataSerializer;

class EntityDataAccessor_Base {};

template <typename T>
class EntityDataAccessor : public EntityDataAccessor_Base {
public:
    EntityDataAccessor(int id, EntityDataSerializer<T>* serializer);

    void* padding[2];
};
