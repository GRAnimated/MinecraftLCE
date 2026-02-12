#pragma once

class WeighedRandomItem {
public:
    WeighedRandomItem(int a2) : m_weight(a2) {}
    virtual ~WeighedRandomItem() = default;

private:
    int m_weight;
};
