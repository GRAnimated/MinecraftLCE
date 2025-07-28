#pragma once

class Rotations {
public:
    Rotations(float x, float y, float z);

    float getX() const;
    float getY() const;
    float getZ() const;

    static Rotations* copy(const Rotations* rotations) {
        if (!rotations)
            return nullptr;
        return new Rotations(rotations->x, rotations->y, rotations->z);
    }

private:
    float x;
    float y;
    float z;
};
