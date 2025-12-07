#pragma once

#include <string>
#include <typeinfo>
#include <vector>

template <typename T>
class Predicate {
public:
    Predicate() {}

    virtual bool apply(T) const = 0;
    virtual Predicate<T>* copy() const { return nullptr; }
    virtual ~Predicate() {}
};

template <typename T>
class Predicates {
public:
    // TODO: impl those, and check if those below are correctly declared
    class ConnectivePredicate : public Predicate<T> {
        bool apply(T) const override;
    };
    class FunctionPredicate : public Predicate<T> {
    public:
        FunctionPredicate(bool (*predicate)(T)) { this->mPredicate = predicate; }

        static FunctionPredicate* createPredicate(bool (*predicate)(T)) {
            return new FunctionPredicate(predicate);
        }

        bool apply(T a) const override { return this->mPredicate(a); }

        bool (*mPredicate)(T);
    };
    class ConstantPredicate : public Predicate<T> {
    public:
        ConstantPredicate(bool constValue) { this->mConstValue = constValue; }

        bool apply(T) const override { return this->mConstValue; }
        Predicate<T>* copy() const override { return new ConstantPredicate(this->mConstValue); }

        bool mConstValue;  // I guess it's bool, could be union; if you find possiblity of it, do it
    };
    class EqualToValuePredicate : public Predicate<T> {
        bool apply(T) const override;
    };
};

class Boxed;
class Property {
public:
    Property();
    void updateCachedHashCode();

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
    AbstractProperty(const std::wstring& name, const std::type_info& typeInfo)
        : Property(), mTypeInfo(typeInfo), mName(name) {}

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

    void* fill;
    const std::type_info& mTypeInfo;
    std::wstring mName;
};
