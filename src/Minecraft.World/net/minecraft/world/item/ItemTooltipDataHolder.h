#pragma once

#include <memory>

class Player;

class ItemToolTipDataHolder {
public:
    std::shared_ptr<Player> mPlayer;
    void* fill;
    int idk;
};