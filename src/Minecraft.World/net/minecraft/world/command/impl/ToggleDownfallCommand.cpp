#include "net/minecraft/world/command/impl/ToggleDownfallCommand.h"
#include "net/minecraft/server/MinecraftServer.h"
#include "net/minecraft/server/ServerLevel.h"
#include "net/minecraft/world/command/Command.h"
#include "net/minecraft/world/command/EGameCommand.h"
#include "net/minecraft/world/entity/CommandSender.h"
#include "net/minecraft/world/level/storage/LevelData.h"
#include "types.h"
#include <memory>
#include <string>

ToggleDownfallCommand::ToggleDownfallCommand() : Command() {}

EGameCommand ToggleDownfallCommand::getId() {
    return eToggleDownfallCommand;
}

int ToggleDownfallCommand::getPermissionLevel() {
    return 2;
}

void toggleDownfall() {
  MinecraftServer* server = MinecraftServer::getInstance();
  ServerLevel* level = server->level;
  
  LevelData* data = level->getLevelData();

  bool isRaining = data->isRaining();
  data->setRaining(!isRaining);
  
  return;
}

void ToggleDownfallCommand::execute(std::shared_ptr<CommandSender> sender, arrayWithLength<uchar> input) {  
  toggleDownfall();

  std::wstring message;
  message += (L"commands.downfall.success");
  
  Command::logAdminAction(sender, (ClientboundChatPacket::EChatPacketMessage)0, 0, 0, &message, 1);
  return;
}
