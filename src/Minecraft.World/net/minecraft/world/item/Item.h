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
            this->m_level = level;
            this->m_uses = uses;
            this->m_speed = speed;
            this->m_damage = damage;
            this->m_enchantmentValue = enchantmentValue;
            this->m_id = id;
        }

        int getLevel() const { return this->m_level; }
        int getUses() const { return this->m_uses; }
        float getSpeed() const { return this->m_speed; }
        float getAttackDamageBonus() const { return this->m_damage; }
        int getEnchantmentValue() const { return this->m_enchantmentValue; }
        Item* getTierItem() const;

    private:
        int m_level;
        int m_uses;
        float m_speed;
        float m_damage;
        int m_enchantmentValue;
        int m_id;  // pure guess
    };

    Item();
    void addProperty(ResourceLocation, const ItemPropertyFunction*);
    unsigned int getId();
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

    static void staticCtor();
    static void staticInit();

    void* m_qword8;
    SimpleRegistry<ResourceLocation, const ItemPropertyFunction*>* m_simpleRegistry;
    int m_maxStackSize;
    int m_maxDamage;
    TextureAtlasSprite* m_defaultIcon;
    int m_baseItemType;
    int m_material;
    bool m_handEquipped;
    bool m_stackedByData;
    void* m_craftingRemainingItem;
    std::wstring m_wstring1;
    int m_descriptionId;
    int m_useDescriptionId;
    std::wstring m_iconName;
    char m_byte78;  // probably bool but idk
};
