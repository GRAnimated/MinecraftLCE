#pragma once

#include <string>

class GameRule {
public:
    struct _ValueType {
        _ValueType() {
            m_field8 = false;
            m_field0 = 0;
        }

        bool m_field8;
        long m_field0;
    };

    void setParameter(const std::wstring&, GameRule::_ValueType);
};
