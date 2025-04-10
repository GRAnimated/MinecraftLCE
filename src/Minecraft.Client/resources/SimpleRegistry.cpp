/*#include "SimpleRegistry.h"
#include "Minecraft.World/Random.h"

template <typename Key, typename Value, typename Hash, typename KeyEqual>
Value SimpleRegistry<Key, Value, Hash, KeyEqual>::get(const Key& key){
    return this->mMap.at(key);
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void SimpleRegistry<Key, Value, Hash, KeyEqual>::registerKey(const Key& key, const Value& value){
    mMap[key] = value;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
std::unordered_map<Key, Value> SimpleRegistry<Key, Value, Hash, KeyEqual>::keySet(){
    return this->mMap;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
Value SimpleRegistry<Key, Value, Hash, KeyEqual>::getRandom(Random* random) {
    if (mMap.empty()) {
        return nullptr;
    }

    // Assuming Random is some custom random number generator class with an appropriate method
    auto it = mMap.begin();
    std::advance(it, random->nextInt(mMap.size())); // 'nextInt' should return a random index in the
range

    return it->second;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
bool SimpleRegistry<Key, Value, Hash, KeyEqual>::containsKey(const Key& key) {
    return mMap.find(key) != mMap.end();
}*/