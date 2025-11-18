#pragma once

#include <memory>

template <typename T>
class not_null_ptr;

class ItemInstance;
class Container;
class Player;

class Slot {
public:
    Slot(std::shared_ptr<Container> container, int index, int x, int y);

    void onQuickCraft(not_null_ptr<ItemInstance> item, not_null_ptr<ItemInstance> item2);

    virtual ~Slot();
    virtual void onQuickCraft(not_null_ptr<ItemInstance> item, int count);
    virtual void onSwapCraft(int count);
    virtual void checkTakeAchievements(not_null_ptr<ItemInstance> item);
    virtual not_null_ptr<ItemInstance> onTake(std::shared_ptr<Player> player,
                                              not_null_ptr<ItemInstance> item);
    virtual bool mayPlace(not_null_ptr<ItemInstance> item);
    virtual not_null_ptr<ItemInstance> getItem();
    virtual bool hasItem();
    virtual void set(not_null_ptr<ItemInstance> item);
    virtual void setChanged();
    virtual int getMaxStackSize();
    virtual int getMaxStackSize(not_null_ptr<ItemInstance> item);
    virtual std::wstring getNoItemIcon();
    virtual not_null_ptr<ItemInstance> remove(int count);
    virtual bool isAt(std::shared_ptr<Container> container, int index);
    virtual bool mayPickup(std::shared_ptr<Player> player);
    virtual bool isActive();
    virtual bool mayCombine(not_null_ptr<ItemInstance> item);
    virtual void combine(not_null_ptr<ItemInstance> item);

    int mSlot = 0;
    std::shared_ptr<Container> mContainer = nullptr;
    int mIndex = 0;
    int mX = 0;
    int mY = 0;
};
