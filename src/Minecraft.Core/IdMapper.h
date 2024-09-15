#pragma once

#include "Minecraft.Core/IdMap.h"

template <typename T>
class IdMapper : public IdMap<T> {
public:
    int getId(const BlockState* state) override;
    T byId(int id) override;
};

// TODO: Unknown location for this variable
extern IdMapper<const BlockState*>* sBlockStateMapper;
