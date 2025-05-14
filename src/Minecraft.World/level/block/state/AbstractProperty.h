#pragma once

#include <string>
#include <typeinfo>

class Boxed;
class Property {};

template <typename T>
class AbstractProperty : public Property {
public:
    virtual std::wstring getName() const;
    virtual std::wstring getName(Boxed const*) const;
    virtual int getPossibleValues() const = 0;
    virtual const std::type_info& getValueClass() const;
    virtual Boxed* getValue(const std::wstring&) const;
    virtual std::wstring toString() const;
    virtual bool equals(Property const*) const;
    virtual int hashCode() const;
    virtual int getValueCount() const = 0;
    virtual int getValueAtIndex(unsigned int) const = 0;
    virtual int getIndexForValue(Boxed*) const = 0;
    virtual std::wstring getName(const int&) const = 0;
    virtual int getUnboxedValue(const std::wstring&) const = 0;
};
