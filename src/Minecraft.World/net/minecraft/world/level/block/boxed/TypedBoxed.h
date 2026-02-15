#pragma once

#include "net/minecraft/world/level/block/boxed/Boxed.h"

template <typename T>
class TypedBoxed : public Boxed {
public:
    TypedBoxed(T* value) : Boxed(&typeid(*value)) { this->m_value = *value; }

    unsigned int hashOf() const override { return std::hash<T>{}(m_value); }
    bool operator==(const Boxed* compared) const override {
        if (!compared->isA(this->m_typeInfo))
            return false;

        return this->m_value == const_cast<TypedBoxed<T>*>(compared->tryGetType<T>())->m_value;
    }
    void setValue(const Boxed* boxed) override {
        this->m_value = *const_cast<TypedBoxed<T>*>(boxed->tryGetType<T>())->getValue();
    }
    std::wstring toString() const override;  // good luck

    T* getValue() { return &this->m_value; }

    T m_value;
};
