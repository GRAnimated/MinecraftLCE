#include "net/minecraft/world/entity/player/CameraController.h"

// NON_MATCHING ORDERING and type iirc
CameraController::CameraController(int mode) : m_dword70(mode != 3), m_cameraMode(mode) {
    this->m_qword0 = 0LL;
    this->m_dword78 = 0;
    this->m_qword50 = 0LL;
    this->m_qword38 = 0LL;
    this->m_qword40 = 0LL;
    this->m_qword48 = 0LL;
    this->m_pos = Vec3::newPermanent(0.0, 0.0, 0.0);
    this->m_rot = Vec3::newPermanent(0.0, 0.0, 0.0);
    this->m_qword68 = 0LL;
    this->m_dword7C = -1;
    this->m_dword80 = 0;
}
