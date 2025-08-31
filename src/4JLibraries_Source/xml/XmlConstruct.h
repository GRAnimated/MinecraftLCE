#pragma once

// this is completly guessed, as everything there seems to be inlined on WiiU
class XmlInt {
public:
    bool hasValue() { return this->mHasValue; }
    int getValue() { return this->mValue; }

    bool mHasValue;
    int mValue;
};

class XmlConstruct {
public:
    XmlInt maybeInt() const;
};
