#pragma once

#include "net/minecraft/client/ui/scene/scenes/UIScene_CreativeMenu.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include "types.h"
#include <vector>

class ItemInstance;
class Item;
class Block;
class BlockState;

// most of the names/signatures are guessed beside: ITEM_BLOCKSTATE, ADD, ITEM_AUX
class MenuBuilder {
public:
    static std::vector<UIScene_CreativeMenu::ItemBuilder> ITEM_BUILDERS[15];

    void setCategory(UIScene_CreativeMenu::ECreative_Inventory_Groups category) {
        this->mContent = &ITEM_BUILDERS[category];
    }

    void ADD(const not_null_ptr<ItemInstance>& itemInstance);
    template <typename T>
    void ITEM_AUX(Block* block, const AbstractProperty<T>* property, T value) {
        const BlockState* state = block->defaultBlockState()->setValue((Property*)property, value);
        this->ITEM_BLOCKSTATE(state);
    }
    void ITEM(Item* item) { this->ADD(not_null_ptr<ItemInstance>(new ItemInstance(item, 1, 0))); }
    void ITEM(Item* item, int aux) { this->ADD(not_null_ptr<ItemInstance>(new ItemInstance(item, 1, aux))); }
    void ITEM_BLOCK(Block* block) { this->ITEM_BLOCKSTATE(block->defaultBlockState()); }
    void ITEM_BLOCK(Block* block, int data) {
        this->ADD(not_null_ptr<ItemInstance>(new ItemInstance(block, 1, data)));
    }
    void ITEM_BLOCKSTATE(const BlockState* state) {
        this->ITEM_BLOCK(state->getBlock(), state->getBlock()->convertBlockStateToLegacyData(state));
    }

    std::vector<UIScene_CreativeMenu::ItemBuilder>* mContent;
};
