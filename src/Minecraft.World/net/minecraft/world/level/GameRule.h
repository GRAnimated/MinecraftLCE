#pragma once

#include <string>

class GameRule {
public:
    struct _ValueType {
        _ValueType() {
            field_8 = false;
            field_0 = 0;
        }

        bool field_8;
        long field_0;
    };

    void setParameter(const std::wstring&, GameRule::_ValueType);
};
