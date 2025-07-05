#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"

BoundingBox::BoundingBox(int x0, int y0, int z0, int x1, int y1, int z1) {
    this->x0 = x0;
    this->y0 = y0;
    this->z0 = z0;
    this->x1 = x1;
    this->y1 = y1;
    this->z1 = z1;
}
