#pragma once

#include "Minecraft.World/level/block/state/AbstractProperty.h"

class IntegerProperty : public AbstractProperty<int> {
public:
    static IntegerProperty* create(std::wstring const&, int, int);

    int getPossibleValues() const override;
    bool equals(Property const*) const override;
    int hashCode() const override;
    int getValueCount() const override;
    int getValueAtIndex(unsigned int) const override;
    int getIndexForValue(Boxed*) const override;
    std::wstring getName(int const&) const override;
    int getUnboxedValue(std::wstring const&) const override;
    ~IntegerProperty();
};
