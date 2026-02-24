#pragma once

#include <unordered_map>
#include <vector>

class Block;

template <typename T>
class IdMap {
public:
    virtual int getId(T object);
    virtual T byId(int id);

    std::unordered_map<T, int> m_ap;
    std::vector<T> m_vector;
};
