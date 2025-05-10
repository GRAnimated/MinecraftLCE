#pragma once

class CGameNetworkManager {
public:
    static CGameNetworkManager* sInstance;

    bool IsLeavingGame();
    bool IsInSession();
    void Initialise();
    void SetLocalGame(bool local);
    bool IsHost();
};
