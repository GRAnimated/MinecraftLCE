#pragma once

#include "types.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/entity/CommandSender.h"
#include <memory>

class CommandSender;

class Command {
public:
    Command();

    virtual ~Command();
    virtual EGameCommand getId() = 0;
    virtual int getPermissionLevel();
    virtual void execute(std::shared_ptr<CommandSender>, arrayWithLength<uchar>) = 0;
    virtual bool canExecute(std::shared_ptr<CommandSender>);
};
