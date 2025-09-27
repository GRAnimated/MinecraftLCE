#include "ClientboundPreLoginPacket.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/SharedConstants.h"
#include "net/minecraft/client/CMinecraftApp.h"

std::shared_ptr<Packet> ClientboundPreLoginPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPreLoginPacket());
}

ClientboundPreLoginPacket::ClientboundPreLoginPacket() {
    this->mName = L"";
    this->mPlayers = nullptr;
    this->mPlayerCount = 0;
    this->mUnk1 = 0;
    this->mUnk2 = 0;
    this->mMapName = 0; // not to be confused with world name, which I don't think is written here
    this->mUnk3 = 0;
    this->mUnk4 = 0;
    this->mUnk5 = 0;
    this->mUnk6 = 0;
    this->mUnk7 = 0;
    this->mUnk8 = 0;
    this->mUnk9 = 0;
    this->mUnk10 = 0;
    this->mUnk11 = 0;
    this->mUnk12 = 0;
    this->mUnk13 = 0;
    this->mUnk14 = 0;
    this->mUnk15 = 0;
    this->mUnk16 = 0;
    this->mUnk17 = 0;
    this->mUnk18 = 0;
    this->mProtocolVersion = 0;
    this->mUnk19 = false;
    this->mUnk20 = 15;
}

EPacketType ClientboundPreLoginPacket::getPacketId() {
    return _ClientboundPreLoginPacket;
}

void ClientboundPreLoginPacket::read(DataInputStream* input) {
    this->mProtocolVersion = input->readShort();
    this->mName = this->readUtf(input, 0x20);
    this->mUnk1 = input->readByte();
    this->mUnk2 = input->readInt();

    this->mPlayerCount = input->readByte();
    if (this->mPlayerCount) {
        this->mPlayers = new PlayerUID[this->mPlayerCount]; // see note in PlayerUID

        for (int i = 0; i < this->mPlayerCount; i++) {
            this->mPlayers[i] = input->readPlayerUID();
        }
    }

    this->mMapName = input->readByte();
    this->mUnk3 = input->readByte();
    this->mUnk4 = input->readByte();
    this->mUnk5 = input->readByte();
    this->mUnk6 = input->readByte();
    this->mUnk7 = input->readByte();
    this->mUnk8 = input->readByte();
    this->mUnk9 = input->readByte();
    this->mUnk10 = input->readByte();
    this->mUnk11 = input->readByte();
    this->mUnk12 = input->readByte();
    this->mUnk13 = input->readByte();
    this->mUnk14 = input->readByte();
    this->mUnk15 = input->readByte();
    this->mUnk16 = input->readInt();
    this->mUnk17 = input->readByte();
    this->mUnk18 = input->readInt();
    this->mUnk19 = input->readBoolean();
    this->mUnk20 = input->readInt();
    CConsoleMinecraftApp::sInstance.SetUniqueMapName(&this->mMapName);
}

void ClientboundPreLoginPacket::write(DataOutputStream* output) {
    output->writeShort(SharedConstants::NETWORK_PROTOCOL_VERSION);
    this->writeUtf(this->mName, output);
    output->writeByte(this->mUnk1);
    output->writeInt(this->mUnk2);

    output->writeByte(this->mPlayerCount);
    for (int i = 0; i < this->mPlayerCount; i++) {
        output->writePlayerUID(this->mPlayers[i]);
    }

    output->writeByte(this->mMapName);
    output->writeByte(this->mUnk3);
    output->writeByte(this->mUnk4);
    output->writeByte(this->mUnk5);
    output->writeByte(this->mUnk6);
    output->writeByte(this->mUnk7);
    output->writeByte(this->mUnk8);
    output->writeByte(this->mUnk9);
    output->writeByte(this->mUnk10);
    output->writeByte(this->mUnk11);
    output->writeByte(this->mUnk12);
    output->writeByte(this->mUnk13);
    output->writeByte(this->mUnk14);
    output->writeByte(this->mUnk15);
    output->writeInt(this->mUnk16);
    output->writeByte(this->mUnk17);
    output->writeInt(this->mUnk18);
    output->writeBoolean(this->mUnk19);
    output->writeInt(this->mUnk20);
}
