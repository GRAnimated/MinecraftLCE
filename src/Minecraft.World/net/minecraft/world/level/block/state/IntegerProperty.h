#pragma once

#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"

class IntegerProperty : public AbstractProperty<int> {
public:
    static IntegerProperty* create(const std::wstring&, int, int);

    const std::vector<Boxed*>& getPossibleValues() const override;
    bool equals(const Property*) const override;
    int hashCode() const override;
    int getValueCount() const override;
    Boxed* getValueAtIndex(unsigned int) const override;
    unsigned int getIndexForValue(Boxed*) const override;
    std::wstring getName(const int&) const override;
    int getUnboxedValue(const std::wstring&) const override;
    ~IntegerProperty();
};
