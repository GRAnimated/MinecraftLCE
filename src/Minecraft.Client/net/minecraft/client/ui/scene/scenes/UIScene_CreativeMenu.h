#pragma once

#include "net/minecraft/client/ui/scene/scenes/UIScene_AbstractContainerMenu.h"

class UIScene_CreativeMenu : UIScene_AbstractContainerMenu {
public:
    enum ECreative_Inventory_Groups : int {
        Structures,
        Decoration,
        RedstoneAndTransport,
        Materials,
        Food,
        Tools,
        Misc
    };

    class ItemBuilder {
        virtual void crazyFunc();
    };
    class TabSpec {
    public:
        TabSpec(const wchar_t*, int, int, UIScene_CreativeMenu::ECreative_Inventory_Groups*, int,
                UIScene_CreativeMenu::ECreative_Inventory_Groups*, int,
                UIScene_CreativeMenu::ECreative_Inventory_Groups*);
    };

    static void staticCtor();
    static void nullsub_728() {}  // no idea, not present/inlined on WiiU
};
