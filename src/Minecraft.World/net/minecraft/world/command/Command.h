#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/PlayerUID.h"
#include "net/minecraft/world/entity/CommandSender.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "types.h"
#include <memory>

class CommandSender;

class Command {
public:
    Command();

    static void logAdminAction(std::shared_ptr<CommandSender>, ClientboundChatPacket::EChatPacketMessage,
                               int*, unsigned int, std::wstring*, unsigned int);

    std::shared_ptr<Player> getPlayer(PlayerUID);

    virtual ~Command();
    virtual EGameCommand getId() = 0;
    virtual int getPermissionLevel();
    virtual void execute(std::shared_ptr<CommandSender>, arrayWithLength<uchar>) = 0;
    virtual bool canExecute(std::shared_ptr<CommandSender>);
};
