#include "Minecraft.World/item/Item.h"
#include <memory>
#include "Minecraft.Client/resources/ResourceLocation.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/entity/player/Player.h"
#include "types.h"

#include "Minecraft.Client/resources/MappedRegistry.h"

// should be replaced with proper ones later on
// even though those are unused
const ItemPropertyFunction* lefthandedFunction = nullptr;
const ItemPropertyFunction* cooldownFunction = nullptr;

Item::Item(){
    // Some of those should probably be moved to header def but idk which ones
        this->mMaxStackSize = 64;
        this->mMaxDamage = 0;
        this->mHandEquipped = false;
        this->mStackedByData = 0;
        this->mCraftingRemainingItem = nullptr;
        this->wstring_1 = L"";
        this->mBaseItemType = 0;
        this->mMaterial = 0;
        this->mIconName = L"";
        this->mIcon = nullptr;
        this->byte78 = 0;
    //
    this->mSimpleRegistry = new SimpleRegistry<ResourceLocation, const ItemPropertyFunction*>();

    this->addProperty(ResourceLocation(L"lefthanded"), lefthandedFunction);

    this->addProperty(ResourceLocation(L"cooldown"), cooldownFunction);
}

bool Item::canBeDepleted(){
    return this->mMaxDamage > 0 && (!this->mStackedByData || this->mMaxStackSize == 1);
}

void Item::setIconName(std::wstring const& iconName){
    this->mIconName = iconName;
}

std::shared_ptr<ItemInstance> Item::getDefaultInstance(const std::shared_ptr<ItemInstance>& a2){
    return std::shared_ptr<ItemInstance>(new ItemInstance(this));
}

bool Item::verifyTagAfterLoad(CompoundTag*){
    return false;
}

int Item::GetUseTooltip(const ItemToolTipDataHolder&){
    return -1;
}

bool Item::useOn(const std::shared_ptr<Player>&, Level*, const BlockPos&, InteractionHand::EInteractionHand, const Direction*, float, float, float, bool){
    return true;
}

float Item::getDestroySpeed(const std::shared_ptr<ItemInstance>&, BlockState*){
    return 1.0f;
}

bool Item::TestUse(Level*, const std::shared_ptr<Player>&, InteractionHand::EInteractionHand){
    return false;
}

InteractionResultHolder Item::use(Level*, const std::shared_ptr<Player>& player, InteractionHand::EInteractionHand hand){
    return InteractionResultHolder(InteractionResult::PASS, player->getItemInHand(hand));
}

not_null_ptr<ItemInstance> Item::finishUsingItem(not_null_ptr<ItemInstance> item, Level*, const std::shared_ptr<LivingEntity>&){
    return item;
}

int Item::getMaxStackSize(){
    return this->mMaxStackSize;
}

int Item::getLevelDataForAuxValue(int){
    return 0;
}

bool Item::hurtEnemy(const std::shared_ptr<ItemInstance>&, const std::shared_ptr<LivingEntity>&, const std::shared_ptr<LivingEntity>&){
    return false;
}

bool Item::mineBlock(const std::shared_ptr<ItemInstance>&, Level*, const BlockState*, const BlockPos&, std::shared_ptr<LivingEntity>&){
    return false;
}

int Item::getAttackDamage(const std::shared_ptr<Entity>&){
    return 1;
}

bool Item::canDestroySpecial(const BlockState*){
    return false;
}

bool Item::interactEnemy(const std::shared_ptr<ItemInstance>&, const std::shared_ptr<Player>&, const std::shared_ptr<LivingEntity>&, InteractionHand::EInteractionHand){
    return false;
}

bool Item::isHandEquipped(){
    return this->mHandEquipped;
}

bool Item::isMirroredArt(){
    return false;
}

int Item::getDescriptionId(int){
    return this->mDescriptionId;
}

int Item::getDescriptionId(const std::shared_ptr<ItemInstance>&){
    return this->mDescriptionId;
}

int Item::getUseDescriptionId(){
    return this->mUseDescriptionId;
}

int Item::getUseDescriptionId(const std::shared_ptr<ItemInstance>&){
    return this->mUseDescriptionId;
}

bool Item::shouldOverrideMultiplayerNBT(){
    return true;
}

int Item::getColor(const std::shared_ptr<ItemInstance>&, int){
    return 0xFFFFFF;
}

void Item::inventoryTick(std::shared_ptr<ItemInstance>&, Level*, std::shared_ptr<Entity>&, int, bool){}

void Item::onCraftedBy(const std::shared_ptr<ItemInstance>&, Level*, const std::shared_ptr<Player>&){}

bool Item::isComplex(){
    return false;
}

int Item::getUseAnimation(const std::shared_ptr<ItemInstance>&){
    return 0;
}

int Item::getUseDuration(const std::shared_ptr<ItemInstance>&){
    return 0;
}

void Item::releaseUsing(const std::shared_ptr<ItemInstance>&, Level*, const std::shared_ptr<LivingEntity>&, int){}

void Item::appendHoverText(const std::shared_ptr<ItemInstance>&, const std::shared_ptr<Player>&, void* htmlString, bool){}

bool Item::isFoil(not_null_ptr<ItemInstance> itemInstance){
    return itemInstance->isEnchanted();
}

bool Item::isEnchantable(const std::shared_ptr<ItemInstance>& a1){
    return this->getMaxStackSize() == 1 && this->canBeDepleted();
}

int Item::getEnchantmentValue(){
    return 0;
}

bool Item::mayBePlacedInAdventureMode(){
    return true;
}

bool Item::isValidRepairItem(const std::shared_ptr<ItemInstance>&, const std::shared_ptr<ItemInstance>&){
    return false;
}

bool Item::hasMultipleSpriteLayers(){
    return false;
}

void* Item::getLayerIcon(int a2, int, const std::shared_ptr<ItemInstance>&){
    return this->getIcon(a2);
}

int Item::getIconType(){
    return 1;
}

void* Item::getIcon(int){
    return this->mIcon;
}

int Item::GetArmorType(){
    return 0;
}

int Item::GetOverrideCount(){
    return -1;
}

int Item::GetOverrideCountColour(){
    return -1;
}

void* Item::GetOverrideCountIcon(const std::shared_ptr<ItemInstance>&){
    return nullptr;
}