#pragma once

class BlockPos;
class Direction;
class Vec3i;
class DataInputStream;
class DataOutputStream;

class BoundingBox {
public:
    int m_x0;
    int m_y0;
    int m_z0;
    int m_x1;
    int m_y1;
    int m_z1;

    BoundingBox();
    explicit BoundingBox(BoundingBox*);
    BoundingBox(int x0, int z0, int x1, int z1);
    BoundingBox(int x0, int y0, int z0, int x1, int y1, int z1);
    static BoundingBox* getUnknownBox();
    static BoundingBox* createProper(int, int, int, int, int, int);
    static BoundingBox* orientBox(int x, int y, int z, int offsetX, int offsetY, int offsetZ, int width,
                                  int height, int depth, const Direction*);
    bool intersects(BoundingBox*);
    bool intersects(Vec3i lower, Vec3i upper);
    bool intersects(int x0, int z0, int x1, int z1);
    void expand(BoundingBox*);
    void move(int x, int y, int z);
    bool isInside(Vec3i);
    int getXSpan();
    int getYSpan();
    int getZSpan();
    BlockPos getCenter();
    void write(DataOutputStream*);
    void read(DataInputStream*);
};

static_assert(sizeof(BoundingBox) == 0x18, "Switch bounding box layout");
