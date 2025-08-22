#pragma once

#include "net/minecraft/client/resources/SimpleRegistry.h"
#include "net/minecraft/world/InteractionHand.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/entity/ai/attributes/AttributeModifier.h"
#include "net/minecraft/world/item/InteractionResultHolder.h"
#include "net/minecraft/world/item/ItemTooltipDataHolder.h"
#include "types.h"
#include <memory>
#include <string>
#include <unordered_map>

class ResourceLocation;
class Block;
class LivingEntity;
class ItemInstance;
class Level;
class Player;
class BlockState;
class CompoundTag;
class Entity;
class IconRegister;
class BlockPos;
class Direction;
class TextureAtlasSprite;

class ItemPropertyFunction {
public:
    virtual void call(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<LivingEntity>) = 0;
};

// Don't know if this exists, it exists on Java
enum ActionResultType { SUCCESS, PASS, FAIL };

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
    void addProperty(ResourceLocation, const ItemPropertyFunction*);
    int getId();
    bool canBeDepleted();
    std::wstring getIconName();
    void setIconName(const std::wstring&);
    void setMaxDamage(int);
    int getMaxDamage();
    void setStackedByData(bool);
    bool isStackedByData();

    static int VALIDgetId(Item*);

    static Item* byId(int id);
    static void registerBlock(Block* block);
    static void registerBlock(Block* block, Item*);
    static Item* byBlock(Block* block);
    static Item* byString(const std::wstring& string);
    static void registerItem(int id, const std::wstring& name_id, Item* item);
    static void registerItem(int id, const ResourceLocation& name_id, Item* item);

    virtual not_null_ptr<ItemInstance> getDefaultInstance();
    virtual bool verifyTagAfterLoad(CompoundTag* tag);
    virtual unsigned int GetUseTooltip(const ItemToolTipDataHolder& toolTipDataHolder);
    virtual ~Item() {}
    virtual ActionResultType useOn(std::shared_ptr<Player> user, Level* level, const BlockPos& pos,
                                   InteractionHand::EInteractionHand hand, const Direction* direction,
                                   float rayX, float rayY, float rayZ,
                                   bool missOrInside);  // it's either miss or inside (taken from mojmap)
    virtual float getDestroySpeed(not_null_ptr<ItemInstance> itemInstance, BlockState* state);
    virtual bool TestUse(Level* level, std::shared_ptr<Player> user, InteractionHand::EInteractionHand hand);
    virtual InteractionResultHolder use(Level* level, std::shared_ptr<Player> user,
                                        InteractionHand::EInteractionHand hand);
    virtual not_null_ptr<ItemInstance> finishUsingItem(not_null_ptr<ItemInstance> itemInstance, Level* level,
                                                       std::shared_ptr<LivingEntity> user);
    virtual int getMaxStackSize();
    virtual int getLevelDataForAuxValue(int auxValue);
    virtual bool hurtEnemy(not_null_ptr<ItemInstance> itemInstance, std::shared_ptr<LivingEntity> victim,
                           std::shared_ptr<LivingEntity> attacker);
    virtual bool mineBlock(not_null_ptr<ItemInstance> itemInstance, Level* level, const BlockState* state,
                           const BlockPos& pos, std::shared_ptr<LivingEntity> user);
    virtual int getAttackDamage(std::shared_ptr<Entity> entity);
    virtual bool canDestroySpecial(const BlockState* state);
    virtual bool interactEnemy(not_null_ptr<ItemInstance> itemInstance, std::shared_ptr<Player> user,
                               std::shared_ptr<LivingEntity> ent, InteractionHand::EInteractionHand);
    virtual bool isHandEquipped();
    virtual bool isMirroredArt();
    virtual unsigned int getDescriptionId(int auxValue);
    virtual unsigned int getDescriptionId(not_null_ptr<ItemInstance> itemInstance);
    virtual unsigned int getUseDescriptionId();
    virtual unsigned int getUseDescriptionId(not_null_ptr<ItemInstance> itemInstance);
    virtual bool shouldOverrideMultiplayerNBT();
    virtual int getColor(not_null_ptr<ItemInstance> itemInstance,
                         int auxValue);  // not sure about auxValue, pure guess
    virtual void inventoryTick(not_null_ptr<ItemInstance> itemInstance, Level* level,
                               std::shared_ptr<Entity> ent, int slot, bool inHand);
    virtual void onCraftedBy(not_null_ptr<ItemInstance> itemInstance, Level*, std::shared_ptr<Player> player);
    virtual bool isComplex();
    virtual int getUseAnimation(not_null_ptr<ItemInstance> itemInstance);
    virtual int getUseDuration(not_null_ptr<ItemInstance> itemInstance);
    virtual void releaseUsing(not_null_ptr<ItemInstance> itemInstance, Level* level,
                              std::shared_ptr<LivingEntity> livingEnt, int remainingTicks);
    virtual void appendHoverText(not_null_ptr<ItemInstance> itemInstance, std::shared_ptr<Player> player,
                                 void* htmlString, bool);
    virtual std::wstring getName(not_null_ptr<ItemInstance> itemInstance);
    virtual bool isFoil(not_null_ptr<ItemInstance> itemInstance);
    virtual void getRarity(not_null_ptr<ItemInstance> itemInstance);
    virtual bool isEnchantable(not_null_ptr<ItemInstance> itemInstance);
    virtual int getEnchantmentValue();
    virtual bool mayBePlacedInAdventureMode();
    virtual bool isValidRepairItem(not_null_ptr<ItemInstance> source, not_null_ptr<ItemInstance> repairItem);
    virtual std::unordered_map<eATTRIBUTE_ID, AttributeModifier*>*
    getDefaultAttributeModifiers(const EquipmentSlot* eqpSlot);
    virtual void registerIcons(IconRegister* iconRegister);
    virtual bool hasMultipleSpriteLayers();
    virtual TextureAtlasSprite* getLayerIcon(int, int);
    virtual int getIconType();
    virtual TextureAtlasSprite* getIcon(int auxValue);
    virtual TextureAtlasSprite* getIcon(not_null_ptr<ItemInstance> itemInstance);
    virtual int GetArmorType();
    virtual int GetOverrideCount();
    virtual int GetOverrideCountColour();
    virtual TextureAtlasSprite* GetOverrideCountIcon(not_null_ptr<ItemInstance> itemInstance);

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
