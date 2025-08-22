#pragma once

#include <unordered_map>
#include <vector>

// idk if this is STL function, but I highly doubt as WiiU has this inlined
template <typename V, typename K>
void putMapValuesIntoVector(std::vector<V>* out, std::unordered_map<K, V>* in) {
    for (auto& pair : *in) {
        out->push_back(pair.second);
    }
}

std::wstring formatwstr(const wchar_t* format, ...);  // move somewhere else
