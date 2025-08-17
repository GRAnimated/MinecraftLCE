#include "net/minecraft/network/protocol/game/GameCommandPacket.h"

GameCommandPacket::GameCommandPacket(EGameCommand command, arrayWithLength<uchar> commandArguments) {
    this->mCommandArguments = commandArguments;
    this->mArgsCount = commandArguments.data == nullptr ? 0 : commandArguments.length;
    this->mCommand = command;
}
