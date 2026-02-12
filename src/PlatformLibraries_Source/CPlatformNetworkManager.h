#pragma once

#include "PlatformLibraries_Source/NQRNetworkManager.h"
#include "net/minecraft/network/protocol/game/ClientboundPreLoginPacket.h"
#include "net/minecraft/world/PlayerUID.h"
#include "net/minecraft/world/level/gamemode/minigames/EMiniGameId.h"
#include <cstdint>

namespace nn::friends {
class FriendPresence;
}
class CGameNetworkManager;
class GameSessionData {
    char filuniek[346];
};
struct FriendSessionInfo {
    void* qword0;
    NQRNetworkManager::SessionSearchResult mSearchResult;
    GameSessionData mGameSessionData;
    uint8_t mCurrentPlayerCount;
};
class INetworkPlayer;
class NQRNetworkPlayer;

class CPlatformNetworkManager {
public:
    virtual void Initialise(CGameNetworkManager*, int) = 0;
    virtual void Terminate() = 0;
    virtual int GetJoiningReadyPercentage() = 0;
    virtual int CorrectErrorIDS(int) = 0;
    virtual void DoWork() = 0;
    virtual int GetPlayerCount() = 0;
    virtual int GetOnlinePlayerCount() = 0;
    virtual int GetLocalPlayerMask(int) = 0;
    virtual void AddLocalPlayerByUserIndex(int) = 0;
    virtual void RemoveLocalPlayerByUserIndex(int) = 0;
    virtual int AddLocalPlayerByPlayerUID(PlayerUID) = 0;
    virtual INetworkPlayer* GetLocalPlayerByUserIndex(int) = 0;
    virtual INetworkPlayer* GetPlayerByIndex(int) = 0;
    virtual INetworkPlayer* GetPlayerByXuid(PlayerUID) = 0;
    virtual INetworkPlayer* GetPlayerBySmallId(unsigned char) = 0;
    virtual bool ShouldMessageForFullSession() = 0;
    virtual INetworkPlayer* GetHostPlayer() = 0;
    virtual bool IsHost() = 0;
    virtual void JoinGameFromInviteInfo(int, int, const nn::friends::FriendPresence*) = 0;
    virtual bool LeaveGame(bool) = 0;
    virtual bool IsInSession() = 0;
    virtual bool IsInGameplay() = 0;
    virtual bool IsReadyToPlayOrIdle() = 0;
    virtual bool IsInStatsEnabledSession() = 0;
    virtual bool IsMatchmakingEnabled() = 0;
    virtual bool IsHandlingBootInvite() = 0;
    virtual bool SessionHasSpace(unsigned int) = 0;
    // virtual bool SessionHasMii(int) = 0;
    virtual void SendInviteGUI(int) = 0;
    virtual bool IsAddingPlayer() = 0;
    virtual void HostGame(int, bool, bool, unsigned char, EMiniGameId, unsigned int, unsigned int*) = 0;
    virtual int JoinGame(FriendSessionInfo*, int, int, bool) = 0;
    virtual bool FindAndJoinGame(int, int, EMiniGameId, unsigned int, unsigned int*, unsigned int*) = 0;
    virtual void CancelJoinGame() = 0;
    virtual bool SetLocalGame(bool) = 0;
    virtual bool IsLocalGame() = 0;
    virtual bool SetPrivateGame(bool) = 0;
    virtual bool IsPrivateGame() = 0;
    virtual bool IsLeavingGame() = 0;
    virtual void ResetLeavingGame() = 0;
    virtual void RegisterPlayerChangedCallback(int, void (*)(void*, INetworkPlayer*, bool), void*) = 0;
    virtual void UnRegisterPlayerChangedCallback(int, void (*)(void*, INetworkPlayer*, bool), void*) = 0;
    virtual void HandleSignInChange() = 0;
    virtual void _RunNetworkGame() = 0;
    virtual bool _LeaveGame(bool, bool) = 0;
    virtual void _HostGame(int, unsigned char, EMiniGameId, unsigned int, unsigned int*) = 0;
    virtual void _StartGame() = 0;
    virtual void UpdateAndSetGameSessionData(INetworkPlayer*) = 0;
    virtual void RemoveLocalPlayer(INetworkPlayer*) = 0;
    virtual void SystemFlagAddPlayer(INetworkPlayer*) = 0;
    virtual void SystemFlagSet(INetworkPlayer*, int) = 0;
    virtual void SystemFlagGet(INetworkPlayer*, int) = 0;
    virtual void SystemFlagClearAll(INetworkPlayer*) = 0;
    virtual void GatherStats() = 0;
    virtual void GatherRTTStats() = 0;
    virtual void SetSessionTexturePackParentId(int) = 0;
    virtual void SetSessionSubTexturePackId(int) = 0;
    virtual void SetSessionGameModeId(int) = 0;
    virtual void Notify(int, unsigned long) = 0;
    virtual void GetSessionList(int, int, bool) = 0;
    virtual void GetGameSessionInfo(int, unsigned int, FriendSessionInfo*) = 0;
    virtual void SetSessionsUpdatedCallback(void (*)(void*), void*) = 0;
    virtual void GetFullFriendSessionInfo(FriendSessionInfo*, void (*)(bool, void*), void*) = 0;
    virtual void ForceFriendsSessionRefresh() = 0;
    virtual void ClearFriendsSessions() = 0;
    virtual void AlreadyInSession(const nn::friends::FriendPresence*) = 0;
    virtual void GetAgeRestricted() = 0;
    virtual void usingAdhocMode() = 0;
    virtual void setAdhocMode(bool) = 0;
    virtual void startAdhocMatching() = 0;
    virtual bool isAdhocConnected() = 0;
    virtual void connectToAdhoc() = 0;
    virtual bool isAdhocModeChangeInProgress() = 0;
    virtual void AttemptAdhocSignIn(int (*)(void*, bool, int), void*, bool) = 0;
    virtual void setLanMode(bool) = 0;
    virtual void usingLanMode() = 0;
    virtual bool isLanConnected() = 0;
    virtual bool isLanModeChangeInProgress() = 0;
    virtual void checkValidInviteData(const nn::friends::FriendPresence*) = 0;
    virtual void SetExitAndJoinFromInviteInProgress(bool) = 0;
    virtual void CancelDisconnectFromExitAndJoin() = 0;
    virtual void FakeLocalPlayerJoined() = 0;
    virtual void GetDisplayNameByGamertag(std::wstring) = 0;
    virtual void GetOutstandingAckCount(INetworkPlayer*) = 0;
    virtual void TryToConnectOnline(int (*)(void*, bool, int), void*, bool) = 0;
    virtual void AttemptPSNSignIn(int (*)(void*, bool, int), void*, bool, int) = 0;
    virtual void RecvInviteGUI() = 0;
    virtual void UpdateInviteData(void*) = 0;
    virtual void CheckFriendsCanPlay(int, int&, std::shared_ptr<ClientboundPreLoginPacket>, int, int&, int&,
                                     int&, int&)
        = 0;
    virtual ~CPlatformNetworkManager() = 0;
};
