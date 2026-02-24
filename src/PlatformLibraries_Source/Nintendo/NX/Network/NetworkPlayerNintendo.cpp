#include "INetworkPlayer.h"
#include "NQRNetworkPlayer.h"
#include "PlatformLibraries_Source/Nintendo/NX/Network/NetworkPlayerNintendo.h"
#include "net/minecraft/core/System.h"
#include <string>

NetworkPlayerNintendo::NetworkPlayerNintendo(NQRNetworkPlayer* netPlayer) : INetworkPlayer() {
    this->m_mSocket = nullptr;
    this->m_mLastChunkPacketMs = 0;
    this->m_mQNetPlayer = netPlayer;
}

int NetworkPlayerNintendo::GetSmallId() {
    return this->m_mQNetPlayer->GetSmallId();
}

void NetworkPlayerNintendo::SendData(INetworkPlayer* player, const void* data, int size, bool reliable,
                                     bool ordered) {
    this->m_mQNetPlayer->SendData(((NetworkPlayerNintendo*)player)->m_mQNetPlayer, data, size, ordered);
}

bool NetworkPlayerNintendo::IsSameSystem(INetworkPlayer* player) {
    // it's either that member variables are part of interface, or they are casting it like i'm doing rn
    return this->m_mQNetPlayer->IsSameSystem(((NetworkPlayerNintendo*)player)->m_mQNetPlayer);
}

int NetworkPlayerNintendo::GetOutstandingAckCount() {
    return this->m_mQNetPlayer->GetOutstandingAckCount();
}

int NetworkPlayerNintendo::GetSinglePlayerOutstandingAckCount() {
    return 0;
}

void NetworkPlayerNintendo::DecrementAcksOutstanding() {}

int NetworkPlayerNintendo::GetSendQueueSizeBytes(INetworkPlayer* player, bool includeOverhead) {
    return this->m_mQNetPlayer->GetSendQueueSizeBytes();
}

int NetworkPlayerNintendo::GetSendQueueSizeMessages(INetworkPlayer* player, bool includeOverhead) {
    return this->m_mQNetPlayer->GetSendQueueSizeMessages();
}

int NetworkPlayerNintendo::GetCurrentRtt() {
    return 0;
}

bool NetworkPlayerNintendo::IsHost() {
    return this->m_mQNetPlayer->IsHost();
}

// NON_MATCHING: correct PlayerUID struct
bool NetworkPlayerNintendo::IsGuest() {
    return (this->m_mQNetPlayer->GetUID().m_gap0 & 2) >> 1;
}

bool NetworkPlayerNintendo::IsLocal() {
    return this->m_mQNetPlayer->IsLocal();
}

int NetworkPlayerNintendo::GetSessionIndex() {
    return this->m_mQNetPlayer->GetSessionIndex();
}

bool NetworkPlayerNintendo::IsTalking() {
    return this->m_mQNetPlayer->IsTalking();
}

bool NetworkPlayerNintendo::IsMutedByLocalUser(int userIndex) {
    return this->m_mQNetPlayer->IsMutedByLocalUser(userIndex);
}

bool NetworkPlayerNintendo::HasVoice() {
    return this->m_mQNetPlayer->HasVoice();
}

bool NetworkPlayerNintendo::HasCamera() {
    return false;
}

int NetworkPlayerNintendo::GetUserIndex() {
    return this->m_mQNetPlayer->GetLocalPlayerIndex();
}

void NetworkPlayerNintendo::SetSocket(Socket* socket) {
    this->m_mSocket = socket;
}

Socket* NetworkPlayerNintendo::GetSocket() {
    return this->m_mSocket;
}

std::wstring NetworkPlayerNintendo::GetOnlineName() {
    return this->m_mQNetPlayer->GetNetworkNameW();
}

std::wstring NetworkPlayerNintendo::GetDisplayName() {
    if (this->IsLocal())
        return this->GetMiiName();

    return this->GetOnlineName();
}

PlayerUID NetworkPlayerNintendo::GetUID() {
    return this->m_mQNetPlayer->GetUID();
}

void NetworkPlayerNintendo::SetUID(PlayerUID uid) {
    this->m_mQNetPlayer->SetUID(uid);
}

void NetworkPlayerNintendo::SentChunkPacket() {
    this->m_mLastChunkPacketMs = System::processTimeInMilliSecs();
}

int NetworkPlayerNintendo::GetTimeSinceLastChunkPacket_ms() {
    if (this->m_mLastChunkPacketMs)
        return System::processTimeInMilliSecs() - this->m_mLastChunkPacketMs;
    else
        return 0x7fffffff;
}

bool NetworkPlayerNintendo::isFake() {
    return false;
}

NQRNetworkPlayer* NetworkPlayerNintendo::GetQNetPlayer() {
    return this->m_mQNetPlayer;
}
