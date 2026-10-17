#pragma once

#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include <string>
#include <unordered_map>
#include <vector>

class Vec3i;

class Direction : public StringRepresentable {
public:
    class Plane : public Predicate<const Direction*> {
    public:
        static Plane* HORIZONTAL;
        static Plane* VERTICAL;

        Plane();

        bool apply(const Direction*) const override;

        const Direction* getRandomDirection(Random&);
        arrayWithLength<const Direction*> iterator();
    };
    class AxisDirection {
    public:
        static AxisDirection* POSITIVE;
        static AxisDirection* NEGATIVE;
    };

    class Axis : public Predicate<const Direction*>, public StringRepresentable {
    public:
        static void staticCtor();
        static Axis* X;
        static Axis* Y;
        static Axis* Z;

        bool isHorizontal();
        int getId();

        static Axis* VALUES[3];

        static inline Predicates<Axis*>::ConstantPredicate* PREDICATE
            = new Predicates<Axis*>::ConstantPredicate(true);

        std::wstring toString() const override;
        std::wstring getSerializedName() const override;

    private:
        std::wstring m_name;
        Plane* m_plane;
        int m_id;
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

    static const Direction* from3DDataValue(int value);
    static const Direction* from2DDataValue(int value);

    Direction(int, int, int, const std::wstring&, Direction::AxisDirection*, Direction::Axis*, Vec3i*,
              unsigned char);
    virtual ~Direction();

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getZ() const { return m_z; }

    unsigned int get3DDataValue() const;
    int get2DDataValue() const;

    Axis* getAxis() const;
    Vec3i getNormal() const;
    AxisDirection* getAxisDirection() const;

    std::wstring getName() const;

    const Direction* getOpposite() const;

private:
    int m_dirX;
    int m_dirY;
    int m_dirZ;
    std::wstring m_name;
    Direction::Axis* m_axis;
    Direction::AxisDirection* m_axisDirection;
    Vec3i* m_pos;
    unsigned char m_index;
    int m_x;
    int m_y;
    int m_z;
};

static_assert(sizeof(Direction::Axis) == 0x38, "Direction::Axis Switch layout");
static_assert(sizeof(Direction) == 0x58, "Direction Switch layout");
