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
class CensoredString;

class ItemInstance {
public:
    static not_null_ptr<ItemInstance> EMPTY;

    bool isEmpty() const;
    int getCount();
    void updateEmptyCacheFlag();
    void setCount(int);
    Item* getItem() const;
    ~ItemInstance();
    void init(Item* item, int count, int aux);
    ItemInstance(Block*);
    ItemInstance(Block*, int);
    ItemInstance(Block*, int, int);
    ItemInstance(Item*);
    ItemInstance(Item*, int);
    ItemInstance(Item*, int, int);
    ItemInstance(CompoundTag*);
    static void addDataWalkers(DataFixerUpper*);
    not_null_ptr<ItemInstance> copy() const;
    void grow(int);
    void shrink(int);
    void split(int);
    void useOn(std::shared_ptr<Player>, Level*, const BlockPos&, InteractionHand::EInteractionHand,
               const Direction*, float, float, float, bool);
    void getDestroySpeed(BlockState const*);
    void TestUse(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand);
    void use(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand);
    void finishUsingItem(Level*, std::shared_ptr<Player>);
    CompoundTag* save(CompoundTag*);
    void getMaxStackSize();
    bool hasTag();
    CompoundTag* getTag();
    bool isDamageableItem();
    bool isDamaged();
    bool isStackable();
    bool isStackedByData();
    int getDamageValue();
    void getAuxValue() const;
    void setAuxValue(int);
    int getMaxDamage();
    void hurt(int, Random*);
    void hurtAndBreak(int, std::shared_ptr<LivingEntity>);
    void hurtEnemy(std::shared_ptr<LivingEntity>, std::shared_ptr<Player>);
    void mineBlock(Level*, BlockState const*, const BlockPos&, std::shared_ptr<Player>);
    void canDestroySpecial(BlockState const*);
    void interactEnemy(std::shared_ptr<Player>, std::shared_ptr<LivingEntity>,
                       InteractionHand::EInteractionHand);
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
    int getUseDuration();
    void getUseAnimation() const;
    void releaseUsing(Level*, std::shared_ptr<LivingEntity>, int);
    void setTag(CompoundTag*);
    void addTagElement(std::wstring, Tag*);
    void getOrCreateTagElement(const std::wstring&);
    void getTagElement(const std::wstring&);
    void getEnchantmentTags();
    void wasCreatedByRestrictedPlayer();
    void getHoverNameUnfiltered();
    void getHoverName();
    void setTranslatableName(int);
    void setHoverName(const std::wstring&);
    void setCensorshipInfo(const std::wstring&, bool);
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

    bool operator=(const ItemInstance&);

private:
    void* qword_0 = nullptr;
    void* qword_8 = nullptr;
    int mCount;
    int dword_14;
    Item* mItem;
    CompoundTag* mTag;
    bool mIsEmpty;
    int mDamage;
    bool byte_30;
    void* qword_38 = nullptr;
    void* qword_40 = nullptr;
    std::shared_ptr<CensoredString*> mCensoredString;
    void* qword_58;
    bool byte_60;
    void* qword_68;
    void* qword_70;
};
