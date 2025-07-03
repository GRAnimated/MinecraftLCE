#pragma once

#include <memory>

class Player;

class PlayerIO {
public:
    PlayerIO();
    virtual ~PlayerIO();
    virtual void save(std::shared_ptr<Player>) = 0;
    virtual void load(std::shared_ptr<Player>) = 0;
    virtual void clearOldPlayerFiles() = 0;
    virtual void saveMapIdLookup() = 0;
    virtual void deleteMapFilesForPlayer(std::shared_ptr<Player>) = 0;
    virtual void saveAllCachedData() = 0;
};
