#pragma once

#include "net/minecraft/world/level/block/boxed/Boxed.h"

template <typename T>
class TypedBoxed : public Boxed {
public:
    TypedBoxed(T* value) : Boxed(&typeid(*value)) { this->mValue = *value; }
    //~TypedBoxed() override;

    unsigned int hashOf() const override { return std::hash<T>{}(mValue); }
    bool operator==(const Boxed* compared) const override {
        if (!compared->isA(this->mTypeInfo))
            return false;

        return this->mValue == const_cast<TypedBoxed<T>*>(compared->tryGetType<T>())->mValue;
    }
    void setValue(const Boxed* boxed) override {
        this->mValue = *const_cast<TypedBoxed<T>*>(boxed->tryGetType<T>())->getValue();
    }
    std::wstring toString() const override;  // good luck

    T* getValue() { return &this->mValue; }

    T mValue;
};
