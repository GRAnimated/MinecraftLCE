#pragma once

#include <memory>

class Packet;

class ServerGamePacketListenerImpl {
public:
    void send(std::shared_ptr<Packet>);
};
