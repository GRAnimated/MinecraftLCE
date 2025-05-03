#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Client/eGameHostOption.h"
#include "Minecraft.Client/platform/NX/Platform.h"
#include "Minecraft.World/PlayerUID.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/inventory/Inventory.h"
#include "Minecraft.World/inventory/InventoryMenu.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.Core/BlockPos.h"
#include "Player.h"
#include <memory>

Player::Player(Level* level, std::wstring const& a3) : LivingEntity(level) {
    this->init();
    this->mGameProfile = a3;
    MemSect(11);
    this->mInventoryMenu = new InventoryMenu(this->mInventory, !level->mIsLocal, this);
    MemSect(0);
    this->mContainerMenu = this->mInventoryMenu;
    BlockPos sharedSpawnPos = level->getSharedSpawnPos();
    this->moveTo((double)sharedSpawnPos.getX() + 0.5, (double)(sharedSpawnPos.getY() + 1),
                 (double)sharedSpawnPos.getZ() + 0.5, 0.0F, 0.0F);
    this->mRotOffs = 180.0f;
    this->dword820 = 1;
    this->mSkinCapeId = 0;
    this->dword82C = 0;
    this->mSkinId = 0;
    this->bool834 = 0;
    this->qword838 = 0LL;
    this->bool840 = 0;
    this->SetPowerupTicks((PowerupItems::eGlide_Timed_Powerup_ID)0, 0);
    this->SetPowerupTicks((PowerupItems::eGlide_Timed_Powerup_ID)1, 0);
    this->SetPowerupTicks((PowerupItems::eGlide_Timed_Powerup_ID)2, 0);
    playerUID1 = PlayerUID(0);
    playerUID2 = PlayerUID(0);
    statsUID = StatsUID::EMPTY_SUID();
    this->setBool7FC(CConsoleMinecraftApp::sInstance.GetGameHostOption((eGameHostOption)4));
    this->bool7FD = false;
}

void Player::SetPowerupTicks(PowerupItems::eGlide_Timed_Powerup_ID id, int ticks) {
    this->mGlidepowerUpTicks[id] = ticks;
}

// NON_MATCHING
void Player::staticCtor() {
    // 4 counts of defineIdInternal
    // also SynchedEntityData :abyss:
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00000107"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin20000107"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00000111"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin20000111"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00000222"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin20000222"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00000223"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin20000223"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin20000231"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00000320"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002056"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002057"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002518"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002715"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002716"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00001626"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00001244"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00001246"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00001248"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00001254"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002405"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002417"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002421"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002411"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002424"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00003225"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002730"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002715"));
    sSkins.push_back(CMinecraftApp::getSkinIdFromPath(L"dlcskin00002104"));
}

void Player::updatePlayerSize() {
    float newHeight, newWidth;

    if (this->dword880 == 2) {
        newHeight = 0.0f;
        newWidth = 0.0f;
    } else if (this->dword880 == 1) {
        newHeight = 0.3f;
        newWidth = 0.3f;
    } else {
        if (this->isFallFlying()) {
            newHeight = 0.6f;
            newWidth = 0.6f;
        } else if (this->isSleeping()) {
            newHeight = 0.2f;
            newWidth = 0.2f;
        } else if (this->isSneaking()) {
            newHeight = 1.65f;
            newWidth = 0.6f;
        } else {
            newHeight = 1.8f;
            newWidth = 0.6f;
        }
    }

    if (newWidth != this->mWidth || newHeight != this->mHeight) {
        const AABB* aabb = this->getBoundingBox();
        aabb = aabb->newTemp(aabb->min.x, aabb->min.y, aabb->min.z, aabb->min.x + (double)newWidth,
                             aabb->min.y + (double)newHeight, aabb->min.z + (double)newWidth);

        if (!this->mLevel->hasBlockCubes(aabb) || this->isPassenger()) {
            this->setSize(newWidth, newHeight);
        }
    }
}
