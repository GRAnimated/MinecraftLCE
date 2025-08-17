#pragma once

#include "net/minecraft/world/command/Command.h"
#include "net/minecraft/world/entity/CommandSender.h"

class GiveItemCommand : public Command {
public:
    GiveItemCommand();

    //~GiveItemCommand() override;
    EGameCommand getId() override;
    int getPermissionLevel() override;
    void execute(std::shared_ptr<CommandSender>, arrayWithLength<uchar>) override;
};
