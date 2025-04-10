#pragma once

class BlockState;

template <typename T>
class IdMap {
public:
    virtual int getId(const BlockState* state);
    virtual T byId(int id);
};
