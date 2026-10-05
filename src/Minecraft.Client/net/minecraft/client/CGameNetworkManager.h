#pragma once

class GameSessionData;

class CGameNetworkManager {
public:
    static CGameNetworkManager sInstance;

    bool IsLeavingGame();
    bool IsInSession();
    void Initialise();
    void SetLocalGame(bool local);
    bool IsHost();
    void ResetLeavingGame();
    void DoWork();
    bool IsLocalGame();
    int GetPlayerCount();
    int GetPrimaryPad();
    bool ServerStoppedValid();
    void ServerStoppedWait();
    void ServerStoppedDestroy();
    int GetMaxPlayers(GameSessionData*);
};
