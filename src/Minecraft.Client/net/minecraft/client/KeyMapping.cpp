#include "net/minecraft/client/KeyMapping.h"
#include <string>

KeyMapping::KeyMapping(const std::wstring& name, int key) {
    mKeyDescription = name;
    mKeyCode = key;
}
