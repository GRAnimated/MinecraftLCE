#pragma once

#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include <unordered_map>

class BooleanProperty : public AbstractProperty<bool> {
public:
    static BooleanProperty* create(const std::wstring&);

    const std::vector<Boxed*>& getPossibleValues() const override;
    bool equals(const Property*) const override;
    int hashCode() const override;
    int getValueCount() const override;
    Boxed* getValueAtIndex(unsigned int) const override;
    unsigned int getIndexForValue(Boxed*) const override;
    bool getUnboxedValue(const std::wstring&) const override;
    std::wstring getName(const bool&) const override;
    ~BooleanProperty();

    std::vector<Boxed*> m_allowedValues;
    std::unordered_map<std::wstring, bool> m_values;
};
