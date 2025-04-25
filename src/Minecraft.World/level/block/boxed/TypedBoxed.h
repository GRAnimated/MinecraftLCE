#pragma once

#include "Minecraft.World/level/block/boxed/Boxed.h"

template <typename T>
class TypedBoxed : public Boxed {
public:
    TypedBoxed(T*);
    ~TypedBoxed() override;

    unsigned int hashOf() const override;
    bool operator==(Boxed const*) const override;
    void setValue(Boxed const*) override;
    std::wstring toString() const override;

    // Inlined, guessed name
    TypedBoxed<T>* tryGetType() const;
    T* getValue() const;
};
