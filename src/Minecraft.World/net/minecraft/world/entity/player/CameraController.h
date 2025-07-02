#pragma once

#include "Minecraft.World/phys/Vec3.h"
#include <vector>
class CameraController {
public:
    class SplineNode {};

    CameraController(int);

    int getCameraMode();

    void* qword0;
    std::vector<CameraController::SplineNode> mSplineNodes;
    std::vector<std::vector<double>> doubles;
    void* qword38;
    void* qword40;
    void* qword48;
    void* qword50;
    Vec3* mPos;
    Vec3* mRot;
    void* qword68;
    int dword70;
    int mCameraMode;
    int dword78;
    int dword7C;
    int dword80;
};