#pragma once

#include "INetworkPlayer.h"

class NetworkPlayerNintendo : public INetworkPlayer {
public:
    NetworkPlayerNintendo(NQRNetworkPlayer*);

    // symbol from WiiU let's assuem it's the same
    const wchar_t* GetMiiName();

    int GetSmallId() override;
    void SendData(INetworkPlayer* player, const void* data, int size, bool reliable, bool ordered) override;
    bool IsSameSystem(INetworkPlayer* player) override;
    int GetOutstandingAckCount() override;
    int GetSinglePlayerOutstandingAckCount() override;
    void DecrementAcksOutstanding() override;
    int GetSendQueueSizeBytes(INetworkPlayer* player, bool includeOverhead) override;
    int GetSendQueueSizeMessages(INetworkPlayer* player, bool includeOverhead) override;
    int GetCurrentRtt() override;
    bool IsHost() override;
    bool IsGuest() override;
    bool IsLocal() override;
    int GetSessionIndex() override;
    bool IsTalking() override;
    bool IsMutedByLocalUser(int userIndex) override;
    bool HasVoice() override;
    bool HasCamera() override;
    int GetUserIndex() override;
    void SetSocket(Socket* socket) override;
    Socket* GetSocket() override;
    std::wstring GetOnlineName() override;
    std::wstring GetDisplayName() override;
    PlayerUID GetUID() override;
    void SetUID(PlayerUID uid) override;
    void SentChunkPacket() override;
    int GetTimeSinceLastChunkPacket_ms() override;
    bool isFake() override;
    NQRNetworkPlayer* GetQNetPlayer() override;

    NQRNetworkPlayer* mQNetPlayer;
    Socket* mSocket;
    long mLastChunkPacket_ms;
};