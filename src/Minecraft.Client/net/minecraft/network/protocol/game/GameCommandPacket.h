#pragma once

#include "types.h"
#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/command/EGameCommand.h"

class GameCommandPacket : public Packet, public std::enable_shared_from_this<GameCommandPacket> {
    GameCommandPacket();
    GameCommandPacket(EGameCommand, arrayWithLength<uchar>);

    EGameCommand mCommand;
    int mArgsCount;
    arrayWithLength<uchar> mCommandArguments;
};
