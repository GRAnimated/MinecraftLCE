#include "INetworkPlayer.h"
#include "NQRNetworkManager.h"
#include "NQRNetworkPlayer.h"
#include "NX/Thread/C4JEventImpl.h"
#include "NX/Thread/C4JThreadImpl.h"
#include "Nintendo/NX/Network/CPlatformNetworkManagerNintendo.h"
#include "net/minecraft/client/CGameNetworkManager.h"
#include "net/minecraft/network/Socket.h"

/*void CPlatformNetworkManagerNintendo::Initialise(CGameNetworkManager*, int) {
    this->byte10 = 0;
    this->byte13 = 0;
    (*(void(__fastcall**)(__int64, _QWORD))(*(_QWORD*)CProfile::sInstance + 632LL))(CProfile::sInstance, 0LL);
    this->word11 = 0;
    this->byte12 = 0;
    this->word14 = 0;
    v6 = (NQRNetworkManager_NX*)operator new(0x1950u);
    sub_71007D6B84(v6, (__int64)&this->Listener_VTable);
    this->qword18 = v6;
    v7 = operator new(0x1950u);
    ZN26NQRNetworkManager_Adhoc_NXC_gen(v7, (__int64)&this->Listener_VTable);
    this->qword20 = v7;
    v8 = operator new(0x22C0u);
    sub_71007CE934(v8, (__int64)&this->Listener_VTable);
    qword_71017DB830 = v8;
    v9 = (NQRNetworkManager_NX*)this->qword18;
    this->mNQRNetworkManager = v9;
    v9->VTable->Initialise(v9);
    (*(void(__fastcall**)(_QWORD))(*(_QWORD*)this->qword20 + 24LL))(this->qword20);
    (*(void(__fastcall**)(__int64))(*(_QWORD*)qword_71017DB830 + 24LL))(qword_71017DB830);
    this->qword1E0 = a2;
    this->dword58 = a3;
    qword_71017DB838 = (__int64)this;
    this->qword1E8 = 0LL;
    this->qword1F0 = 0LL;
    this->word50 = 0;
    this->qword1F8 = 0LL;
    this->qword200 = 0LL;
    result = 1LL;
    this->byte53 = 0;
    this->byte55 = 0;
    this->qword278 = 0LL;
    this->qword280 = 0LL;
    this->qword260 = 0LL;
    this->qword268 = 0LL;
    this->byte54 = 1;
    this->byte274 = 0;
}*/

void CPlatformNetworkManagerNintendo::Terminate() {
    this->mNQRNetworkManager->Terminate();
}

int CPlatformNetworkManagerNintendo::GetJoiningReadyPercentage() {
    return this->mNQRNetworkManager->GetJoiningReadyPercentage();
}

int CPlatformNetworkManagerNintendo::CorrectErrorIDS(int errorIDS) {
    return errorIDS;
}

void CPlatformNetworkManagerNintendo::DoWork() {
    this->TickSearch();

    if (this->mRequestLeaveRoom) {
        this->mNQRNetworkManager->LeaveRoom(this->byte54);
        this->mRequestLeaveRoom = false;
    }
    this->mNQRNetworkManager->Tick();
    if (this->mRequestEnableAdhoc) {
        this->setAdhocMode(true);
    } else if (this->mRequestDisableAdhoc) {
        this->setAdhocMode(false);
    } else if (this->mRequestSignIn) {
        this->setLanMode(true);
    } else if (this->mRequestSignout) {
        this->setLanMode(false);
    }
}

int CPlatformNetworkManagerNintendo::GetPlayerCount() {
    return this->mNQRNetworkManager->GetPlayerCount();
}

int CPlatformNetworkManagerNintendo::GetOnlinePlayerCount() {
    return this->mNQRNetworkManager->GetOnlinePlayerCount();
}

int CPlatformNetworkManagerNintendo::GetLocalPlayerMask(int mask) {
    return 1 << mask;
}

void CPlatformNetworkManagerNintendo::AddLocalPlayerByUserIndex(int index) {
    this->mNQRNetworkManager->AddLocalPlayerByUserIndex(index);
}

// NON_MATCHING: something is getting pushed on stack???
void CPlatformNetworkManagerNintendo::RemoveLocalPlayerByUserIndex(int index) {
    INetworkPlayer* netPlayer = getNetworkPlayer(this->mNQRNetworkManager->GetLocalPlayerByUserIndex(index));
    if (netPlayer) {
        if (netPlayer->GetSocket()) {
            C4JThreadImpl* thr = new C4JThreadImpl(RemovePlayerOnSocketClosedThreadProc, netPlayer,
                                                   "RemovePlayerOnSocketClosed", 0);
            thr->SetProcessor(2);
            thr->Run();
        } else {
            this->mNQRNetworkManager->RemoveLocalPlayerByUserIndex(index);
        }
    }
}

int CPlatformNetworkManagerNintendo::AddLocalPlayerByPlayerUID(PlayerUID) {
    return 0;
}

INetworkPlayer* CPlatformNetworkManagerNintendo::GetLocalPlayerByUserIndex(int index) {
    return getNetworkPlayer(this->mNQRNetworkManager->GetLocalPlayerByUserIndex(index));
}

INetworkPlayer* CPlatformNetworkManagerNintendo::GetPlayerByIndex(int index) {
    return getNetworkPlayer(this->mNQRNetworkManager->GetPlayerByIndex(index));
}

INetworkPlayer* CPlatformNetworkManagerNintendo::GetPlayerByXuid(PlayerUID uid) {
    return getNetworkPlayer(this->mNQRNetworkManager->GetPlayerByXuid(uid));
}

INetworkPlayer* CPlatformNetworkManagerNintendo::GetPlayerBySmallId(unsigned char id) {
    return getNetworkPlayer(this->mNQRNetworkManager->GetPlayerBySmallId(id));
}

bool CPlatformNetworkManagerNintendo::ShouldMessageForFullSession() {
    return false;
}

INetworkPlayer* CPlatformNetworkManagerNintendo::GetHostPlayer() {
    return getNetworkPlayer(this->mNQRNetworkManager->GetHostPlayer());
}

bool CPlatformNetworkManagerNintendo::IsHost() {
    if (this->mNQRNetworkManager->IsHost())
        return !this->byte53;

    return false;
}

void CPlatformNetworkManagerNintendo::JoinGameFromInviteInfo(int, int a3,
                                                             const nn::friends::FriendPresence* a4) {
    this->mNQRNetworkManager->JoinRoom(a3, a4);
}

bool CPlatformNetworkManagerNintendo::LeaveGame(bool a2) {
    if (this->mLeavingGame)
        return true;
    this->mLeavingGame = true;
    INetworkPlayer* netPlayer = getNetworkPlayer(
        this->mNQRNetworkManager->GetLocalPlayerByUserIndex(CGameNetworkManager::sInstance.GetPrimaryPad()));
    if (netPlayer) {
        Socket* socket = netPlayer->GetSocket();
        if (socket) {
            socket->mEvent->WaitForSignal(-1);
            if (this->IsInSession()) {
                getNetworkPlayer(this->mNQRNetworkManager->GetLocalPlayerByUserIndex(
                                     CGameNetworkManager::sInstance.GetPrimaryPad()))
                    ->SetSocket(nullptr);
            }
            delete socket;
        }
    }
    if (this->mNQRNetworkManager->IsHost() && CGameNetworkManager::sInstance.ServerStoppedValid()) {
        this->mNQRNetworkManager->EndGame();
        CGameNetworkManager::sInstance.ServerStoppedWait();
        CGameNetworkManager::sInstance.ServerStoppedDestroy();
    }
    return this->_LeaveGame(a2, true);
}

bool CPlatformNetworkManagerNintendo::IsInSession() {
    return this->mNQRNetworkManager->IsInSession();
}

bool CPlatformNetworkManagerNintendo::IsInGameplay() {
    return this->mNQRNetworkManager->GetState() == NQRNetworkManager::IN_GAMEPLAY;
}

bool CPlatformNetworkManagerNintendo::IsReadyToPlayOrIdle() {
    return this->mNQRNetworkManager->IsReadyToPlayOrIdle();
}

bool CPlatformNetworkManagerNintendo::IsInStatsEnabledSession() {
    return true;
}

bool CPlatformNetworkManagerNintendo::IsMatchmakingEnabled() {
    return this->mNQRNetworkManager->IsMatchmakingEnabled();
}

bool CPlatformNetworkManagerNintendo::IsHandlingBootInvite() {
    return this->mNQRNetworkManager->IsHandlingBootInvite();
}

bool CPlatformNetworkManagerNintendo::SessionHasSpace(unsigned int sessionId) {
    return this->mNQRNetworkManager->SessionHasSpace(sessionId);
}

/*bool CPlatformNetworkManagerNintendo::SessionHasMii(int sessionId) {
    return this->mNQRNetworkManager->SessionHasMii(sessionId);
}*/

void CPlatformNetworkManagerNintendo::SendInviteGUI(int) {
    this->mNQRNetworkManager->SendInviteGUI();
}

bool CPlatformNetworkManagerNintendo::IsAddingPlayer() {
    return false;
}

void CPlatformNetworkManagerNintendo::HostGame(int a2, bool onlineGame, bool privateGame, unsigned char a5,
                                               EMiniGameId miniGameId, unsigned int a7, unsigned int* a8) {
    this->SetLocalGame(!onlineGame);
    this->SetPrivateGame(privateGame);
    this->sub_71007C2578();
    this->bool5C = a7 != 0;
    int playerMask = this->GetLocalPlayerMask(CGameNetworkManager::sInstance.GetPrimaryPad()) | a2;
    this->_HostGame(playerMask, a5, miniGameId, a7, a8);
}

int CPlatformNetworkManagerNintendo::JoinGame(FriendSessionInfo* info, int joiningPlayers, int, bool) {
    int joiningCount = 0;
    for (int i = 0; i < 4; i++) {
        joiningCount += ((joiningPlayers >> i) & 1);
    }
    joiningCount += info->mCurrentPlayerCount;

    if (joiningCount <= CGameNetworkManager::sInstance.GetMaxPlayers(&info->mGameSessionData)) {
        int ret = this->mNQRNetworkManager->JoinRoom(&info->mSearchResult, joiningPlayers);
        return (ret & 1) == 0;
    }

    return 2;
}

// NON_MATCHING: logic should be the same though
bool CPlatformNetworkManagerNintendo::FindAndJoinGame(int joiningPlayers, int a3, EMiniGameId miniGameId,
                                                      unsigned int a5, unsigned int* a6, unsigned int* a7) {
    CMatchMakeSearchParam searchParams;

    searchParams.params[0] = 0;
    searchParams.params[1] = (miniGameId << 24) | 0x30780;
    searchParams.params[2] = 0;
    searchParams.params[3] = 1;
    int joiningCount = 0;
    for (int i = 0; i < 4; i++) {
        joiningCount += ((joiningPlayers >> i) & 1);
    }
    searchParams.params[4] = joiningCount;
    searchParams.params[5] = 5;

    int paramIndex = 6;
    for (unsigned int i = 0; i < a5; ++i) {
        searchParams.params[paramIndex] = a6[i];
        searchParams.params[paramIndex + 1] = a7[i] + 2;

        paramIndex += 3;
    }
    return !this->mNQRNetworkManager->FindAndJoinRoom(joiningPlayers, (a5 + 2), &searchParams, miniGameId);
}

void CPlatformNetworkManagerNintendo::CancelJoinGame() {}

bool CPlatformNetworkManagerNintendo::SetLocalGame(bool localGame) {
    if (this->mNQRNetworkManager->GetState() == 2)
        this->mLocalGame = localGame;
    return true;
}

bool CPlatformNetworkManagerNintendo::IsLocalGame() {
    return this->mLocalGame;
}

bool CPlatformNetworkManagerNintendo::SetPrivateGame(bool privateGame) {
    return this->mPrivateGame = privateGame;
}

bool CPlatformNetworkManagerNintendo::IsPrivateGame() {
    return this->mPrivateGame;
}

bool CPlatformNetworkManagerNintendo::IsLeavingGame() {
    return this->mLeavingGame;
}

void CPlatformNetworkManagerNintendo::ResetLeavingGame() {
    this->mLeavingGame = false;
}

void CPlatformNetworkManagerNintendo::RegisterPlayerChangedCallback(int playerId,
                                                                    void (*)(void*, INetworkPlayer*, bool),
                                                                    void*) {
    // array stuff, but got really weak so gonnna leav it for futurte me
}

void CPlatformNetworkManagerNintendo::UnRegisterPlayerChangedCallback(int playerId,
                                                                      void (*)(void*, INetworkPlayer*, bool),
                                                                      void*) {}

void CPlatformNetworkManagerNintendo::HandleSignInChange() {}

void CPlatformNetworkManagerNintendo::_RunNetworkGame() {}

bool CPlatformNetworkManagerNintendo::_LeaveGame(bool, bool) {}

void CPlatformNetworkManagerNintendo::_HostGame(int, unsigned char, EMiniGameId, unsigned int,
                                                unsigned int*) {}

void CPlatformNetworkManagerNintendo::_StartGame() {}

void CPlatformNetworkManagerNintendo::UpdateAndSetGameSessionData(INetworkPlayer*) {}

void CPlatformNetworkManagerNintendo::RemoveLocalPlayer(INetworkPlayer*) {}

void CPlatformNetworkManagerNintendo::SystemFlagAddPlayer(INetworkPlayer*) {}

void CPlatformNetworkManagerNintendo::SystemFlagSet(INetworkPlayer*, int) {}

void CPlatformNetworkManagerNintendo::SystemFlagGet(INetworkPlayer*, int) {}

void CPlatformNetworkManagerNintendo::SystemFlagClearAll(INetworkPlayer*) {}

void CPlatformNetworkManagerNintendo::GatherStats() {}

void CPlatformNetworkManagerNintendo::GatherRTTStats() {}

void CPlatformNetworkManagerNintendo::SetSessionTexturePackParentId(int) {}

void CPlatformNetworkManagerNintendo::SetSessionSubTexturePackId(int) {}

void CPlatformNetworkManagerNintendo::SetSessionGameModeId(int) {}

void CPlatformNetworkManagerNintendo::Notify(int, unsigned long) {}

void CPlatformNetworkManagerNintendo::GetSessionList(int, int, bool) {}

void CPlatformNetworkManagerNintendo::GetGameSessionInfo(int, unsigned int, FriendSessionInfo*) {}

void CPlatformNetworkManagerNintendo::SetSessionsUpdatedCallback(void (*)(void*), void*) {}

void CPlatformNetworkManagerNintendo::GetFullFriendSessionInfo(FriendSessionInfo*, void (*)(bool, void*),
                                                               void*) {}

void CPlatformNetworkManagerNintendo::ForceFriendsSessionRefresh() {}

void CPlatformNetworkManagerNintendo::ClearFriendsSessions() {}

void CPlatformNetworkManagerNintendo::AlreadyInSession(const nn::friends::FriendPresence*) {}

void CPlatformNetworkManagerNintendo::GetAgeRestricted() {}

void CPlatformNetworkManagerNintendo::usingAdhocMode() {}

void CPlatformNetworkManagerNintendo::setAdhocMode(bool) {}

void CPlatformNetworkManagerNintendo::startAdhocMatching() {}

bool CPlatformNetworkManagerNintendo::isAdhocConnected() {}

void CPlatformNetworkManagerNintendo::connectToAdhoc() {}

bool CPlatformNetworkManagerNintendo::isAdhocModeChangeInProgress() {}

void CPlatformNetworkManagerNintendo::AttemptAdhocSignIn(int (*)(void*, bool, int), void*, bool) {}

void CPlatformNetworkManagerNintendo::setLanMode(bool) {}

void CPlatformNetworkManagerNintendo::usingLanMode() {}

bool CPlatformNetworkManagerNintendo::isLanConnected() {}

bool CPlatformNetworkManagerNintendo::isLanModeChangeInProgress() {}

void CPlatformNetworkManagerNintendo::checkValidInviteData(const nn::friends::FriendPresence*) {}

void CPlatformNetworkManagerNintendo::SetExitAndJoinFromInviteInProgress(bool) {}

void CPlatformNetworkManagerNintendo::CancelDisconnectFromExitAndJoin() {}

void CPlatformNetworkManagerNintendo::FakeLocalPlayerJoined() {}

void CPlatformNetworkManagerNintendo::GetDisplayNameByGamertag(std::wstring) {}

void CPlatformNetworkManagerNintendo::GetOutstandingAckCount(INetworkPlayer*) {}

void CPlatformNetworkManagerNintendo::TryToConnectOnline(int (*)(void*, bool, int), void*, bool) {}

void CPlatformNetworkManagerNintendo::AttemptPSNSignIn(int (*)(void*, bool, int), void*, bool, int) {}

void CPlatformNetworkManagerNintendo::RecvInviteGUI() {}

void CPlatformNetworkManagerNintendo::UpdateInviteData(void*) {}

void CPlatformNetworkManagerNintendo::CheckFriendsCanPlay(int, int&,
                                                          std::shared_ptr<ClientboundPreLoginPacket>, int,
                                                          int&, int&, int&, int&) {}
