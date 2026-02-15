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
        return new Rotations(rotations->m_x, rotations->m_y, rotations->m_z);
    }

private:
    float m_x;
    float m_y;
    float m_z;
};
