#pragma once

#include <string>

enum eATTRIBUTE_ID { BASE_ATTACK_DAMAGE = 1, BASE_ATTACK_SPEED = 16 };

class AttributeModifier {
public:
    AttributeModifier(eATTRIBUTE_ID, double, int);

    double mAmount;
    int mOperation;
    std::wstring mName;
    eATTRIBUTE_ID mId;
    bool mSerialize;
};
