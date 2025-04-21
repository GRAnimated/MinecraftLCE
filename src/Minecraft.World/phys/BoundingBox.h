#pragma once

class BoundingBox {
    public:
        int x0;
        int y0;
        int z0;
        int x1;
        int y1;
        int z1;

        BoundingBox(int x0, int y0, int z0, int x1, int y1, int z1);
};
