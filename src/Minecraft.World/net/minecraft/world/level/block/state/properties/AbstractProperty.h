#pragma once

#include <string>
#include <typeinfo>
#include <vector>

template <typename T>
class Predicate {
    bool apply(T) const;
    Predicate<T>* copy() const;
};

template <typename T>
class Predicates {
public:
    // TODO: impl those, and check if those below are correctly declared
    class ConnectivePredicate : Predicate<T> {};
    class FunctionPredicate : Predicate<T> {};
    class ConstantPredicate : Predicate<T> {
    public:
        ConstantPredicate(bool);
    };
    class EqualToValuePredicate : Predicate<T> {};
};

class Boxed;
class Property {
    virtual std::wstring getName() const = 0;
    virtual std::wstring getName(const Boxed*) const = 0;
    virtual const std::vector<Boxed*>& getPossibleValues() const = 0;
    virtual const std::type_info& getValueClass() const = 0;
    virtual Boxed* getValue(const std::wstring&) const = 0;
    virtual std::wstring toString() const = 0;
    virtual bool equals(const Property*) const = 0;
    virtual int hashCode() const = 0;
    virtual int getValueCount() const = 0;
    virtual Boxed* getValueAtIndex(unsigned int) const = 0;
    virtual unsigned int getIndexForValue(Boxed*) const = 0;
};

template <typename T>
class AbstractProperty : public Property {
public:
    std::wstring getName() const override;
    std::wstring getName(const Boxed*) const override;
    const std::vector<Boxed*>& getPossibleValues() const override;
    const std::type_info& getValueClass() const override;
    Boxed* getValue(const std::wstring&) const override;
    std::wstring toString() const override;
    bool equals(const Property*) const override;
    int hashCode() const override;
    virtual std::wstring getName(const T&) const = 0;  // ?
    virtual T getUnboxedValue(const std::wstring&) const = 0;
};
