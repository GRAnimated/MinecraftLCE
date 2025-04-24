#pragma once

#include "Minecraft.Core/StringRepresentable.h"
#include <string>
#include <unordered_map>
#include <vector>

class Vec3i;

class Direction : public StringRepresentable {
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

        bool isHorizontal();
    };

    static const Direction* DOWN;
    static const Direction* UP;
    static const Direction* NORTH;
    static const Direction* SOUTH;
    static const Direction* EAST;
    static const Direction* WEST;

    static std::vector<const Direction*> VALUES;
    static const Direction* BY_2D_DATA[];
    static const Direction* BY_3D_DATA[];
    static int size;
    static std::unordered_map<std::wstring, const Direction*> BY_NAME;

    static void staticCtor();

    Direction(int, int, int, const std::wstring&, Direction::AxisDirection*, Direction::Axis*, Vec3i*,
              unsigned char);
    virtual ~Direction();

    int getX() const { return mX; }
    int getY() const { return mY; }
    int getZ() const { return mZ; }

    int get3DDataValue() const;
    int get2DDataValue() const;

    Axis* getAxis() const;

    std::wstring getName() const;

private:
    int mDirX;
    int mDirY;
    int mDirZ;
    std::wstring mName;
    Direction::Axis* mAxis;
    Direction::AxisDirection* mAxisDirection;
    Vec3i* mPos;
    unsigned char mIndex;
    int mX;
    int mY;
    int mZ;
};
