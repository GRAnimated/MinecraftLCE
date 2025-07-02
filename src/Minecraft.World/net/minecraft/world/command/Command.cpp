#include "Minecraft.World/command/Command.h"
#include "Minecraft.World/entity/CommandSender.h"

Command::~Command() {}

int Command::getPermissionLevel() {
    return 4;
}

bool Command::canExecute(std::shared_ptr<CommandSender> sender) {
    if (this->getPermissionLevel() == 0)
        return true;
    return sender->hasPermission(this->getId());
}