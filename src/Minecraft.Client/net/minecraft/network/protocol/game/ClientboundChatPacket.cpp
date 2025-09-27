#include "ClientboundChatPacket.h"

void ClientboundChatPacket::read(DataInputStream* input) {
    this->mType = input->readShort();
    this->FlexiblePacket::read(input);
}