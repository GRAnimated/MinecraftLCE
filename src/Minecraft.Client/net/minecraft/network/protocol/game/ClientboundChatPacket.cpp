#include "net/minecraft/network/protocol/game/ClientboundChatPacket.h"

void ClientboundChatPacket::read(DataInputStream* input) {
    this->mType = input->readShort();
    this->FlexiblePacket::read(input);
}
