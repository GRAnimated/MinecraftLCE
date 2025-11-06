#pragma once

#include "net/minecraft/world/command/Command.h"
#include "net/minecraft/world/entity/CommandSender.h"

class ToggleDownfallCommand : public Command {
public:
    ToggleDownfallCommand();

    EGameCommand getId() override;
    int getPermissionLevel() override;
    void execute(std::shared_ptr<CommandSender>, arrayWithLength<uchar>) override;
};
