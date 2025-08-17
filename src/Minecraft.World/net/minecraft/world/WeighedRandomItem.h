#pragma once

class WeighedRandomItem {
public:
    WeighedRandomItem(int a2) : mWeight(a2) {}
    virtual ~WeighedRandomItem() = default;

private:
    int mWeight;
};
