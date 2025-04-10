#pragma once
#include "types.h"
#include "Minecraft.World/phys/Vec3.h"
#include "Minecraft.Core/BlockPos.h"
#include <string>

class ClientboundChatPacket {
public:
    enum EChatPacketMessage {};
};
enum EGameCommand {};
class Level;
class CommandStats {
public:
    enum CommandStatType {};
};

class CommandSender {
public:
    virtual ~CommandSender();
    virtual void sendMessage(ClientboundChatPacket::EChatPacketMessage, int*, uint, std::wstring*, uint) = 0;
    virtual void hasPermission(EGameCommand) = 0;
    // according to symbol it should be getDisplayName buttt idk how to correctly do that shit so it
    // generates this and one in Entity VTable (later on)
    virtual std::wstring getNetworkName() = 0;
    virtual BlockPos getCommandSenderBlockPosition() = 0;
    virtual Vec3 getCommandSenderWorldPosition() = 0;
    virtual Level* getCommandSenderWorld() = 0;
    virtual void getCommandSenderEntity();
    virtual bool isSendMessageEnabled() = 0;
    virtual void setCommandStats(CommandStats::CommandStatType, int) = 0;
    virtual void getServer() = 0;
};