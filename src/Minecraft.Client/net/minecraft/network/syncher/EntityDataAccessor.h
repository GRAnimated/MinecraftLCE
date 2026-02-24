#pragma once

template <typename T>
class EntityDataSerializer;

class EntityDataAccessor_Base {
public:
    bool is(const EntityDataAccessor_Base*) const;
};

template <typename T>
class EntityDataAccessor : public EntityDataAccessor_Base {
public:
    EntityDataAccessor(int id, EntityDataSerializer<T>* serializer);

    void* m_padding[2];
};
