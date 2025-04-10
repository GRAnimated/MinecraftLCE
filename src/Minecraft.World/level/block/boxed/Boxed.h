#pragma once

#include <string>

class Boxed {
public:
    Boxed();
    virtual ~Boxed();

    virtual void isA(std::type_info const*) const;
    virtual void isA(std::type_info const&) const;
    virtual unsigned int hashOf() const = 0;
    virtual bool operator==(Boxed const*) const = 0;
    virtual bool operator==(Boxed*) const;
    virtual bool operator!=(Boxed const*) const;
    virtual bool operator!=(Boxed*) const;
    virtual void setValue(Boxed const*) = 0;
    virtual std::wstring toString() const = 0;
};
