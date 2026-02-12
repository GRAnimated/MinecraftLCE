#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"

BoundingBox::BoundingBox(int x0, int y0, int z0, int x1, int y1, int z1) {
    this->m_x0 = x0;
    this->m_y0 = y0;
    this->m_z0 = z0;
    this->m_x1 = x1;
    this->m_y1 = y1;
    this->m_z1 = z1;
}
