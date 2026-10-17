#include "net/minecraft/world/level/block/Rotation.h"

Rotation::Rotation(const std::wstring& name, eTYPE type) {
    m_name = name;
    m_type = type;
}

Rotation::eTYPE Rotation::getType() const {
    return m_type;
}
