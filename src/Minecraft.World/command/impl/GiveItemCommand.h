#pragma once

#include "Minecraft.World/command/Command.h"
#include "Minecraft.World/entity/CommandSender.h"

class GiveItemCommand : public Command {
public:
    ~GiveItemCommand() override;
    EGameCommand getId() override;
    int getPermissionLevel() override;
    void execute(std::shared_ptr<CommandSender>, arrayWithLength<uchar>) override;
};