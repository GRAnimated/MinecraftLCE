#pragma once

#include <memory>

class Container;
class Player;

class HopperMenu {
public:
    HopperMenu(std::shared_ptr<Container>, std::shared_ptr<Container>, std::shared_ptr<Player>);
};
