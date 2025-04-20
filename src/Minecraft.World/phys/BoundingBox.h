//
// Created by DexrnZacAttack on 4/19/2025 (ZPC-I1)
//

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
