#pragma once

#include "Minecraft.Client/resources/IdMap.h"

class BlockState;

template <typename T>
class IdMapper : public IdMap<T> {
public:
    void addMapping(T type, int id);
    int getId(T object) override;
    T byId(int id) override;

private:
    void* filler[7];
};

// TODO: Unknown location for this variable
extern IdMapper<const BlockState*>* sBlockStateMapper;
