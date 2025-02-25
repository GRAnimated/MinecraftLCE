#pragma once

#include "types.h"
#include "Minecraft.World/InteractionHand.h"

#include <memory>
#include <string>

class Block;
class BlockState;
class BlockPos;
class CompoundTag;
class DataFixerUpper;
class Direction;
class Enchantment;
class EquipmentSlot;
class Item;
class ItemFrame;
class Level;
class LivingEntity;
class Player;
class Random;
class Tag;

class ItemInstance {
public:
    bool isEmpty() const;
    int getCount();
    void updateEmptyCacheFlag();
    void setCount(int);
    Item* getItem() const;
    ~ItemInstance();
    void _init(Item*, int, int);
    ItemInstance(Block*);
    ItemInstance(Block*, int);
    ItemInstance(Block*, int, int);
    ItemInstance(Item*);
    ItemInstance(Item*, int);
    ItemInstance(Item*, int, int);
    ItemInstance(CompoundTag*);
    static void addDataWalkers(DataFixerUpper*);
    void copy() const;
    void grow(int);
    void shrink(int);
    void split(int);
    void useOn(std::shared_ptr<Player>, Level*, BlockPos const&, InteractionHand::EInteractionHand, Direction const*, float, float, float, bool);
    void getDestroySpeed(BlockState const*);
    void TestUse(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand);
    void use(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand);
    void finishUsingItem(Level*, std::shared_ptr<Player>);
    void save(CompoundTag*);
    void getMaxStackSize();
    void hasTag();
    void getTag();
    bool isDamageableItem();
    bool isDamaged();
    bool isStackable();
    bool isStackedByData();
    void getDamageValue();
    void getAuxValue() const;
    void setAuxValue(int);
    void getMaxDamage();
    void hurt(int, Random*);
    void hurtAndBreak(int, std::shared_ptr<LivingEntity>);
    void hurtEnemy(std::shared_ptr<LivingEntity>, std::shared_ptr<Player>);
    void mineBlock(Level*, BlockState const*, BlockPos const&, std::shared_ptr<Player>);
    void canDestroySpecial(BlockState const*);
    void interactEnemy(std::shared_ptr<Player>, std::shared_ptr<LivingEntity>, InteractionHand::EInteractionHand);
    void copy_not_shared() const;
    static void tagMatches(not_null_ptr<ItemInstance> const&, not_null_ptr<ItemInstance> const&);
    void matches(not_null_ptr<ItemInstance> const&, bool);
    static void matches(not_null_ptr<ItemInstance> const&, not_null_ptr<ItemInstance> const&, bool);
    void sameItem(not_null_ptr<ItemInstance> const&);
    static bool isSame(not_null_ptr<ItemInstance> const&, not_null_ptr<ItemInstance> const&);
    void sameItemIgnoreDurability(not_null_ptr<ItemInstance> const&);
    static bool isSameIgnoreDurability(not_null_ptr<ItemInstance> const&, not_null_ptr<ItemInstance> const&);
    void sameItemWithTags(not_null_ptr<ItemInstance> const&, std::vector<std::wstring>*);
    void sameItem_not_shared(ItemInstance*);
    void getUseDescriptionId();
    void getDescriptionId(int);
    void toString();
    void inventoryTick(Level*, std::shared_ptr<Entity>, int, bool);
    void onCraftedBy(Level*, std::shared_ptr<Player>, int);
    void getUseDuration();
    void getUseAnimation() const;
    void releaseUsing(Level*, std::shared_ptr<LivingEntity>, int);
    void setTag(CompoundTag*);
    void addTagElement(std::wstring, Tag*);
    void getOrCreateTagElement(std::wstring const&);
    void getTagElement(std::wstring const&);
    void getEnchantmentTags();
    void wasCreatedByRestrictedPlayer();
    void getHoverNameUnfiltered();
    void getHoverName();
    void setTranslatableName(int);
    void setHoverName(std::wstring const&);
    void setCensorshipInfo(std::wstring const&, bool);
    void getOwnerUUID();
    void wasCreatedOnHost();
    void resetHoverName();
    void hasCustomHoverName();
    void getAttributeModifiers(EquipmentSlot const*);
    void getTooltipLines(std::shared_ptr<Player>, bool);
    void getHoverTextOnly(std::shared_ptr<Player>, bool);
    void hasFoil();
    void getRarity();
    bool isEnchanted();
    bool isEnchantable();
    void enchant(Enchantment*, int);
    void mayBePlacedInAdventureMode();
    bool isFramed();
    void setFramed(std::shared_ptr<ItemFrame>);
    void getFrame();
    void getBaseRepairCost();
    void setRepairCost(int);
    void hasAdventureModeBreakTagForBlock(Block*);
    void hasAdventureModePlaceTagForBlock(Block*);
    void getPopTime() const;
    void setPopTime(int);
    void set4JData(int);
    void get4JData();
    void hasPotionStrengthBar();
    void GetPotionStrength();

    bool operator=(ItemInstance const&);

private:
    void* qword_0;
    void* qword_8;
    int mCount;
    int dword_14;
    void* mItem;
    void* qword_20;
    bool mIsEmpty;
    int dword_2c;
    bool byte_30;
    void* qword_38;
    void* qword_40;
    void* qword_48;
    void* qword_50;
    void* qword_58;
    bool byte_60;
};
