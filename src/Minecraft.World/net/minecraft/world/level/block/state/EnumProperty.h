#pragma once

#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include <string>
#include <typeinfo>

template <typename T>
class EnumProperty : public AbstractProperty<T> {
public:
    template <int N>
    static EnumProperty<T>* create(const std::wstring& name, const std::type_info&, T (&values)[N],
                                   Predicates<T>*);

    // int getPossibleValues() const override; // On WiiU it seems that EnumProperty overrides this but on
    // Switch it doesn't for whatever reason :skull:
    bool equals(const Property*) const override;
    int hashCode() const override;
    int getValueCount() const override;
    Boxed* getValueAtIndex(unsigned int) const override;
    unsigned int getIndexForValue(Boxed*) const override;
    std::wstring getName(const T&) const override;
    T getUnboxedValue(const std::wstring&) const override;
    virtual ~EnumProperty();
};
