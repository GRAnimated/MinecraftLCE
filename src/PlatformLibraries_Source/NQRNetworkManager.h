#pragma once

#include <string>

class NQRNetworkPlayer;
class PlayerUID;

namespace nn::friends {
class FriendPresence;
}

struct CMatchMakeSearchParam {
    unsigned int m_params[14];
};

class NQRNetworkManager {
public:
    struct SessionSearchResult {
        char m_fill[84];
    };
    class PresenceSyncInfo;

    enum eNQRNetworkManagerState { IN_GAMEPLAY = 6 };

    virtual ~NQRNetworkManager();
    virtual void Tick() = 0;
    virtual void Initialise() = 0;
    virtual void Terminate() = 0;
    virtual eNQRNetworkManagerState GetState() = 0;
    virtual bool IsHost() = 0;
    virtual bool IsReadyToPlayOrIdle() = 0;
    virtual bool IsInSession() = 0;
    virtual bool IsMatchmakingEnabled() = 0;
    virtual void CreateAndJoinRoom(int, int, void*, int, int*, int, bool, unsigned char) = 0;
    virtual void UpdateExternalRoomData() = 0;
    virtual bool FriendRoomManagerIsBusy() = 0;
    virtual void FriendRoomManagerSearch() = 0;
    virtual void FriendRoomManagerSearch2() = 0;
    virtual void FriendRoomManagerGetCount() = 0;
    virtual void FriendRoomManagerGetRoomInfo(int, NQRNetworkManager::SessionSearchResult*) = 0;
    virtual int JoinRoom(NQRNetworkManager::SessionSearchResult*, int) = 0;
    virtual bool FriendPresenceUpdatedRoomList() = 0;
    virtual void GetFriendRoomSearchResults(int*) = 0;
    virtual void JoinRoom(unsigned int, int, const NQRNetworkManager::PresenceSyncInfo*) = 0;
    virtual void JoinRoom(int, const nn::friends::FriendPresence*) = 0;
    virtual void GetExtDataForRoom(unsigned int, void*, void (*)(bool, void*), void*) = 0;
    virtual bool FindAndJoinRoom(int, unsigned int, CMatchMakeSearchParam*, unsigned char) = 0;
    virtual void StartGame() = 0;
    virtual void LeaveRoom(bool) = 0;
    virtual void EndGame() = 0;
    virtual bool SessionHasSpace(int) = 0;
    virtual bool SessionHasMii(int) = 0;
    virtual void AddLocalPlayerByUserIndex(int) = 0;
    virtual void RemoveLocalPlayerByUserIndex(int) = 0;
    virtual void SendInviteGUI() = 0;
    virtual int GetPlayerCount() = 0;
    virtual int GetOnlinePlayerCount() = 0;
    virtual NQRNetworkPlayer* GetPlayerByIndex(int) = 0;
    virtual NQRNetworkPlayer* GetPlayerBySmallId(int) = 0;
    virtual NQRNetworkPlayer* GetPlayerByXuid(PlayerUID) = 0;
    virtual void GetDisplayNameByGamertag(std::wstring) = 0;
    virtual NQRNetworkPlayer* GetLocalPlayerByUserIndex(int) = 0;
    virtual NQRNetworkPlayer* GetHostPlayer() = 0;
    virtual void SetPresenceDataStartHostingGame() = 0;
    virtual int GetJoiningReadyPercentage() = 0;
    virtual void LocalDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) = 0;
    virtual void RemoteDataSend(NQRNetworkPlayer*, NQRNetworkPlayer*, const void*, unsigned int) = 0;
    virtual void GetSessionIndex(NQRNetworkPlayer*) = 0;
    virtual void TryToConnectOnline(int (*)(void*, bool, int), void*, bool) = 0;
    virtual bool isAdhocConnected() = 0;
    virtual void connectToAdhoc() = 0;
    virtual bool isLanConnected() = 0;
};
