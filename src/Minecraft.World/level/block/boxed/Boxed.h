#pragma once

#include <string>

class Boxed {
public:
    Boxed(std::type_info const* typeInfo);
    virtual ~Boxed();

    virtual bool isA(std::type_info const* type) const { return mTypeInfo == type; }
    virtual bool isA(std::type_info const& type) const { return mTypeInfo == &type; }
    virtual unsigned int hashOf() const = 0;
    virtual bool operator==(Boxed const* other) const = 0;
    virtual bool operator==(Boxed* other) const { return operator==(static_cast<Boxed const*>(other)); }
    virtual bool operator!=(Boxed const* other) const { return !operator==(other); }
    virtual bool operator!=(Boxed* other) const { return !operator==(static_cast<Boxed const*>(other)); }
    virtual void setValue(Boxed const* other) = 0;
    virtual std::wstring toString() const = 0;

private:
    std::type_info const* mTypeInfo;
};
