#pragma once

#include <array>

class Direction {
public:
    static Direction* DOWN;
    static Direction* UP;
    static Direction* NORTH;
    static Direction* SOUTH;
    static Direction* EAST;
    static Direction* WEST;

    static std::array<Direction*, 6> DIRECTIONS;
    static Direction* END;
    static int size;

    int getX() const;
    int getY() const;
    int getZ() const;
};