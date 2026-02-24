#pragma once

#include "net/minecraft/world/PlayerUID.h"
class NQRNetworkPlayer {
public:
    int GetCustomDataValue();
    int GetSmallId();
    void SendData(NQRNetworkPlayer*, const void*, unsigned int, bool);
    bool IsSameSystem(NQRNetworkPlayer*);
    int GetOutstandingAckCount();
    int GetSendQueueSizeBytes();
    int GetSendQueueSizeMessages();
    bool IsHost();
    PlayerUID GetUID();
    bool IsLocal();
    int GetSessionIndex();
    bool IsTalking();
    bool IsMutedByLocalUser(int);
    bool HasVoice();
    int GetLocalPlayerIndex();
    std::wstring GetNetworkNameW();
    std::wstring GetMiiName();
    void SetUID(PlayerUID);
};