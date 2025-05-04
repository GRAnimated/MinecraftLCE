#include "Minecraft.World/entity/player/CameraController.h"

// NON_MATCHING ORDERING and type iirc
CameraController::CameraController(int mode) : dword70(mode != 3), mCameraMode(mode) {
    this->qword0 = 0LL;
    this->dword78 = 0;
    this->qword50 = 0LL;
    this->qword38 = 0LL;
    this->qword40 = 0LL;
    this->qword48 = 0LL;
    this->mPos = Vec3::newPermanent(0.0, 0.0, 0.0);
    this->mRot = Vec3::newPermanent(0.0, 0.0, 0.0);
    this->qword68 = 0LL;
    this->dword7C = -1;
    this->dword80 = 0;
}