#pragma once

#include "NQRNetworkManager.h"

class NQRNetworkManager_NX : public NQRNetworkManager {
public:
    static bool IsHandlingBootInvite();

    ~NQRNetworkManager_NX() override;
    void Tick() override;
    void Initialise() override;
    void Terminate() override;
    eNQRNetworkManagerState GetState() override;
    bool IsHost() override;
    bool IsReadyToPlayOrIdle() override;
    bool IsInSession() override;
    bool IsMatchmakingEnabled() override;
    void CreateAndJoinRoom(int, int, void*, int, int*, int, bool, unsigned char) override;
    void UpdateExternalRoomData() override;
    bool FriendRoomManagerIsBusy() override;
    void FriendRoomManagerSearch() override;
    void FriendRoomManagerSearch2() override;
    void FriendRoomManagerGetCount() override;
    void FriendRoomManagerGetRoomInfo(int, NQRNetworkManager::SessionSearchResult*) override;
    int JoinRoom(NQRNetworkManager::SessionSearchResult*, int) override;
    bool FriendPresenceUpdatedRoomList() override;
    void GetFriendRoomSearchResults(int*) override;
    void JoinRoom(unsigned int, int, const NQRNetworkManager::PresenceSyncInfo*) override;
    void JoinRoom(int, const nn::friends::FriendPresence*) override;
    void GetExtDataForRoom(unsigned int, void*, void (*)(bool, void*), void*) override;
    bool FindAndJoinRoom(int, unsigned int, CMatchMakeSearchParam*, unsigned char) override;
    void StartGame() override;
    void LeaveRoom(bool) override;
    void EndGame() override;
    bool SessionHasSpace(int) override;
    bool SessionHasMii(int) override;
    void AddLocalPlayerByUserIndex(int) override;
    void RemoveLocalPlayerByUserIndex(int) override;
    void SendInviteGUI() override;
    int GetPlayerCount() override;
    int GetOnlinePlayerCount() override;
    NQRNetworkPlayer* GetPlayerByIndex(int) override;
    NQRNetworkPlayer* GetPlayerBySmallId(int) override;
    NQRNetworkPlayer* GetPlayerByXuid(PlayerUID) override;
    void GetDisplayNameByGamertag(std::wstring) override;
    NQRNetworkPlayer* GetLocalPlayerByUserIndex(int) override;
    NQRNetworkPlayer* GetHostPlayer() override;
    void SetPresenceDataStartHostingGame() override;
    int GetJoiningReadyPercentage() override;
    void LocalDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) override;
    void RemoteDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) override;
    void GetSessionIndex(NQRNetworkPlayer*) override;
    void TryToConnectOnline(int (*)(void*, bool, int), void*, bool) override;
    bool isAdhocConnected() override;
    void connectToAdhoc() override;
    bool isLanConnected() override;
};
