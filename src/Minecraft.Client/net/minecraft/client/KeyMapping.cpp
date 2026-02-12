#include "net/minecraft/client/KeyMapping.h"
#include <string>

KeyMapping::KeyMapping(const std::wstring& name, int key) {
    m_keyDescription = name;
    m_keyCode = key;
}
