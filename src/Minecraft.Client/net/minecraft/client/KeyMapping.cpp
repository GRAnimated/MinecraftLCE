#include "net/minecraft/client/KeyMapping.h"

KeyMapping::KeyMapping(const std::wstring& name, int key) {
    mKeyDescription = name;
    mKeyCode = key;
}
