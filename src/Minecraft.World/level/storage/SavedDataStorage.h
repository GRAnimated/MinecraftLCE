#pragma once

#include <string>
#include <typeinfo>

class SavedData;

class SavedDataStorage {
public:
    virtual ~SavedDataStorage();
    virtual void get(const std::type_info&, const std::wstring&);
    virtual void set(const std::wstring&, std::shared_ptr<SavedData>);
    virtual void save();
    virtual void getFreeAuxValueFor(const std::wstring&);
};
