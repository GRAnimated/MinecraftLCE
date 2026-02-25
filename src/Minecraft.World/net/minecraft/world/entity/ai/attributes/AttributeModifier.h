#pragma once

#include <string>

enum eATTRIBUTE_ID { BASE_ATTACK_DAMAGE = 1, BASE_ATTACK_SPEED = 16 };

class AttributeModifier {
public:
    AttributeModifier(eATTRIBUTE_ID, double, int);

    double m_amount;
    int m_operation;
    std::wstring m_name;
    eATTRIBUTE_ID m_id;
    bool m_serialize;
};
