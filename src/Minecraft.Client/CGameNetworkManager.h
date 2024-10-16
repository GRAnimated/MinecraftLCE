#pragma once

class CGameNetworkManager {
public:
    static CGameNetworkManager* sInstance;

    bool IsLeavingGame();
    bool IsInSession();
};
