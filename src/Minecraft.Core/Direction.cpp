#include "Minecraft.Core/Direction.h"

#include "Minecraft.Core/Vec3i.h"

#include <string>

void Direction::staticCtor() {
    Axis::staticCtor();

    DOWN = new Direction(0, 1, -1, L"down", AxisDirection::NEGATIVE, Axis::Y, new Vec3i(0, -1, 0), 0);
    UP = new Direction(1, 0, -1, L"up", AxisDirection::POSITIVE, Axis::Y, new Vec3i(0, 1, 0), 1);
    NORTH = new Direction(2, 3, 2, L"north", AxisDirection::NEGATIVE, Axis::Z, new Vec3i(0, 0, -1), 2);
    SOUTH = new Direction(3, 2, 0, L"south", AxisDirection::POSITIVE, Axis::Z, new Vec3i(0, 0, 1), 3);
    WEST = new Direction(4, 5, 1, L"west", AxisDirection::NEGATIVE, Axis::X, new Vec3i(-1, 0, 0), 4);
    EAST = new Direction(5, 4, 3, L"east", AxisDirection::POSITIVE, Axis::X, new Vec3i(1, 0, 0), 5);

    for (auto it = VALUES.begin(); it != VALUES.end(); ++it) {
        const Direction* dir = *it;

        BY_3D_DATA[dir->mDirX] = dir;

        if (dir->getAxis()->isHorizontal())
            BY_2D_DATA[dir->mDirZ] = dir;

        std::wstring name = dir->getName();
        BY_NAME[name] = dir;
    }
}

Direction::Direction(int dirX, int dirY, int dirZ, const std::wstring& name,
                     Direction::AxisDirection* axisDirection, Direction::Axis* axis, Vec3i* pos,
                     unsigned char index) {
    mDirZ = dirZ;
    mDirY = dirY;
    mDirX = dirX;
    mName = name;
    mAxis = axis;
    mAxisDirection = axisDirection;
    mPos = new Vec3i(*pos);
    mIndex = index;

    VALUES.push_back(this);

    mX = pos->getX();
    mY = pos->getY();
    mZ = pos->getZ();
}

int Direction::get3DDataValue() const {
    return mDirX;
}

int Direction::get2DDataValue() const {
    return mDirZ;
}

Direction::Axis* Direction::getAxis() const {
    return mAxis;
}

std::wstring Direction::getName() const {
    return mName;
}
