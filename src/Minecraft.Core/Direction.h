#pragma once

class Direction {
public:
    static Direction* DOWN;
    static Direction* UP;
    static Direction* NORTH;
    static Direction* SOUTH;
    static Direction* EAST;
    static Direction* WEST;

    int getX() const;
    int getY() const;
    int getZ() const;
};