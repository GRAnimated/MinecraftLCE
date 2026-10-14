#include "net/minecraft/world/phys/AABB.h"

#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/phys/HitResult.h"
#include "net/minecraft/world/phys/Vec3.h"

HitResult* AABB::clip(Vec3* start, Vec3* end) const {
    Vec3* closest = collideWithXPlane(m_inX, start, end);
    const Direction* face = Direction::WEST;
    Vec3* candidate = collideWithXPlane(m_axX, start, end);
    if (candidate && isClosest(start, closest, candidate)) {
        closest = candidate;
        face = Direction::EAST;
    }
    candidate = collideWithYPlane(m_inY, start, end);
    if (candidate && isClosest(start, closest, candidate)) {
        closest = candidate;
        face = Direction::DOWN;
    }
    candidate = collideWithYPlane(m_axY, start, end);
    if (candidate && isClosest(start, closest, candidate)) {
        closest = candidate;
        face = Direction::UP;
    }
    candidate = collideWithZPlane(m_inZ, start, end);
    if (candidate && isClosest(start, closest, candidate)) {
        closest = candidate;
        face = Direction::NORTH;
    }
    candidate = collideWithZPlane(m_axZ, start, end);
    if (candidate && isClosest(start, closest, candidate)) {
        closest = candidate;
        face = Direction::SOUTH;
    }
    // Strict distance comparison preserves the earlier face at edges and corners.
    return closest ? new HitResult(closest, face) : nullptr;
}
