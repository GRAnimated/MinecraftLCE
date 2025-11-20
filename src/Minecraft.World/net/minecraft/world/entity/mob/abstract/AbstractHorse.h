#pragma once

#include "net/minecraft/world/ContainerListener.h"
#include "net/minecraft/world/entity/OwnableEntity.h"
#include "net/minecraft/world/entity/mob/Animal.h"
#include "net/minecraft/world/entity/player/PlayerRideableJumping.h"

class AbstractHorse : public Animal,
                      public net_minecraft_world::ContainerListener,
                      public PlayerRideableJumping,
                      public OwnableEntity {};
