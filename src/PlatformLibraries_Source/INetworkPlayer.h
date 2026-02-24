#pragma once

#include "net/minecraft/world/PlayerUID.h"

class Socket;
class NQRNetworkPlayer;

class INetworkPlayer {
public:
    INetworkPlayer();

    virtual ~INetworkPlayer() = 0;
    virtual int GetSmallId() = 0;
    virtual void SendData(INetworkPlayer* player, const void* data, int size, bool reliable, bool ordered)
        = 0;
    virtual bool IsSameSystem(INetworkPlayer* player) = 0;
    virtual int GetOutstandingAckCount() = 0;
    virtual int GetSinglePlayerOutstandingAckCount() = 0;
    virtual void DecrementAcksOutstanding() = 0;
    virtual int GetSendQueueSizeBytes(INetworkPlayer* player, bool includeOverhead) = 0;
    virtual int GetSendQueueSizeMessages(INetworkPlayer* player, bool includeOverhead) = 0;
    virtual int GetCurrentRtt() = 0;
    virtual bool IsHost() = 0;
    virtual bool IsGuest() = 0;
    virtual bool IsLocal() = 0;
    virtual int GetSessionIndex() = 0;
    virtual bool IsTalking() = 0;
    virtual bool IsMutedByLocalUser(int userIndex) = 0;
    virtual bool HasVoice() = 0;
    virtual bool HasCamera() = 0;
    virtual int GetUserIndex() = 0;
    virtual void SetSocket(Socket* socket) = 0;
    virtual Socket* GetSocket() = 0;
    virtual std::wstring GetOnlineName() = 0;
    virtual std::wstring GetDisplayName() = 0;
    virtual PlayerUID GetUID() = 0;
    virtual void SetUID(PlayerUID uid) = 0;
    virtual void SentChunkPacket() = 0;
    virtual int GetTimeSinceLastChunkPacket_ms() = 0;
    virtual bool isFake() = 0;
    virtual NQRNetworkPlayer* GetQNetPlayer() = 0;
};