#include "Minecraft.Core/Direction.h"

#include "Minecraft.Core/Vec3i.h"

#include <string>

// NON_MATCHING
void Direction::staticCtor() {
    Axis::staticCtor();

    DOWN = new Direction(0, 1, -1, L"down", AxisDirection::NEGATIVE, Axis::Y, new Vec3i(0, -1, 0), 0);
    UP = new Direction(1, 0, -1, L"up", AxisDirection::POSITIVE, Axis::Y, new Vec3i(0, 1, 0), 1);
    NORTH = new Direction(2, 3, 2, L"north", AxisDirection::NEGATIVE, Axis::Z, new Vec3i(0, 0, -1), 2);
    SOUTH = new Direction(3, 2, 0, L"south", AxisDirection::POSITIVE, Axis::Z, new Vec3i(0, 0, 1), 3);
    EAST = new Direction(4, 5, 1, L"east", AxisDirection::NEGATIVE, Axis::X, new Vec3i(-1, 0, 0), 4);
    WEST = new Direction(5, 4, 3, L"west", AxisDirection::POSITIVE, Axis::X, new Vec3i(1, 0, 0), 5);

    VALUES = {DOWN, UP, NORTH, SOUTH, EAST, WEST};
}

// NON_MATCHING: There's more code surrounding the values push back
Direction::Direction(int dirX, int dirY, int dirZ, const std::wstring& name, Direction::AxisDirection* axisDirection, Direction::Axis* axis, Vec3i* pos, unsigned char u8) {
    mDirX = dirX;
    mDirY = dirY;
    mDirZ = dirZ;
    field_18 = name;
    field_30 = axis;
    field_38 = axisDirection;
    mPos = new Vec3i(*pos);
    byte_48 = u8;

    VALUES.push_back(this);

    mX = pos->getX();
    mY = pos->getY();
    mZ = pos->getZ();
}
