#include "types.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/entity/CommandSender.h"
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