#pragma once

#include "net/minecraft/world/phys/Vec3.h"
#include <vector>

class CameraController {
public:
    class SplineNode {};

    CameraController(int);

    int getCameraMode();

    void* m_qword0;
    std::vector<CameraController::SplineNode> m_splineNodes;
    std::vector<std::vector<double>> m_doubles;
    void* m_qword38;
    void* m_qword40;
    void* m_qword48;
    void* m_qword50;
    Vec3* m_pos;
    Vec3* m_rot;
    void* m_qword68;
    int m_dword70;
    int m_cameraMode;
    int m_dword78;
    int m_dword7C;
    int m_dword80;
};
