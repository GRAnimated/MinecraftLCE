#pragma once

#include <string>

namespace nn::friends {
class FriendPresence;
}

class CMatchMakeSearchParam;
class NQRNetworkPlayer;
class PlayerUID;

class NQRNetworkManager {
public:
    class SessionSearchResult;
    class PresenceSyncInfo;

    virtual ~NQRNetworkManager();
    virtual void Tick() = 0;
    virtual void Initialise() = 0;
    virtual void Terminate() = 0;
    virtual void GetState() = 0;
    virtual void IsHost() = 0;
    virtual void IsReadyToPlayOrIdle() = 0;
    virtual void IsInSession() = 0;
    virtual void IsMatchmakingEnabled() = 0;
    virtual void CreateAndJoinRoom(int, int, void*, int, int*, int, bool, unsigned char) = 0;
    virtual void UpdateExternalRoomData() = 0;
    virtual void FriendRoomManagerIsBusy() = 0;
    virtual void FriendRoomManagerSearch() = 0;
    virtual void FriendRoomManagerSearch2() = 0;
    virtual void FriendRoomManagerGetCount() = 0;
    virtual void FriendRoomManagerGetRoomInfo(int, NQRNetworkManager::SessionSearchResult*) = 0;
    virtual void JoinRoom(NQRNetworkManager::SessionSearchResult*, int) = 0;
    virtual void JoinRoom(unsigned int, int, const NQRNetworkManager::PresenceSyncInfo*) = 0;
    virtual void JoinRoom(int, const nn::friends::FriendPresence*) = 0;
    virtual void FriendPresenceUpdatedRoomList() = 0;
    virtual void GetFriendRoomSearchResults(int*) = 0;
    virtual void GetExtDataForRoom(unsigned int, void*, void (*)(bool, void*), void*) = 0;
    virtual void FindAndJoinRoom(int, unsigned int, CMatchMakeSearchParam*, unsigned char) = 0;
    virtual void StartGame() = 0;
    virtual void LeaveRoom(bool) = 0;
    virtual void EndGame() = 0;
    virtual void SessionHasSpace(int) = 0;
    virtual void SessionHasMii(int) = 0;
    virtual void AddLocalPlayerByUserIndex(int) = 0;
    virtual void RemoveLocalPlayerByUserIndex(int) = 0;
    virtual void SendInviteGUI() = 0;
    virtual void GetPlayerCount() = 0;
    virtual void GetOnlinePlayerCount() = 0;
    virtual void GetPlayerByIndex(int) = 0;
    virtual void GetPlayerBySmallId(int) = 0;
    virtual void GetPlayerByXuid(PlayerUID) = 0;
    virtual void GetDisplayNameByGamertag(std::wstring) = 0;
    virtual void GetLocalPlayerByUserIndex(int) = 0;
    virtual void GetHostPlayer() = 0;
    virtual void SetPresenceDataStartHostingGame() = 0;
    virtual void GetJoiningReadyPercentage() = 0;
    virtual void LocalDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) = 0;
    virtual void RemoteDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) = 0;
    virtual void GetSessionIndex(NQRNetworkPlayer*) = 0;
    virtual void TryToConnectOnline(int (*)(void*, bool, int), void*, bool) = 0;
    virtual void isAdhocConnected() = 0;
    virtual void connectToAdhoc() = 0;
    virtual void isLanConnected() = 0;
};
