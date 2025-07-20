#pragma once

#include <string>
class StringRepresentable {
public:
    virtual std::wstring toString() const;
    virtual std::wstring getSerializedName() const;
};
