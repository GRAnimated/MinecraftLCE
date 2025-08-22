#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/command/EGameCommand.h"
#include "types.h"

class GameCommandPacket : public Packet, public std::enable_shared_from_this<GameCommandPacket> {
public:
    static std::shared_ptr<Packet> create();

    GameCommandPacket();
    GameCommandPacket(EGameCommand, arrayWithLength<uchar>);

    EGameCommand mCommand;
    int mArgsCount;
    arrayWithLength<uchar> mCommandArguments;
};
