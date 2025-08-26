#pragma once

#include <memory>
#include <vector>

class BlockPos;
class Dimension;
class Player;
class Packet;
class ServerPlayer;

class PlayerList {
public:
    void broadcast(std::shared_ptr<Player>, double, double, double, double, int, std::shared_ptr<Packet>);
    void broadcastAll(std::shared_ptr<Packet> packet);

    std::vector<std::shared_ptr<ServerPlayer>>* getPlayers();

    bool isTrackingBlock(const BlockPos&, const Dimension*);
};
