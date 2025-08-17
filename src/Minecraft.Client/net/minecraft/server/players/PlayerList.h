#pragma once

#include <memory>

class BlockPos;
class Dimension;
class Player;
class Packet;

class PlayerList {
public:
    void broadcast(std::shared_ptr<Player>, double, double, double, double, int, std::shared_ptr<Packet>);

    bool isTrackingBlock(const BlockPos&, const Dimension*);
};
