#include "net/minecraft/network/protocol/game/ClientboundChatPacket.h"

void ClientboundChatPacket::read(DataInputStream* input) {
    this->mType = static_cast<EChatPacketMessage>(input->readShort());
    this->FlexiblePacket::read(input);
}
