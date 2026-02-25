#pragma once

#include <string>

template <typename T>
class TypedBoxed;

class Boxed {
public:
    Boxed(const std::type_info* typeInfo);

    virtual ~Boxed();
    virtual bool isA(const std::type_info* type) const;
    virtual bool isA(const std::type_info& type) const;
    virtual unsigned int hashOf() const = 0;
    virtual bool operator==(const Boxed* other) const = 0;
    virtual bool operator==(Boxed* other) const;
    virtual bool operator!=(const Boxed* other) const;
    virtual bool operator!=(Boxed* other) const;
    virtual void setValue(const Boxed* other) = 0;
    virtual std::wstring toString() const = 0;

    template <typename T>
    const TypedBoxed<T>* tryGetType() const {
        return this->isA(typeid(T)) ? static_cast<const TypedBoxed<T>*>(this) : nullptr;
    }

    const std::type_info* m_typeInfo;
};
