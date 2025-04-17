#include "Minecraft.World/entity/LivingEntity.h"
#include "Player.h"
#include "Minecraft.Client/CMinecraftApp.h"

void Player::staticCtor()
{
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
