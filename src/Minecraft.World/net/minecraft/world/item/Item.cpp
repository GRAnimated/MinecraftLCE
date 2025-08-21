#include "net/minecraft/world/item/Item.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/item/BlockItem.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "types.h"
#include <memory>
#include <unordered_map>

#include "net/minecraft/client/resources/MappedRegistry.h"

// should be replaced with proper ones later on
// even though those are unused
const ItemPropertyFunction* lefthandedFunction = nullptr;
const ItemPropertyFunction* cooldownFunction = nullptr;

extern std::unordered_map<Block*, Item*> blocksMap;

const Item::Tier* Item::Tier::WOOD = new Item::Tier(0, 59, 2.0, 0.0, 15, 0);
const Item::Tier* Item::Tier::STONE = new Item::Tier(1, 131, 4.0, 1.0, 5, 1);
const Item::Tier* Item::Tier::IRON = new Item::Tier(2, 250, 6.0, 2.0, 14, 2);
const Item::Tier* Item::Tier::DIAMOND = new Item::Tier(3, 1561, 8.0, 3.0, 10, 3);
const Item::Tier* Item::Tier::GOLD = new Item::Tier(0, 32, 12.0, 0.0, 22, 4);

Item::Item() {
    this->mMaxStackSize = 64;
    this->mMaxDamage = 0;
    this->mHandEquipped = false;
    this->mStackedByData = 0;
    this->mCraftingRemainingItem = nullptr;
    this->wstring_1 = L"";
    this->mBaseItemType = 0;
    this->mMaterial = 0;
    this->mIconName = L"";
    this->mDefaultIcon = nullptr;
    this->byte78 = 0;

    this->mSimpleRegistry = new SimpleRegistry<ResourceLocation, const ItemPropertyFunction*>();

    this->addProperty(ResourceLocation(L"lefthanded"), lefthandedFunction);

    this->addProperty(ResourceLocation(L"cooldown"), cooldownFunction);
}

void Item::registerBlock(Block* block) {
    Item::registerBlock(block, new BlockItem(block));
}

void Item::registerBlock(Block* block, Item* item) {
    Item::registerItem(block->getId(), Blocks::Registry->getKey(block), item);
    blocksMap[block] = item;
}

bool Item::canBeDepleted() {
    return this->mMaxDamage > 0 && (!this->mStackedByData || this->mMaxStackSize == 1);
}

void Item::setIconName(const std::wstring& iconName) {
    this->mIconName = iconName;
}

not_null_ptr<ItemInstance> Item::getDefaultInstance() {
    return new ItemInstance(this);
}

bool Item::verifyTagAfterLoad(CompoundTag*) {
    return false;
}

unsigned int Item::GetUseTooltip(const ItemToolTipDataHolder&) {
    return -1;
}

ActionResultType Item::useOn(std::shared_ptr<Player>, Level*, const BlockPos&,
                             InteractionHand::EInteractionHand, const Direction*, float, float, float, bool) {
    return ActionResultType::PASS;
}

float Item::getDestroySpeed(not_null_ptr<ItemInstance>, BlockState*) {
    return 1.0f;
}

bool Item::TestUse(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand) {
    return false;
}

InteractionResultHolder Item::use(Level*, std::shared_ptr<Player> player,
                                  InteractionHand::EInteractionHand hand) {
    return InteractionResultHolder(InteractionResult::PASS, player->getItemInHand(hand));
}

not_null_ptr<ItemInstance> Item::finishUsingItem(not_null_ptr<ItemInstance> item, Level*,
                                                 std::shared_ptr<LivingEntity>) {
    return item;
}

int Item::getMaxStackSize() {
    return this->mMaxStackSize;
}

int Item::getLevelDataForAuxValue(int) {
    return 0;
}

bool Item::hurtEnemy(not_null_ptr<ItemInstance>, std::shared_ptr<LivingEntity>,
                     std::shared_ptr<LivingEntity>) {
    return false;
}

bool Item::mineBlock(not_null_ptr<ItemInstance>, Level*, const BlockState*, const BlockPos&,
                     std::shared_ptr<LivingEntity>) {
    return false;
}

int Item::getAttackDamage(std::shared_ptr<Entity>) {
    return 1;
}

bool Item::canDestroySpecial(const BlockState*) {
    return false;
}

bool Item::interactEnemy(not_null_ptr<ItemInstance>, std::shared_ptr<Player>, std::shared_ptr<LivingEntity>,
                         InteractionHand::EInteractionHand) {
    return false;
}

bool Item::isHandEquipped() {
    return this->mHandEquipped;
}

bool Item::isMirroredArt() {
    return false;
}

unsigned int Item::getDescriptionId(int) {
    return this->mDescriptionId;
}

unsigned int Item::getDescriptionId(not_null_ptr<ItemInstance>) {
    return this->mDescriptionId;
}

unsigned int Item::getUseDescriptionId() {
    return this->mUseDescriptionId;
}

unsigned int Item::getUseDescriptionId(not_null_ptr<ItemInstance>) {
    return this->mUseDescriptionId;
}

bool Item::shouldOverrideMultiplayerNBT() {
    return true;
}

int Item::getColor(not_null_ptr<ItemInstance>, int) {
    return 0xFFFFFF;
}

void Item::inventoryTick(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<Entity>, int, bool) {}

void Item::onCraftedBy(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<Player>) {}

bool Item::isComplex() {
    return false;
}

int Item::getUseAnimation(not_null_ptr<ItemInstance>) {
    return 0;
}

int Item::getUseDuration(not_null_ptr<ItemInstance>) {
    return 0;
}

void Item::releaseUsing(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<LivingEntity>, int) {}

void Item::appendHoverText(not_null_ptr<ItemInstance>, std::shared_ptr<Player>, void* htmlString, bool) {}

bool Item::isFoil(not_null_ptr<ItemInstance> itemInstance) {
    return itemInstance->isEnchanted();
}

bool Item::isEnchantable(not_null_ptr<ItemInstance> a1) {
    return this->getMaxStackSize() == 1 && this->canBeDepleted();
}

int Item::getEnchantmentValue() {
    return 0;
}

bool Item::mayBePlacedInAdventureMode() {
    return true;
}

bool Item::isValidRepairItem(not_null_ptr<ItemInstance>, not_null_ptr<ItemInstance>) {
    return false;
}

std::unordered_map<eATTRIBUTE_ID, AttributeModifier*>*
Item::getDefaultAttributeModifiers(const EquipmentSlot*) {
    return new std::unordered_map<eATTRIBUTE_ID, AttributeModifier*>();
}

void Item::registerIcons(IconRegister* iconRegister) {
    this->mDefaultIcon = iconRegister->registerIcon(this->mIconName);
}

bool Item::hasMultipleSpriteLayers() {
    return false;
}

TextureAtlasSprite* Item::getLayerIcon(int a2, int) {
    return this->getIcon(a2);
}

int Item::getIconType() {
    return 1;
}

TextureAtlasSprite* Item::getIcon(int) {
    return this->mDefaultIcon;
}

TextureAtlasSprite* Item::getIcon(not_null_ptr<ItemInstance> item) {
    return this->getIcon(item->getAuxValue());
}

int Item::GetArmorType() {
    return 0;
}

int Item::GetOverrideCount() {
    return -1;
}

int Item::GetOverrideCountColour() {
    return -1;
}

TextureAtlasSprite* Item::GetOverrideCountIcon(not_null_ptr<ItemInstance>) {
    return nullptr;
}
