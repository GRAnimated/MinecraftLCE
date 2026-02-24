#pragma once

#include <memory>

class Player;

class ItemToolTipDataHolder {
public:
    std::shared_ptr<Player> m_player;
    void* m_fill;
    int m_idk;
};
