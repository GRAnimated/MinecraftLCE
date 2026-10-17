#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"

const std::vector<const Property*>& BlockStateDefinition::getProperties() const {
    return m_properties;
}
