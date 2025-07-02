#include "Minecraft.Client/KeyMapping.h"

KeyMapping::KeyMapping(const std::wstring& name, int key) {
    mKeyDescription = name;
    mKeyCode = key;
}
