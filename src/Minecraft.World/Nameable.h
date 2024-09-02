#pragma once

class Nameable {
public:
    Nameable();

    virtual void getName() = 0;
    virtual void hasCustomName() = 0;
    virtual void getDisplayName() = 0;
    virtual void getCustomName() = 0;
};
