#pragma once

class BlockState;

template <typename T>
class IdMap {
public:
    virtual int getId(T object);
    virtual T byId(int id);
};
