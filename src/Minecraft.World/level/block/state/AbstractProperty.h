#pragma once

#include <string>

class Boxed;
class Property {};

template <typename T>
class AbstractProperty : public Property {
public:
    virtual std::wstring getName() const;
    virtual std::wstring getName(Boxed const*) const;
    virtual int getPossibleValues() const = 0;
    virtual std::type_info const& getValueClass() const;
    virtual Boxed* getValue(std::wstring const&) const;
    virtual std::wstring toString() const;
    virtual bool equals(Property const*) const;
    virtual int hashCode() const;
    virtual int getValueCount() const = 0;
    virtual int getValueAtIndex(unsigned int) const = 0;
    virtual int getIndexForValue(Boxed*) const = 0;
    virtual std::wstring getName(int const&) const = 0;
    virtual int getUnboxedValue(std::wstring const&) const = 0;
};
