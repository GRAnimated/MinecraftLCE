#pragma once

class BoundingBox {
public:
    int m_x0;
    int m_y0;
    int m_z0;
    int m_x1;
    int m_y1;
    int m_z1;

    BoundingBox(int x0, int y0, int z0, int x1, int y1, int z1);
};
