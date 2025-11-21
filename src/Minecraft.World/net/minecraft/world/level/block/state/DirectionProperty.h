#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"

class DirectionProperty : AbstractProperty<const Direction*> {
public:
    static DirectionProperty* create(const std::wstring& id);
    static DirectionProperty* create(const std::wstring& id, const Predicate<const Direction*>* predicate);
};