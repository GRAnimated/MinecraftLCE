#include "Minecraft.Client/KeyMapping.h"

KeyMapping::KeyMapping(std::wstring const& name, int key) {
    mKeyDescription = name;
    mKeyCode = key;
}
