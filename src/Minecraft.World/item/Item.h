#pragma once
#include "types.h"
#include "Minecraft.Client/resources/SimpleRegistry.h"
#include "Minecraft.World/InteractionHand.h"
#include "Minecraft.World/inventory/EquipmentSlot.h"
#include "Minecraft.World/item/InteractionResultHolder.h"
#include <memory>
#include <string>

class ResourceLocation;
class Block;
class LivingEntity;
class ItemInstance;
class Level;
class Player;
class BlockState;
class CompoundTag;
class ItemToolTipDataHolder {
public:
    char gap0[24];
    int idk;
};
class Entity;
class IconRegister;
class BlockPos;
class Direction;
class TextureAtlasSprite;

class ItemPropertyFunction {
public:
    virtual void call(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<LivingEntity>);
};

class Item {
public:
    class Tier {
    public:
        static const Tier* WOOD;
        static const Tier* STONE;
        static const Tier* IRON;
        static const Tier* DIAMOND;
        static const Tier* GOLD;

        Tier(int level, int uses, float speed, float damage, int enchantmentValue, int id) {
            this->mLevel = level;
            this->mUses = uses;
            this->mSpeed = speed;
            this->mDamage = damage;
            this->mEnchantmentValue = enchantmentValue;
            this->mId = id;
        }

        int getLevel() const { return this->mLevel; }

        int getUses() const { return this->mUses; }

        float getSpeed() const { return this->mSpeed; }

        float getAttackDamageBonus() const { return this->mDamage; }

        int getEnchantmentValue() const { return this->mEnchantmentValue; }

        Item* getTierItem() const;

    private:
        int mLevel;
        int mUses;
        float mSpeed;
        float mDamage;
        int mEnchantmentValue;
        int mId;  // pure guess
    };

    Item();
    void addProperty(ResourceLocation, ItemPropertyFunction const*);
    int getId();
    bool canBeDepleted();
    void setIconName(const std::wstring&);
    void setMaxDamage(int);
    int getMaxDamage();

    static Item* byId(int id);
    static void registerBlock(Block* block);
    static void registerBlock(Block* block, Item*);
    static Item* byBlock(Block* block);
    static Item* byString(const std::wstring& string);
    static void registerItem(int id, const std::wstring& name_id, Item* item);
    static void registerItem(int id, const ResourceLocation& name_id, Item* item);

    virtual not_null_ptr<ItemInstance> getDefaultInstance();
    virtual bool verifyTagAfterLoad(CompoundTag*);
    virtual int GetUseTooltip(const ItemToolTipDataHolder&);
    virtual ~Item();
    virtual bool useOn(std::shared_ptr<Player>, Level*, const BlockPos&, InteractionHand::EInteractionHand,
                       const Direction*, float, float, float, bool);
    virtual float getDestroySpeed(not_null_ptr<ItemInstance>, BlockState*);
    virtual bool TestUse(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand);
    virtual InteractionResultHolder use(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand);
    virtual not_null_ptr<ItemInstance> finishUsingItem(not_null_ptr<ItemInstance>, Level*,
                                                       std::shared_ptr<LivingEntity>);
    virtual int getMaxStackSize();
    virtual int getLevelDataForAuxValue(int);
    virtual bool hurtEnemy(not_null_ptr<ItemInstance>, std::shared_ptr<LivingEntity>,
                           std::shared_ptr<LivingEntity>);
    virtual bool mineBlock(not_null_ptr<ItemInstance>, Level*, const BlockState*, const BlockPos&,
                           std::shared_ptr<LivingEntity>);
    virtual int getAttackDamage(std::shared_ptr<Entity>);
    virtual bool canDestroySpecial(const BlockState*);
    virtual bool interactEnemy(not_null_ptr<ItemInstance>, std::shared_ptr<Player>,
                               std::shared_ptr<LivingEntity>, InteractionHand::EInteractionHand);
    virtual bool isHandEquipped();
    virtual bool isMirroredArt();
    virtual int getDescriptionId(int);
    virtual int getDescriptionId(not_null_ptr<ItemInstance>);
    virtual int getUseDescriptionId();
    virtual int getUseDescriptionId(not_null_ptr<ItemInstance>);
    virtual bool shouldOverrideMultiplayerNBT();
    virtual int getColor(not_null_ptr<ItemInstance>, int);
    virtual void inventoryTick(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<Entity>, int, bool);
    virtual void onCraftedBy(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<Player>);
    virtual bool isComplex();
    virtual int getUseAnimation(not_null_ptr<ItemInstance>);
    virtual int getUseDuration(not_null_ptr<ItemInstance>);
    virtual void releaseUsing(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<LivingEntity>, int);
    virtual void appendHoverText(not_null_ptr<ItemInstance>, std::shared_ptr<Player>, void* htmlString, bool);
    virtual std::wstring getName(not_null_ptr<ItemInstance>);
    virtual bool isFoil(not_null_ptr<ItemInstance>);
    virtual void getRarity(not_null_ptr<ItemInstance>);
    virtual bool isEnchantable(not_null_ptr<ItemInstance>);
    virtual int getEnchantmentValue();
    virtual bool mayBePlacedInAdventureMode();
    virtual bool isValidRepairItem(not_null_ptr<ItemInstance> source, not_null_ptr<ItemInstance> repairItem);
    virtual void getDefaultAttributeModifiers(const EquipmentSlot*);
    virtual void registerIcons(IconRegister*);
    virtual bool hasMultipleSpriteLayers();
    virtual TextureAtlasSprite* getLayerIcon(int, int, not_null_ptr<ItemInstance>);
    virtual int getIconType();
    virtual TextureAtlasSprite* getIcon(int);
    virtual TextureAtlasSprite* getIcon(not_null_ptr<ItemInstance>);
    virtual int GetArmorType();
    virtual int GetOverrideCount();
    virtual int GetOverrideCountColour();
    virtual TextureAtlasSprite* GetOverrideCountIcon(not_null_ptr<ItemInstance>);

    void* qword8;
    SimpleRegistry<ResourceLocation, const ItemPropertyFunction*>* mSimpleRegistry;
    int mMaxStackSize;
    int mMaxDamage;
    TextureAtlasSprite* mDefaultIcon;
    int mBaseItemType;
    int mMaterial;
    bool mHandEquipped;
    bool mStackedByData;
    void* mCraftingRemainingItem;
    std::wstring wstring_1;
    int mDescriptionId;
    int mUseDescriptionId;
    std::wstring mIconName;
    char byte78;  // probably bool but idk
};