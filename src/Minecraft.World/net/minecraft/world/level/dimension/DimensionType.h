#pragma once

#include <string>

class Dimension;

class DimensionType {
public:
    static DimensionType* OVERWORLD;
    static DimensionType* NETHER;
    static DimensionType* END;

    static DimensionType* getById(int dimensionId);

    std::wstring getName() const;
    char getId() const;
    Dimension* create() const;
};
