#include "net/minecraft/world/level/block/state/BlockStatePredicate.h"

#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include <algorithm>

BlockStatePredicate::BlockStatePredicate(BlockStateDefinition* definition) : m_definition(definition) {}

BlockStatePredicate::~BlockStatePredicate() = default;

BlockStatePredicate* BlockStatePredicate::forBlock(Block* block) {
    return new BlockStatePredicate(block->getBlockStateDefinition());
}

bool BlockStatePredicate::apply(const BlockState* state) const {
    if (!state || state->getBlock() != m_definition->getBlock())
        return false;

    if (!m_predicates.empty()) {
        for (const auto& entry : m_predicates) {
            Boxed* value = state->getBoxedValue(entry.first);
            if (!entry.second->apply(value))
                return false;
        }
    }
    return true;
}

BlockStatePredicate* BlockStatePredicate::where(Property* property, const Predicate<Boxed*>* predicate) {
    const auto& properties = m_definition->getProperties();
    // The original performs this scan but still registers an absent property.
    std::find(properties.begin(), properties.end(), property);
    m_predicates[property] = predicate;
    return this;
}
