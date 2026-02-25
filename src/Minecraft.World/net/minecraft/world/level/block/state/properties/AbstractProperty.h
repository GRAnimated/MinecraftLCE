#pragma once

#include "net/minecraft/core/System.h"
#include "net/minecraft/world/level/block/boxed/TypedBoxed.h"
#include <functional>
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
        FunctionPredicate(bool (*predicate)(T)) { this->m_predicate = predicate; }

        static FunctionPredicate* createPredicate(bool (*predicate)(T)) {
            return new FunctionPredicate(predicate);
        }

        bool apply(T a) const override { return this->m_predicate(a); }

        bool (*m_predicate)(T);
    };
    class ConstantPredicate : public Predicate<T> {
    public:
        ConstantPredicate(bool constValue) { this->m_constValue = constValue; }

        bool apply(T) const override { return this->m_constValue; }
        Predicate<T>* copy() const override { return new ConstantPredicate(this->m_constValue); }

        bool m_constValue;  // I guess it's bool, could be union; if you find possiblity of it, do it
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
    virtual const std::vector<Boxed*>& getPossibleValues() const = 0;
    virtual const std::type_info* getValueClass() const = 0;
    virtual Boxed* getValue(const std::wstring&) const = 0;
    virtual std::wstring getName(const Boxed*) const = 0;
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
        : Property(), m_typeInfo(&typeInfo), m_name(name) {}

    // TODO: fix TypedBoxed::tryGetType as in original it calls different one that is really the same but
    // different signature or something
    static int hashBoxedSet(const std::vector<Boxed*>& values) {
        int hash = 0;
        for (auto it = values.begin(); it != values.end(); it++) {
            // thanks god 4J did cast it to int here or it would explode I guess
            hash += (int)std::hash<T>{}(*const_cast<TypedBoxed<T>*>((*it)->tryGetType<T>())->getValue());
        }
        return hash;
    }

    std::wstring getName() const override { return this->m_name; }
    const std::type_info* getValueClass() const override { return this->m_typeInfo; }
    // NON_MATCHING: I'm dumb, impossible to match :), fix the structure
    Boxed* getValue(const std::wstring& name) const override {
        // they just get ptr to whatever getUnboxedValue returns, I'm 95% sure that getUnboxedValue returns
        // just T type, not reference, so yyou can't just get ptr of it directly so you have to create that
        // temp obj
        T retVal = this->getUnboxedValue(name);
        return new TypedBoxed<T>(&retVal);
    }
    std::wstring getName(const Boxed* boxedValue) const override {
        return this->getName(*const_cast<TypedBoxed<T>*>(boxedValue->tryGetType<T>())->getValue());
    }
    std::wstring toString() const override { return L""; }
    bool equals(const Property* other) const override {
        if (this == other)
            return true;

        const AbstractProperty<T>* otherCasted = dynamic_cast<const AbstractProperty<T>*>(other);

        if (!otherCasted || this->m_typeInfo != otherCasted->m_typeInfo) {
            return false;
        }

        return this->m_name == otherCasted->m_name;
    }
    // TODO: this is wrong as hell btw !!!!!
    int hashCode() const override { return 31 * (size_t)this->m_typeInfo + javaStringHashCode(this->m_name); }
    virtual T getUnboxedValue(const std::wstring&) const = 0;
    virtual std::wstring getName(const T&) const = 0;

    void* m_fill;
    const std::type_info* m_typeInfo;
    std::wstring m_name;
};
