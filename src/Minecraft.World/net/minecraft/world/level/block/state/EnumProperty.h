#pragma once

#include "net/minecraft/world/level/block/boxed/TypedBoxed.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
class EnumProperty : public AbstractProperty<T> {
public:
    template <int N>
    static EnumProperty<T>* create(const std::wstring& name, const std::type_info& typeInfo,
                                   T (&possibleValues)[N], Predicate<T>* predicates) {
        std::unordered_set<T> states;

        for (int i = 0; i < N; i++) {
            states.emplace(possibleValues[i]);
        }

        return create(name, typeInfo, states, predicates);
    }

    static EnumProperty<T>* create(const std::wstring& name, const std::type_info& typeInfo,
                                   const std::unordered_set<T>& possibleValues,
                                   const Predicate<T>* predicates) {
        std::unordered_set<T> values;

        for (auto it = possibleValues.begin(); it != possibleValues.end(); ++it) {
            if (predicates->apply(*it))
                values.emplace((T&)*it);  // there's probably better way to do this but idk
        }

        return new EnumProperty<T>(name, typeInfo, values);
    }

    EnumProperty(const std::wstring& name, const std::type_info& typeInfo,
                 const std::unordered_set<T>& values)
        : AbstractProperty<T>(name, typeInfo) {
        for (auto it = values.begin(); it != values.end(); ++it) {
            std::wstring name((*it)->getSerializedName());
            this->mValues.find(name);  // what
            this->mValues[name] = *it;
            this->mAllowedValues.push_back(new TypedBoxed<T>((T*)&(*it)));
        }
        this->updateCachedHashCode();
    }

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

    std::vector<Boxed*> mAllowedValues;
    std::unordered_map<std::wstring, T> mValues;
};
