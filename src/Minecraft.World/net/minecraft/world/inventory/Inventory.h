#pragma once

#include "net/minecraft/core/NonNullList.h"
#include "net/minecraft/world/Container.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "types.h"

class ListTag;

class Inventory : public Container {
public:
    explicit Inventory(Player*);
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    const not_null_ptr<ItemInstance>& getSelected();
    static bool isHotbarSlot(int);
    static int getSelectionSize();
    void swapPaint(int);
    bool add(not_null_ptr<ItemInstance>);
    bool add(int, not_null_ptr<ItemInstance>);
    bool hasResource(Item*);
    int getFreeSlot();
    int getSlotWithRemainingSpace(not_null_ptr<ItemInstance>);
    bool hasRemainingSpaceForItem(not_null_ptr<ItemInstance>, not_null_ptr<ItemInstance>, bool);
    bool isSameItem(not_null_ptr<ItemInstance>, not_null_ptr<ItemInstance>, bool);
    int addResource(not_null_ptr<ItemInstance>);
    int addResource(int, not_null_ptr<ItemInstance>);
    void removeItem(not_null_ptr<ItemInstance>);
    not_null_ptr<ItemInstance> getArmor(int);
    void setCarried(not_null_ptr<ItemInstance>);
    not_null_ptr<ItemInstance> getCarried();
    ListTag* save(ListTag*);
    void load(ListTag*);

    std::wstring getName() override;
    std::wstring getCustomName() override;
    bool hasCustomName() override;
    std::wstring getDisplayName() override;
    ~Inventory() override;
    int getContainerSize() override;
    bool isEmpty() override;
    not_null_ptr<ItemInstance> getItem(unsigned int) override;
    not_null_ptr<ItemInstance> removeItem(unsigned int, int) override;
    not_null_ptr<ItemInstance> removeItemNoUpdate(int) override;
    void setItem(unsigned int, not_null_ptr<ItemInstance>) override;
    int getMaxStackSize() override;
    void setChanged() override;
    bool stillValid(std::shared_ptr<Player>) override;
    void startOpen(std::shared_ptr<Player>) override;
    void stopOpen(std::shared_ptr<Player>) override;
    bool canPlaceItem(int, not_null_ptr<ItemInstance>) override;
    int getContainerData(int) override;
    void setContainerData(int, int) override;
    int getContainerDataCount() override;
    void clearContent() override;

    NonNullList<not_null_ptr<ItemInstance>> m_items;
    NonNullList<not_null_ptr<ItemInstance>> m_armor;
    NonNullList<not_null_ptr<ItemInstance>> m_offhand;
    NonNullList<not_null_ptr<ItemInstance>> m_itemsView;
    NonNullList<not_null_ptr<ItemInstance>> m_armorView;
    NonNullList<not_null_ptr<ItemInstance>> m_offhandView;
    bool m_selectionChanged;
    int m_selected;
    Player* m_player;
    not_null_ptr<ItemInstance> m_lastSelected;
    not_null_ptr<ItemInstance> m_carried;
    int m_timesChanged;

private:
    NonNullList<not_null_ptr<ItemInstance>> getSlotList(unsigned int&);
};

ASSERT_SIZEOF(Inventory, 0x100)
