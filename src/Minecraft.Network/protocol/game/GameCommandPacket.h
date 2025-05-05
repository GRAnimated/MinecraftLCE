#include "types.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/command/EGameCommand.h"
#include "Minecraft.Network/protocol/Packet.h"

class GameCommandPacket : public Packet, public std::enable_shared_from_this<GameCommandPacket> {
    GameCommandPacket();
    GameCommandPacket(EGameCommand, arrayWithLength<uchar>);

    EGameCommand mCommand;
    int mArgsCount;
    arrayWithLength<uchar> mCommandArguments;
};