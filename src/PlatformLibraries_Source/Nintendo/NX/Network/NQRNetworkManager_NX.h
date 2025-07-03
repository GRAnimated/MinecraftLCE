#pragma once

#include "PlatformLibraries_Source/NQRNetworkManager.h"

class NQRNetworkManager_NX : public NQRNetworkManager {
public:
    ~NQRNetworkManager_NX() override;
    void Tick() override;
    void Initialise() override;
    void Terminate() override;
    void GetState() override;
    void IsHost() override;
    void IsReadyToPlayOrIdle() override;
    void IsInSession() override;
    void IsMatchmakingEnabled() override;
    void CreateAndJoinRoom(int, int, void*, int, int*, int, bool, unsigned char) override;
    void UpdateExternalRoomData() override;
    void FriendRoomManagerIsBusy() override;
    void FriendRoomManagerSearch() override;
    void FriendRoomManagerSearch2() override;
    void FriendRoomManagerGetCount() override;
    void FriendRoomManagerGetRoomInfo(int, NQRNetworkManager::SessionSearchResult*) override;
    void JoinRoom(NQRNetworkManager::SessionSearchResult*, int) override;
    void JoinRoom(unsigned int, int, const NQRNetworkManager::PresenceSyncInfo*) override;
    void JoinRoom(int, const nn::friends::FriendPresence*) override;
    void FriendPresenceUpdatedRoomList() override;
    void GetFriendRoomSearchResults(int*) override;
    void GetExtDataForRoom(unsigned int, void*, void (*)(bool, void*), void*) override;
    void FindAndJoinRoom(int, unsigned int, CMatchMakeSearchParam*, unsigned char) override;
    void StartGame() override;
    void LeaveRoom(bool) override;
    void EndGame() override;
    void SessionHasSpace(int) override;
    void SessionHasMii(int) override;
    void AddLocalPlayerByUserIndex(int) override;
    void RemoveLocalPlayerByUserIndex(int) override;
    void SendInviteGUI() override;
    void GetPlayerCount() override;
    void GetOnlinePlayerCount() override;
    void GetPlayerByIndex(int) override;
    void GetPlayerBySmallId(int) override;
    void GetPlayerByXuid(PlayerUID) override;
    void GetDisplayNameByGamertag(std::wstring) override;
    void GetLocalPlayerByUserIndex(int) override;
    void GetHostPlayer() override;
    void SetPresenceDataStartHostingGame() override;
    void GetJoiningReadyPercentage() override;
    void LocalDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) override;
    void RemoteDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) override;
    void GetSessionIndex(NQRNetworkPlayer*) override;
    void TryToConnectOnline(int (*)(void*, bool, int), void*, bool) override;
    void isAdhocConnected() override;
    void connectToAdhoc() override;
    void isLanConnected() override;
};
