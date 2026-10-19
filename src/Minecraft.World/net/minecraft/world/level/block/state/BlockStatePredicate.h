#pragma once

#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include "types.h"
#include <unordered_map>

class Block;
class BlockState;
class BlockStateDefinition;

/** Property predicates are borrowed; destroying this object releases only the map storage.
 */
class BlockStatePredicate : public Predicate<const BlockState*> {
public:
    BlockStatePredicate(BlockStateDefinition*);
    ~BlockStatePredicate() override;

    static BlockStatePredicate* forBlock(Block*);
    bool apply(const BlockState*) const override;
    BlockStatePredicate* where(Property*, const Predicate<Boxed*>*);

    template <typename T>
    class PredicateConversion : public Predicate<Boxed*> {
    public:
        PredicateConversion(const Predicate<T>* predicate) : m_predicate(predicate) {}

        bool apply(Boxed* value) const override {
            return m_predicate->apply(*const_cast<TypedBoxed<T>*>(value->tryGetType<T>())->getValue());
        }

    private:
        const Predicate<T>* m_predicate;
    };

    template <typename T>
    BlockStatePredicate* where(Property* property, Predicate<T>* predicate) {
        const Predicate<Boxed*>* conversion = new PredicateConversion<T>(predicate);
        return where(property, conversion);
    }

private:
    BlockStateDefinition* m_definition;
    std::unordered_map<Property*, const Predicate<Boxed*>*> m_predicates;
};

ASSERT_SIZEOF(BlockStatePredicate, 0x38);
