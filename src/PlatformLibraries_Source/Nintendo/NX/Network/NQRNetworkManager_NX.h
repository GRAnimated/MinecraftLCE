#pragma once

#include "PlatformLibraries_Source/NQRNetworkManager.h"

class NQRNetworkManager_NX : public NQRNetworkManager {
public:
    virtual ~NQRNetworkManager_NX() override;
    virtual void Tick() override;
    virtual void Initialise() override;
    virtual void Terminate() override;
    virtual void GetState() override;
    virtual void IsHost() override;
    virtual void IsReadyToPlayOrIdle() override;
    virtual void IsInSession() override;
    virtual void IsMatchmakingEnabled() override;
    virtual void CreateAndJoinRoom(int, int, void*, int, int*, int, bool, unsigned char) override;
    virtual void UpdateExternalRoomData() override;
    virtual void FriendRoomManagerIsBusy() override;
    virtual void FriendRoomManagerSearch() override;
    virtual void FriendRoomManagerSearch2() override;
    virtual void FriendRoomManagerGetCount() override;
    virtual void FriendRoomManagerGetRoomInfo(int, NQRNetworkManager::SessionSearchResult*) override;
    virtual void JoinRoom(NQRNetworkManager::SessionSearchResult*, int) override;
    virtual void JoinRoom(unsigned int, int, const NQRNetworkManager::PresenceSyncInfo*) override;
    virtual void JoinRoom(int, const nn::friends::FriendPresence*) override;
    virtual void FriendPresenceUpdatedRoomList() override;
    virtual void GetFriendRoomSearchResults(int*) override;
    virtual void GetExtDataForRoom(unsigned int, void*, void (*)(bool, void*), void*) override;
    virtual void FindAndJoinRoom(int, unsigned int, CMatchMakeSearchParam*, unsigned char) override;
    virtual void StartGame() override;
    virtual void LeaveRoom(bool) override;
    virtual void EndGame() override;
    virtual void SessionHasSpace(int) override;
    virtual void SessionHasMii(int) override;
    virtual void AddLocalPlayerByUserIndex(int) override;
    virtual void RemoveLocalPlayerByUserIndex(int) override;
    virtual void SendInviteGUI() override;
    virtual void GetPlayerCount() override;
    virtual void GetOnlinePlayerCount() override;
    virtual void GetPlayerByIndex(int) override;
    virtual void GetPlayerBySmallId(int) override;
    virtual void GetPlayerByXuid(PlayerUID) override;
    virtual void GetDisplayNameByGamertag(std::wstring) override;
    virtual void GetLocalPlayerByUserIndex(int) override;
    virtual void GetHostPlayer() override;
    virtual void SetPresenceDataStartHostingGame() override;
    virtual void GetJoiningReadyPercentage() override;
    virtual void LocalDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) override;
    virtual void RemoteDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) override;
    virtual void GetSessionIndex(NQRNetworkPlayer*) override;
    virtual void TryToConnectOnline(int (*)(void*, bool, int), void*, bool) override;
    virtual void isAdhocConnected() override;
    virtual void connectToAdhoc() override;
    virtual void isLanConnected() override;
};
