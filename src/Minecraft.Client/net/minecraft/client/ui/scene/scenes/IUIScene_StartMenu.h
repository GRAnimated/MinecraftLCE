#pragma once

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/scenes/partial/IUIPartial_OnlineRestricted.h"

class IUIScene_StartGame : public UIScene, virtual public IUIPartial_OnlineRestricted {};
