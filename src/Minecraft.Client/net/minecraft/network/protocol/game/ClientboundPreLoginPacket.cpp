#include "net/minecraft/network/protocol/game/ClientboundPreLoginPacket.h"

#include "java/io/DataOutputStream.h"
#include "net/minecraft/SharedConstants.h"
#include "net/minecraft/client/CMinecraftApp.h"

std::shared_ptr<Packet> ClientboundPreLoginPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPreLoginPacket());
}

// NON_MATCHING | Score: 1110 (lower is better)
// Can't get it to emit memset over sturh spam
ClientboundPreLoginPacket::ClientboundPreLoginPacket() {
    this->m_name = L"";
    this->m_players = nullptr;
    this->m_playerCount = 0;
    this->m_unk1 = 0;
    this->m_unk2 = 0;
    this->m_mapName = 0;  // not to be confused with world name, which I don't think is written here
    this->m_unk3 = 0;
    this->m_unk4 = 0;
    this->m_unk5 = 0;
    this->m_unk6 = 0;
    this->m_unk7 = 0;
    this->m_unk8 = 0;
    this->m_unk9 = 0;
    this->m_unk10 = 0;
    this->m_unk11 = 0;
    this->m_unk12 = 0;
    this->m_unk13 = 0;
    this->m_unk14 = 0;
    this->m_unk15 = 0;
    this->m_unk16 = 0;
    this->m_unk17 = 0;
    this->m_unk18 = 0;
    this->m_protocolVersion = 0;
    this->m_unk19 = false;
    this->m_unk20 = 15;
}

EPacketType ClientboundPreLoginPacket::getPacketId() {
    return _ClientboundPreLoginPacket;
}

// NON_MATCHING | Score: 1115 (lower is better)
// Just a few mismatched instructions
void ClientboundPreLoginPacket::read(DataInputStream* input) {
    this->m_protocolVersion = input->readShort();
    this->m_name = ClientboundPreLoginPacket::readUtf(input, 0x20);
    this->m_unk1 = input->readByte();
    this->m_unk2 = input->readInt();

    this->m_playerCount = input->readByte();
    if (this->m_playerCount) {
        this->m_players = new PlayerUID[this->m_playerCount];  // see note in PlayerUID

        for (int i = 0; i < this->m_playerCount; i++) {
            this->m_players[i] = input->readPlayerUID();
        }
    }

    this->m_mapName = input->readByte();
    this->m_unk3 = input->readByte();
    this->m_unk4 = input->readByte();
    this->m_unk5 = input->readByte();
    this->m_unk6 = input->readByte();
    this->m_unk7 = input->readByte();
    this->m_unk8 = input->readByte();
    this->m_unk9 = input->readByte();
    this->m_unk10 = input->readByte();
    this->m_unk11 = input->readByte();
    this->m_unk12 = input->readByte();
    this->m_unk13 = input->readByte();
    this->m_unk14 = input->readByte();
    this->m_unk15 = input->readByte();
    this->m_unk16 = input->readInt();
    this->m_unk17 = input->readByte();
    this->m_unk18 = input->readInt();
    this->m_unk19 = input->readBoolean();
    this->m_unk20 = input->readInt();
    CConsoleMinecraftApp::sInstance.SetUniqueMapName(&this->m_mapName);
}

// NON_MATCHING | Score: 1466 (lower is better)
// Again just a few mismatched instructions
void ClientboundPreLoginPacket::write(DataOutputStream* output) {
    output->writeShort(SharedConstants::NETWORK_PROTOCOL_VERSION);
    this->writeUtf(this->m_name, output);
    output->writeByte(this->m_unk1);
    output->writeInt(this->m_unk2);

    output->writeByte(this->m_playerCount);
    for (int i = 0; i < this->m_playerCount; i++) {
        output->writePlayerUID(this->m_players[i]);
    }

    output->writeByte(this->m_mapName);
    output->writeByte(this->m_unk3);
    output->writeByte(this->m_unk4);
    output->writeByte(this->m_unk5);
    output->writeByte(this->m_unk6);
    output->writeByte(this->m_unk7);
    output->writeByte(this->m_unk8);
    output->writeByte(this->m_unk9);
    output->writeByte(this->m_unk10);
    output->writeByte(this->m_unk11);
    output->writeByte(this->m_unk12);
    output->writeByte(this->m_unk13);
    output->writeByte(this->m_unk14);
    output->writeByte(this->m_unk15);
    output->writeInt(this->m_unk16);
    output->writeByte(this->m_unk17);
    output->writeInt(this->m_unk18);
    output->writeBoolean(this->m_unk19);
    output->writeInt(this->m_unk20);
}
