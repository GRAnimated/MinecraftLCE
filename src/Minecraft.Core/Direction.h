#pragma once

#include <vector>

class Vec3i;

class Direction {
public:
    class AxisDirection {
    public:
        static AxisDirection* POSITIVE;
        static AxisDirection* NEGATIVE;
    };

    class Axis {
    public:
        static void staticCtor();
        static Axis* X;
        static Axis* Y;
        static Axis* Z;
    };

    static Direction* DOWN;
    static Direction* UP;
    static Direction* NORTH;
    static Direction* SOUTH;
    static Direction* EAST;
    static Direction* WEST;

    static std::vector<Direction*> VALUES;
    static int size;

    static void staticCtor();

    Direction(int, int, int, const std::wstring&, Direction::AxisDirection*, Direction::Axis*, Vec3i*, unsigned char);

    int getX() const;
    int getY() const;
    int getZ() const;
};