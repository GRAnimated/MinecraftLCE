#pragma once

#include "Minecraft.World/level/block/state/AbstractProperty.h"

class IntegerProperty : public AbstractProperty<int> {
public:
    static IntegerProperty* create(const std::wstring&, int, int);

    int getPossibleValues() const override;
    bool equals(Property const*) const override;
    int hashCode() const override;
    int getValueCount() const override;
    int getValueAtIndex(unsigned int) const override;
    int getIndexForValue(Boxed*) const override;
    std::wstring getName(const int&) const override;
    int getUnboxedValue(const std::wstring&) const override;
    ~IntegerProperty();
};
