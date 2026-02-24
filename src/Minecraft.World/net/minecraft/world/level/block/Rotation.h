#pragma once

#include <string>

class Direction;
class Vec3i;

class Rotation {
public:
    enum eTYPE { ROTATE_0, ROTATE_90, ROTATE_180, ROTATE_270 };

    Rotation(const std::wstring& name, eTYPE type);

    Rotation* getRotated(Rotation* rot);
    Rotation* rotate(const Direction* dir) const;
    Rotation* fjRotate(const Vec3i&) const;
    eTYPE getType() const;  // most likely const

    std::wstring m_name;
    eTYPE m_type;
};
