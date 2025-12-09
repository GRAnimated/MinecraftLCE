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

    const std::vector<Boxed*>& getPossibleValues() const override { return this->mAllowedValues; }
    // NON_MATCHING: logic should be the same :)
    bool equals(const Property* other) const override {
        if (this == other)
            return true;

        const EnumProperty<T>* otherCasted = dynamic_cast<const EnumProperty<T>*>(other);

        if (otherCasted && AbstractProperty<T>::equals(otherCasted)) {
            if (this->mAllowedValues == otherCasted->mAllowedValues) {
                return this->mValues == otherCasted->mValues;
            }
        }

        return false;
    }
    int hashCode() const override {
        return 31 * AbstractProperty<T>::hashCode() + AbstractProperty<T>::hashBoxedSet(this->mAllowedValues);
    }
    int getValueCount() const override { return this->mAllowedValues.size(); }
    Boxed* getValueAtIndex(unsigned int index) const override { return this->mAllowedValues.at(index); }
    // this function looks realllllllly bad, and it's mostly unlikely that's how it looked
    unsigned int getIndexForValue(Boxed* value) const override {
        Boxed& valueUn = *value;
        auto it = this->mAllowedValues.begin();
        if (it == this->mAllowedValues.end())
            return 0;

        int count = 0;
        for (it; it != this->mAllowedValues.end(); it++) {
            if (valueUn != (const Boxed*)*it) {
                return count;
            } else {
                count++;
            }
        }
        return 0;
    }
    T getUnboxedValue(const std::wstring& key) const override {
        auto it = this->mValues.find(key);
        if (it != this->mValues.end())
            return it->second;
        return nullptr;
    }
    std::wstring getName(const T& val) const override { return val->getSerializedName(); }
    virtual ~EnumProperty() {
        for (auto it = mAllowedValues.begin(); it != mAllowedValues.end(); it++) {
            delete *it;
        }
    }

    std::vector<Boxed*> mAllowedValues;
    std::unordered_map<std::wstring, T> mValues;
};
