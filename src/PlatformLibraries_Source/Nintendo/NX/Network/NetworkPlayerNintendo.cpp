#include "INetworkPlayer.h"
#include "NQRNetworkPlayer.h"
#include "PlatformLibraries_Source/Nintendo/NX/Network/NetworkPlayerNintendo.h"
#include "net/minecraft/core/System.h"
#include <string>

NetworkPlayerNintendo::NetworkPlayerNintendo(NQRNetworkPlayer* netPlayer) : INetworkPlayer() {
    this->mSocket = nullptr;
    this->mLastChunkPacket_ms = 0;
    this->mQNetPlayer = netPlayer;
}

int NetworkPlayerNintendo::GetSmallId() {
    return this->mQNetPlayer->GetSmallId();
}

void NetworkPlayerNintendo::SendData(INetworkPlayer* player, const void* data, int size, bool reliable,
                                     bool ordered) {
    this->mQNetPlayer->SendData(((NetworkPlayerNintendo*)player)->mQNetPlayer, data, size, ordered);
}

bool NetworkPlayerNintendo::IsSameSystem(INetworkPlayer* player) {
    // it's either that member variables are part of interface, or they are casting it like i'm doing rn
    return this->mQNetPlayer->IsSameSystem(((NetworkPlayerNintendo*)player)->mQNetPlayer);
}

int NetworkPlayerNintendo::GetOutstandingAckCount() {
    return this->mQNetPlayer->GetOutstandingAckCount();
}

int NetworkPlayerNintendo::GetSinglePlayerOutstandingAckCount() {
    return 0;
}

void NetworkPlayerNintendo::DecrementAcksOutstanding() {}

int NetworkPlayerNintendo::GetSendQueueSizeBytes(INetworkPlayer* player, bool includeOverhead) {
    return this->mQNetPlayer->GetSendQueueSizeBytes();
}

int NetworkPlayerNintendo::GetSendQueueSizeMessages(INetworkPlayer* player, bool includeOverhead) {
    return this->mQNetPlayer->GetSendQueueSizeMessages();
}

int NetworkPlayerNintendo::GetCurrentRtt() {
    return 0;
}

bool NetworkPlayerNintendo::IsHost() {
    return this->mQNetPlayer->IsHost();
}

// NON_MATCHING: correct PlayerUID struct
bool NetworkPlayerNintendo::IsGuest() {
    return (this->mQNetPlayer->GetUID().gap_0 & 2) >> 1;
}

bool NetworkPlayerNintendo::IsLocal() {
    return this->mQNetPlayer->IsLocal();
}

int NetworkPlayerNintendo::GetSessionIndex() {
    return this->mQNetPlayer->GetSessionIndex();
}

bool NetworkPlayerNintendo::IsTalking() {
    return this->mQNetPlayer->IsTalking();
}

bool NetworkPlayerNintendo::IsMutedByLocalUser(int userIndex) {
    return this->mQNetPlayer->IsMutedByLocalUser(userIndex);
}

bool NetworkPlayerNintendo::HasVoice() {
    return this->mQNetPlayer->HasVoice();
}

bool NetworkPlayerNintendo::HasCamera() {
    return false;
}

int NetworkPlayerNintendo::GetUserIndex() {
    return this->mQNetPlayer->GetLocalPlayerIndex();
}

void NetworkPlayerNintendo::SetSocket(Socket* socket) {
    this->mSocket = socket;
}

Socket* NetworkPlayerNintendo::GetSocket() {
    return this->mSocket;
}

std::wstring NetworkPlayerNintendo::GetOnlineName() {
    return this->mQNetPlayer->GetNetworkNameW();
}

std::wstring NetworkPlayerNintendo::GetDisplayName() {
    if (this->IsLocal())
        return this->GetMiiName();

    return this->GetOnlineName();
}

PlayerUID NetworkPlayerNintendo::GetUID() {
    return this->mQNetPlayer->GetUID();
}

void NetworkPlayerNintendo::SetUID(PlayerUID uid) {
    this->mQNetPlayer->SetUID(uid);
}

void NetworkPlayerNintendo::SentChunkPacket() {
    this->mLastChunkPacket_ms = System::processTimeInMilliSecs();
}

int NetworkPlayerNintendo::GetTimeSinceLastChunkPacket_ms() {
    if (this->mLastChunkPacket_ms)
        return System::processTimeInMilliSecs() - this->mLastChunkPacket_ms;
    else
        return 0x7fffffff;
}

bool NetworkPlayerNintendo::isFake() {
    return false;
}

NQRNetworkPlayer* NetworkPlayerNintendo::GetQNetPlayer() {
    return this->mQNetPlayer;
}
