#pragma once

// this is completely guessed, as everything there seems to be inlined on WiiU
class XmlInt {
public:
    bool hasValue() { return this->m_hasValue; }
    int getValue() { return this->m_value; }

    bool m_hasValue;
    int m_value;
};

class XmlConstruct {
public:
    XmlInt maybeInt() const;
};
