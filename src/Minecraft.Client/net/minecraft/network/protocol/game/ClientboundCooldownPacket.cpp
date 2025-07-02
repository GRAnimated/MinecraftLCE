#include "net/minecraft/network/protocol/game/ClientboundCooldownPacket.h"
#include "net/minecraft/world/item/Item.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundCooldownPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundCooldownPacket());
}

ClientboundCooldownPacket::ClientboundCooldownPacket() {
    item = nullptr;
    cooldown = 0;
}

EPacketType ClientboundCooldownPacket::getPacketId() {
    return EPacketType::_ClientboundCooldownPacket;
}

void ClientboundCooldownPacket::read(DataInputStream* input) {
    item = Item::byId(input->readVarInt());
    cooldown = input->readVarInt();
}

void ClientboundCooldownPacket::write(DataOutputStream* output) {
    output->writeVarInt(item->getId());
    output->writeVarInt(cooldown);
}

// WHY does this one use a static pointer cast???
void ClientboundCooldownPacket::handle(PacketListener* listener) {
    listener->handleItemCooldown(std::static_pointer_cast<ClientboundCooldownPacket>(shared_from_this()));
}
