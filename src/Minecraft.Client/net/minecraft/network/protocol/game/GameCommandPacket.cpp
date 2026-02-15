#include "net/minecraft/network/protocol/game/GameCommandPacket.h"

GameCommandPacket::GameCommandPacket(EGameCommand command, arrayWithLength<uchar> commandArguments) {
    this->m_commandArguments = commandArguments;
    this->m_argsCount = commandArguments.m_data == nullptr ? 0 : commandArguments.m_length;
    this->m_command = command;
}
