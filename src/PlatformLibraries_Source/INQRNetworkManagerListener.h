#pragma once

#include "CPlatformNetworkManager.h"
#include "NQRNetworkManager.h"

class NQRNetworkPlayer;

class INQRNetworkManagerListener {
public:
    virtual ~INQRNetworkManagerListener();
    virtual void HandleDataReceived(NQRNetworkPlayer*, NQRNetworkPlayer*, unsigned char*, unsigned int) = 0;
    virtual void HandlePlayerJoined(NQRNetworkPlayer*) = 0;
    virtual void HandlePlayerLeaving(NQRNetworkPlayer*) = 0;
    virtual void HandleStateChange(NQRNetworkManager::eNQRNetworkManagerState,
                                   NQRNetworkManager::eNQRNetworkManagerState, bool)
        = 0;
    virtual void HandleResyncPlayerRequest(NQRNetworkPlayer**) = 0;
    virtual void HandleAddLocalPlayerFailed(int) = 0;
    virtual void HandleDisconnect(bool) = 0;
    virtual void HandleInviteReceived(int, nn::friends::FriendPresence*) = 0;
};