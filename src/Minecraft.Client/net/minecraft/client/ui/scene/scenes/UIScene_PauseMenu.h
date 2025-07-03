#pragma once

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/core/storage/C4JStorage.h"
enum EOpenExitGameDialog {};

class UIScene_PauseMenu : public UIScene {
public:
    static void OpenExitGameDialog(int, void*, void (*)(void*, int, C4JStorage::EMessageResult),
                                   void (*)(void*, int, C4JStorage::EMessageResult), EOpenExitGameDialog);
    static void ExitGameDialogReturned(void*, int, C4JStorage::EMessageResult);
    static void ExitGameSaveDialogReturned(void*, int, C4JStorage::EMessageResult);
};
