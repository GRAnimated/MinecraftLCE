#pragma once

class BlockPos;
class Level;

class WorldBorder {
public:
    WorldBorder(Level*);
    ~WorldBorder();

    void isWithinBounds(BlockPos const&);
    void getMinX();
    void getMaxX();
    void getMinZ();
    void getMaxZ();
    void getStatus();
    void getSize();
    virtual void getCenterX();
    virtual void getCenterZ();
    void getListeners();
    void setSize(double);
};
