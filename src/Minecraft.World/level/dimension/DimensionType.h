#pragma once

class Dimension;

class DimensionType {
public:
    static DimensionType* OVERWORLD;
    static DimensionType* NETHER;
    static DimensionType* END;

    static DimensionType* getById(int dimensionId);
    Dimension* create() const;
};
