#pragma once

#include <string>

class Boxed {
public:
    Boxed(const std::type_info* typeInfo);
    virtual ~Boxed();

    virtual bool isA(const std::type_info* type) const { return mTypeInfo == type; }
    virtual bool isA(const std::type_info& type) const { return mTypeInfo == &type; }
    virtual unsigned int hashOf() const = 0;
    virtual bool operator==(const Boxed* other) const = 0;
    virtual bool operator==(Boxed* other) const { return operator==(static_cast<const Boxed*>(other)); }
    virtual bool operator!=(const Boxed* other) const { return !operator==(other); }
    virtual bool operator!=(Boxed* other) const { return !operator==(static_cast<const Boxed*>(other)); }
    virtual void setValue(const Boxed* other) = 0;
    virtual std::wstring toString() const = 0;

private:
    const std::type_info* mTypeInfo;
};
