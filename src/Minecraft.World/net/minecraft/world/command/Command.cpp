#include "net/minecraft/world/command/Command.h"
#include "net/minecraft/world/entity/CommandSender.h"

Command::~Command() {}

int Command::getPermissionLevel() {
    return 4;
}

bool Command::canExecute(std::shared_ptr<CommandSender> sender) {
    if (this->getPermissionLevel() == 0)
        return true;
    return sender->hasPermission(this->getId());
}
