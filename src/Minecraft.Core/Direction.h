#pragma once

#include <string>
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
    virtual ~Direction();

    int getX() const;
    int getY() const;
    int getZ() const;

private:
    int mDirX;
    int mDirY;
    int mDirZ;
    std::wstring field_18;
    Direction::Axis* field_30;
    Direction::AxisDirection* field_38;
    Vec3i* mPos;
    unsigned char byte_48;
    int mX;
    int mY;
    int mZ;
};
