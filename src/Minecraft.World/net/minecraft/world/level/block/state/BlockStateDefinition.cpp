#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include <algorithm>

Block* BlockStateDefinition::getBlock() const {
    return m_block;
}

const arrayWithLength<const BlockState*>* BlockStateDefinition::getPossibleBlockStates() const {
    return &m_states;
}

const BlockState* BlockStateDefinition::any() {
    return m_states[0];
}

// name guessed
bool BlockStateDefinition::hasProperty(const Property* property) const {
    return std::find(m_properties.begin(), m_properties.end(), property) != m_properties.end();
}

// name guessed
// NON_MATCHING | score: 840 (lower is better)
Boxed* BlockStateDefinition::getPropertyValue(const Property* property, unsigned short state) const {
    unsigned int index = 0;
    for (auto it = m_properties.begin(); it != m_properties.end(); ++it, ++index) {
        if (*it == property) {
            unsigned int valueIndex = m_propertyBitMasks[index] & (state >> m_propertyBitOffsets[index]);
            return property->getValueAtIndex(valueIndex);
        }
    }
    return nullptr;
}

// name guessed
const BlockState* BlockStateDefinition::getNeighbour(const Property* property, Boxed* value,
                                                     unsigned short state) const {
    unsigned int index = 0;
    unsigned short valueIndex = 0;
    for (auto it = m_properties.begin(); it != m_properties.end(); ++it, ++index) {
        if (*it == property) {
            valueIndex = property->getIndexForValue(value);
            break;
        }
    }
    unsigned short mask = m_propertyBitMasks[index];
    unsigned char shift = m_propertyBitOffsets[index];
    unsigned int neighbour = (state & ~(mask << shift)) | ((valueIndex & mask) << shift);
    return m_states[neighbour];
}

// name guessed
const std::vector<const Property*>& BlockStateDefinition::getProperties() const {
    return m_properties;
}
