#include "net/minecraft/world/item/Item.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/sounds/SoundEvents.h"
#include "net/minecraft/world/effect/MobEffectInstance.h"
#include "net/minecraft/world/effect/MobEffects.h"
#include "net/minecraft/world/item/AirItem.h"
#include "net/minecraft/world/item/ArmorItem.h"
#include "net/minecraft/world/item/ArmorStandItem.h"
#include "net/minecraft/world/item/ArrowItem.h"
#include "net/minecraft/world/item/AxeItem.h"
#include "net/minecraft/world/item/BowItem.h"
#include "net/minecraft/world/item/CoalItem.h"
#include "net/minecraft/world/item/DebugFourjItem.h"
#include "net/minecraft/world/item/ElytraItem.h"
#include "net/minecraft/world/item/EmptyMapItem.h"
#include "net/minecraft/world/item/FishingRodItem.h"
#include "net/minecraft/world/item/FoodItem.h"
#include "net/minecraft/world/item/HorseArmorItem.h"
#include "net/minecraft/world/item/ItemBootstrapTypes.h"
#include "net/minecraft/world/item/ItemResolvers.h"
#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/item/LeadItem.h"
#include "net/minecraft/world/item/MapItem.h"
#include "net/minecraft/world/item/PickaxeItem.h"
#include "net/minecraft/world/item/ShovelItem.h"
#include "net/minecraft/world/item/SkullItem.h"
#include "net/minecraft/world/item/SwordItem.h"
#include "net/minecraft/world/level/block/LeafBlock.h"
#include <cstring>
#include <new>

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

const Item::Tier* Item::Tier::WOOD = new Item::Tier(0, 59, 2.0, 0.0, 15, 0);  // name guessed
const Item::Tier* Item::Tier::STONE = new Item::Tier(1, 131, 4.0, 1.0, 5, 1);
const Item::Tier* Item::Tier::IRON = new Item::Tier(2, 250, 6.0, 2.0, 14, 2);
const Item::Tier* Item::Tier::DIAMOND = new Item::Tier(3, 1561, 8.0, 3.0, 10, 3);  // name guessed
const Item::Tier* Item::Tier::GOLD = new Item::Tier(0, 32, 12.0, 0.0, 22, 4);

Item::Item() {
    this->m_maxStackSize = 64;
    this->m_maxDamage = 0;
    this->m_handEquipped = false;
    this->m_stackedByData = 0;
    this->m_craftingRemainingItem = nullptr;
    this->m_wstring1 = L"";
    this->m_baseItemType = 0;
    this->m_material = 0;
    this->m_iconName = L"";
    this->m_defaultIcon = nullptr;
    this->m_byte78 = 0;

    this->m_simpleRegistry = new SimpleRegistry<ResourceLocation, const ItemPropertyFunction*>();

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
    return this->m_maxDamage > 0 && (!this->m_stackedByData || this->m_maxStackSize == 1);
}

Item* Item::setIconName(const std::wstring& iconName) {
    this->m_iconName = iconName;
    return this;
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
    return this->m_maxStackSize;
}

int Item::getMaxDamage() {
    return m_maxDamage;
}

bool Item::isStackedByData() {
    return m_stackedByData;
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
    return this->m_handEquipped;
}

bool Item::isMirroredArt() {
    return false;
}

unsigned int Item::getDescriptionId(int) {
    return this->m_descriptionId;
}

unsigned int Item::getDescriptionId(not_null_ptr<ItemInstance>) {
    return this->m_descriptionId;
}

unsigned int Item::getUseDescriptionId() {
    return this->m_useDescriptionId;
}

unsigned int Item::getUseDescriptionId(not_null_ptr<ItemInstance>) {
    return this->m_useDescriptionId;
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
    this->m_defaultIcon = iconRegister->registerIcon(this->m_iconName);
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
    return this->m_defaultIcon;
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

extern std::wstring sBaseTierName;

namespace ItemBootstrap {
extern const int LEATHER_ARMOR_TEXTURES[2] = {209, 210};
}

static_assert(sizeof(SlabBlockItem) == 0xa0, "SlabBlockItem allocation ABI");
static_assert(sizeof(AirItem) == 0x88, "AirItem allocation ABI");
static_assert(sizeof(MultiBlockItem) == 0xa8, "MultiBlockItem allocation ABI");
static_assert(sizeof(TintedBlockItem) == 0xa0, "TintedBlockItem allocation ABI");
static_assert(sizeof(LeafBlockItem) == 0x98, "LeafBlockItem allocation ABI");
static_assert(sizeof(PistonBlockItem) == 0x90, "PistonBlockItem allocation ABI");
static_assert(sizeof(SnowItem) == 0x90, "SnowItem allocation ABI");
static_assert(sizeof(WaterLilyBlockItem) == 0xa0, "WaterLilyBlockItem allocation ABI");
static_assert(sizeof(AnvilBlockItem) == 0xa8, "AnvilBlockItem allocation ABI");
static_assert(sizeof(ShulkerBoxBlockItem) == 0x90, "ShulkerBoxBlockItem allocation ABI");
static_assert(sizeof(ShovelItem) == 0xa8, "ShovelItem allocation ABI");
static_assert(sizeof(PickaxeItem) == 0xa8, "PickaxeItem allocation ABI");
static_assert(sizeof(AxeItem) == 0xa8, "AxeItem allocation ABI");
static_assert(sizeof(FlintAndSteelItem) == 0x80, "FlintAndSteelItem allocation ABI");
static_assert(sizeof(FoodItem) == 0x98, "FoodItem allocation ABI");
static_assert(sizeof(BowItem) == 0x98, "BowItem allocation ABI");
static_assert(sizeof(ArrowItem) == 0x80, "ArrowItem allocation ABI");
static_assert(sizeof(CoalItem) == 0x88, "CoalItem allocation ABI");
static_assert(sizeof(Item) == 0x80, "Item allocation ABI");
static_assert(sizeof(SwordItem) == 0x88, "SwordItem allocation ABI");
static_assert(sizeof(BowlFoodItem) == 0x98, "BowlFoodItem allocation ABI");
static_assert(sizeof(BlockPlanterItem) == 0x88, "BlockPlanterItem allocation ABI");
static_assert(sizeof(HoeItem) == 0x88, "HoeItem allocation ABI");
static_assert(sizeof(SeedItem) == 0x90, "SeedItem allocation ABI");
static_assert(sizeof(ArmorItem) == 0xb0, "ArmorItem allocation ABI");
static_assert(sizeof(HangingEntityItem) == 0x80, "HangingEntityItem allocation ABI");
static_assert(sizeof(GoldenAppleItem) == 0x98, "GoldenAppleItem allocation ABI");
static_assert(sizeof(SignItem) == 0x80, "SignItem allocation ABI");
static_assert(sizeof(DoorItem) == 0x88, "DoorItem allocation ABI");
static_assert(sizeof(BucketItem) == 0x88, "BucketItem allocation ABI");
static_assert(sizeof(MinecartItem) == 0x88, "MinecartItem allocation ABI");
static_assert(sizeof(SaddleItem) == 0x80, "SaddleItem allocation ABI");
static_assert(sizeof(RedStoneDustItem) == 0x80, "RedStoneDustItem allocation ABI");
static_assert(sizeof(SnowballItem) == 0x80, "SnowballItem allocation ABI");
static_assert(sizeof(BoatItem) == 0x80, "BoatItem allocation ABI");
static_assert(sizeof(MilkBucketItem) == 0x80, "MilkBucketItem allocation ABI");
static_assert(sizeof(BookItem) == 0x80, "BookItem allocation ABI");
static_assert(sizeof(EggItem) == 0x80, "EggItem allocation ABI");
static_assert(sizeof(CompassItem) == 0xa0, "CompassItem allocation ABI");
static_assert(sizeof(FishingRodItem) == 0x88, "FishingRodItem allocation ABI");
static_assert(sizeof(ClockItem) == 0xa0, "ClockItem allocation ABI");
static_assert(sizeof(FishFoodItem) == 0x98, "FishFoodItem allocation ABI");
static_assert(sizeof(DyeItem) == 0x100, "DyeItem allocation ABI");
static_assert(sizeof(BedItem) == 0x88, "BedItem allocation ABI");
static_assert(sizeof(MapItem) == 0x88, "MapItem allocation ABI");
static_assert(sizeof(ShearsItem) == 0x80, "ShearsItem allocation ABI");
static_assert(sizeof(MobEffectInstance) == 0x18, "MobEffectInstance allocation ABI");
static_assert(sizeof(EnderpearlItem) == 0x80, "EnderpearlItem allocation ABI");
static_assert(sizeof(PotionItem) == 0x90, "PotionItem allocation ABI");
static_assert(sizeof(BottleItem) == 0x80, "BottleItem allocation ABI");
static_assert(sizeof(EnderEyeItem) == 0x80, "EnderEyeItem allocation ABI");
static_assert(sizeof(SpawnEggItem) == 0x88, "SpawnEggItem allocation ABI");
static_assert(sizeof(ExperienceBottleItem) == 0x80, "ExperienceBottleItem allocation ABI");
static_assert(sizeof(FireChargeItem) == 0x88, "FireChargeItem allocation ABI");
static_assert(sizeof(WritableBookItem) == 0x80, "WritableBookItem allocation ABI");
static_assert(sizeof(WrittenBookItem) == 0x80, "WrittenBookItem allocation ABI");
static_assert(sizeof(SeedFoodItem) == 0xa8, "SeedFoodItem allocation ABI");
static_assert(sizeof(EmptyMapItem) == 0x80, "EmptyMapItem allocation ABI");
static_assert(sizeof(SkullItem) == 0x80, "SkullItem allocation ABI");
static_assert(sizeof(CarrotOnAStickItem) == 0x80, "CarrotOnAStickItem allocation ABI");
static_assert(sizeof(SimpleFoiledItem) == 0x80, "SimpleFoiledItem allocation ABI");
static_assert(sizeof(FireworksItem) == 0x80, "FireworksItem allocation ABI");
static_assert(sizeof(FireworkChargeItem) == 0x88, "FireworkChargeItem allocation ABI");
static_assert(sizeof(EnchantedBookItem) == 0x80, "EnchantedBookItem allocation ABI");
static_assert(sizeof(ArmorStandItem) == 0x80, "ArmorStandItem allocation ABI");
static_assert(sizeof(HorseArmorItem) == 0xc8, "HorseArmorItem allocation ABI");
static_assert(sizeof(LeadItem) == 0x80, "LeadItem allocation ABI");
static_assert(sizeof(NameTagItem) == 0x80, "NameTagItem allocation ABI");
static_assert(sizeof(BannerItem) == 0x90, "BannerItem allocation ABI");
static_assert(sizeof(EndCrystalItem) == 0x80, "EndCrystalItem allocation ABI");
static_assert(sizeof(ChorusFruitItem) == 0x98, "ChorusFruitItem allocation ABI");
static_assert(sizeof(SplashPotionItem) == 0x90, "SplashPotionItem allocation ABI");
static_assert(sizeof(SpectralArrowItem) == 0x80, "SpectralArrowItem allocation ABI");
static_assert(sizeof(TippedArrowItem) == 0x88, "TippedArrowItem allocation ABI");
static_assert(sizeof(LingeringPotionItem) == 0x90, "LingeringPotionItem allocation ABI");
static_assert(sizeof(ElytraItem) == 0x88, "ElytraItem allocation ABI");
static_assert(sizeof(DebugFourjItem) == 0x80, "DebugFourjItem allocation ABI");
static_assert(sizeof(RecordItem) == 0xa8, "RecordItem allocation ABI");

// NON_MATCHING | score: 6165 (lower is better)
void Item::staticCtor() {
    registerBlock(Blocks::WATER);
    registerBlock(Blocks::LAVA);
    registerBlock(Blocks::COCOA);
    registerBlock(Blocks::REEDS);
    registerBlock(Blocks::LIT_REDSTONE_LAMP);
    registerBlock(Blocks::NETHER_WART);
    registerBlock(Blocks::POTATOES);
    registerBlock(Blocks::CARROTS);
    registerBlock(Blocks::CAKE);
    registerBlock(Blocks::WHEAT);
    auto* block1 = Blocks::DOUBLE_WOODEN_SLAB;
    auto* item2
        = new SlabBlockItem(Blocks::DOUBLE_WOODEN_SLAB, static_cast<HalfSlabBlock*>(Blocks::WOODEN_SLAB),
                            static_cast<HalfSlabBlock*>(Blocks::DOUBLE_WOODEN_SLAB));
    auto* configured3 = item2->BlockItem::setDescriptionId(Blocks::DOUBLE_WOODEN_SLAB->getDescriptionId(-1));
    registerBlock(block1, configured3);
    auto* block4 = Blocks::DOUBLE_STONE_SLAB;
    auto* item5
        = new SlabBlockItem(Blocks::DOUBLE_STONE_SLAB, static_cast<HalfSlabBlock*>(Blocks::STONE_SLAB),
                            static_cast<HalfSlabBlock*>(Blocks::DOUBLE_STONE_SLAB));
    auto* configured6 = item5->BlockItem::setDescriptionId(Blocks::DOUBLE_STONE_SLAB->getDescriptionId(-1));
    registerBlock(block4, configured6);
    auto* block7 = Blocks::DOUBLE_STONE_SLAB2;
    auto* item8
        = new SlabBlockItem(Blocks::DOUBLE_STONE_SLAB2, static_cast<HalfSlabBlock*>(Blocks::STONE_SLAB2),
                            static_cast<HalfSlabBlock*>(Blocks::DOUBLE_STONE_SLAB2));
    auto* configured9 = item8->BlockItem::setDescriptionId(Blocks::DOUBLE_STONE_SLAB2->getDescriptionId(-1));
    registerBlock(block7, configured9);
    registerBlock(Blocks::BED);
    registerBlock(Blocks::PISTON_HEAD);
    registerBlock(Blocks::REDSTONE_WIRE);
    registerBlock(Blocks::STANDING_SIGN);
    registerBlock(Blocks::WALL_SIGN);
    registerBlock(Blocks::LIT_REDSTONE_ORE);
    registerBlock(Blocks::UNLIT_REDSTONE_TORCH);
    registerBlock(Blocks::UNPOWERED_REPEATER);
    registerBlock(Blocks::POWERED_REPEATER);
    registerBlock(Blocks::PUMPKIN_STEM);
    registerBlock(Blocks::MELON_STEM);
    registerBlock(Blocks::BREWING_STAND);
    registerBlock(Blocks::CAULDRON);
    registerBlock(Blocks::TRIPWIRE);
    registerBlock(Blocks::FLOWER_POT);
    registerBlock(Blocks::SKULL);
    registerBlock(Blocks::UNPOWERED_COMPARATOR);
    registerBlock(Blocks::POWERED_COMPARATOR);
    auto* block10 = Blocks::AIR;
    auto* item11 = new AirItem(Blocks::AIR);
    registerBlock(block10, item11);
    auto* block12 = Blocks::STONE;
    auto* item13
        = new MultiBlockItem(Blocks::STONE, Blocks::STONE, StoneBlockNameResolver, StoneBlockDescResolver);
    auto* configured14 = item13->BlockItem::setDescriptionId(Blocks::STONE->getDescriptionId(-1));
    registerBlock(block12, configured14);
    auto* block15 = Blocks::GRASS;
    auto* item16 = new TintedBlockItem(Blocks::GRASS, 0);
    registerBlock(block15, item16);
    auto* block17 = Blocks::DIRT;
    auto* item18 = new MultiBlockItem(Blocks::DIRT, Blocks::DIRT, ItemResolvers::DirtBlockName,
                                      ItemResolvers::DirtBlockDesc);
    registerBlock(block17, item18);
    registerBlock(Blocks::COBBLESTONE);
    auto* block19 = Blocks::PLANKS;
    auto* item20 = new MultiBlockItem(Blocks::PLANKS, Blocks::PLANKS, ItemResolvers::PlanksBlockName, 0);
    auto* configured21 = item20->BlockItem::setDescriptionId(Blocks::PLANKS->getDescriptionId(-1));
    registerBlock(block19, configured21);
    auto* block22 = Blocks::SAPLING;
    auto* item23 = new MultiBlockItem(Blocks::SAPLING, Blocks::SAPLING, ItemResolvers::SaplingName, 0);
    auto* configured24 = item23->BlockItem::setDescriptionId(Blocks::SAPLING->getDescriptionId(-1));
    registerBlock(block22, configured24);
    registerBlock(Blocks::BEDROCK);
    auto* block25 = Blocks::SAND;
    auto* item26 = new MultiBlockItem(Blocks::SAND, Blocks::SAND, ItemResolvers::SandBlockName,
                                      ItemResolvers::SandBlockDesc);
    registerBlock(block25, item26);
    registerBlock(Blocks::GRAVEL);
    registerBlock(Blocks::GOLD_ORE);
    registerBlock(Blocks::IRON_ORE);
    registerBlock(Blocks::COAL_ORE);
    auto* block27 = Blocks::LOG;
    auto* item28 = new MultiBlockItem(Blocks::LOG, Blocks::LOG, ItemResolvers::LogName, 0);
    auto* configured29 = item28->BlockItem::setDescriptionId(Blocks::LOG->getDescriptionId(-1));
    registerBlock(block27, configured29);
    auto* block30 = Blocks::LOG2;
    auto* item31 = new MultiBlockItem(Blocks::LOG2, Blocks::LOG2, ItemResolvers::Log2Name, 0);
    auto* configured32 = item31->BlockItem::setDescriptionId(Blocks::LOG2->getDescriptionId(-1));
    registerBlock(block30, configured32);
    auto* block33 = Blocks::LEAVES;
    auto* item34 = new LeafBlockItem(Blocks::LEAVES);
    auto* configured35 = item34->BlockItem::setDescriptionId(Blocks::LEAVES->getDescriptionId(-1));
    registerBlock(block33, configured35);
    auto* block36 = Blocks::LEAVES2;
    auto* item37 = new LeafBlockItem(Blocks::LEAVES2);
    auto* configured38 = item37->BlockItem::setDescriptionId(Blocks::LEAVES2->getDescriptionId(-1));
    registerBlock(block36, configured38);
    auto* block39 = Blocks::SPONGE;
    auto* item40 = new MultiBlockItem(Blocks::SPONGE, Blocks::SPONGE, ItemResolvers::SpongeName,
                                      ItemResolvers::SpongeDesc);
    auto* configured41 = item40->BlockItem::setDescriptionId(Blocks::SPONGE->getDescriptionId(-1));
    registerBlock(block39, configured41);
    registerBlock(Blocks::GLASS);
    registerBlock(Blocks::LAPIS_ORE);
    registerBlock(Blocks::LAPIS_BLOCK);
    registerBlock(Blocks::DISPENSER);
    auto* block42 = Blocks::SANDSTONE;
    auto* item43
        = new MultiBlockItem(Blocks::SANDSTONE, Blocks::SANDSTONE, ItemResolvers::SandStoneBlockName, 0);
    auto* configured44 = item43->BlockItem::setDescriptionId(Blocks::SANDSTONE->getDescriptionId(-1));
    registerBlock(block42, configured44);
    registerBlock(Blocks::NOTEBLOCK);
    registerBlock(Blocks::GOLDEN_RAIL);
    registerBlock(Blocks::DETECTOR_RAIL);
    auto* block45 = Blocks::STICKY_PISTON;
    auto* item46 = new PistonBlockItem(Blocks::STICKY_PISTON);
    registerBlock(block45, item46);
    registerBlock(Blocks::WEB);
    int tallGrassNames[] = {static_cast<int>(StringIDs::Shrub), StringIDs::TallGrass, StringIDs::Fern};
    arrayWithLength<int> tallGrassIds(tallGrassNames);
    auto* block47 = Blocks::TALLGRASS;
    auto* item48 = new TintedBlockItem(Blocks::TALLGRASS, 1);
    auto* configured49 = item48->setDescriptionIds(tallGrassIds);
    registerBlock(block47, configured49);
    registerBlock(Blocks::DEADBUSH);
    auto* block50 = Blocks::PISTON;
    auto* item51 = new PistonBlockItem(Blocks::PISTON);
    registerBlock(block50, item51);
    auto* block52 = Blocks::WOOL;
    auto* item53 = new MultiBlockItem(Blocks::WOOL, Blocks::WOOL, ItemResolvers::WoolName, 0);
    auto* configured54 = item53->BlockItem::setDescriptionId(Blocks::WOOL->getDescriptionId(-1));
    registerBlock(block52, configured54);
    auto* block55 = Blocks::YELLOW_FLOWER;
    auto* item56 = new MultiBlockItem(Blocks::YELLOW_FLOWER, Blocks::YELLOW_FLOWER, ItemResolvers::FlowerName,
                                      ItemResolvers::FlowerDesc);
    auto* configured57 = item56->BlockItem::setDescriptionId(Blocks::YELLOW_FLOWER->getDescriptionId(-1));
    registerBlock(block55, configured57);
    auto* block58 = Blocks::RED_FLOWER;
    auto* item59 = new MultiBlockItem(Blocks::RED_FLOWER, Blocks::RED_FLOWER, ItemResolvers::FlowerName,
                                      ItemResolvers::FlowerDesc);
    auto* configured60 = item59->BlockItem::setDescriptionId(Blocks::RED_FLOWER->getDescriptionId(-1));
    registerBlock(block58, configured60);
    registerBlock(Blocks::BROWN_MUSHROOM);
    registerBlock(Blocks::RED_MUSHROOM);
    registerBlock(Blocks::GOLD_BLOCK);
    registerBlock(Blocks::IRON_BLOCK);
    auto* block61 = Blocks::STONE_SLAB;
    auto* item62 = new SlabBlockItem(Blocks::STONE_SLAB, static_cast<HalfSlabBlock*>(Blocks::STONE_SLAB),
                                     static_cast<HalfSlabBlock*>(Blocks::DOUBLE_STONE_SLAB));
    auto* configured63 = item62->BlockItem::setDescriptionId(Blocks::STONE_SLAB->getDescriptionId(-1));
    registerBlock(block61, configured63);
    registerBlock(Blocks::BRICK_BLOCK);
    registerBlock(Blocks::TNT);
    registerBlock(Blocks::BOOKSHELF);
    registerBlock(Blocks::MOSSY_COBBLESTONE);
    registerBlock(Blocks::OBSIDIAN);
    registerBlock(Blocks::TORCH);
    registerBlock(Blocks::MOB_SPAWNER);
    registerBlock(Blocks::OAK_STAIRS);
    registerBlock(Blocks::CHEST);
    registerBlock(Blocks::DIAMOND_ORE);
    registerBlock(Blocks::DIAMOND_BLOCK);
    registerBlock(Blocks::CRAFTING_TABLE);
    registerBlock(Blocks::FARMLAND);
    registerBlock(Blocks::FURNACE);
    registerBlock(Blocks::LIT_FURNACE);
    registerBlock(Blocks::LADDER);
    registerBlock(Blocks::RAIL);
    registerBlock(Blocks::STONE_STAIRS);
    registerBlock(Blocks::LEVER);
    registerBlock(Blocks::STONE_PRESSURE_PLATE);
    registerBlock(Blocks::WOODEN_PRESSURE_PLATE);
    registerBlock(Blocks::REDSTONE_ORE);
    registerBlock(Blocks::REDSTONE_TORCH);
    registerBlock(Blocks::STONE_BUTTON);
    auto* block64 = Blocks::SNOW_LAYER;
    auto* item65 = new SnowItem(Blocks::SNOW_LAYER);
    registerBlock(block64, item65);
    registerBlock(Blocks::ICE);
    registerBlock(Blocks::SNOW);
    registerBlock(Blocks::CACTUS);
    registerBlock(Blocks::CLAY);
    registerBlock(Blocks::JUKEBOX);
    registerBlock(Blocks::FENCE);
    registerBlock(Blocks::SPRUCE_FENCE);
    registerBlock(Blocks::BIRCH_FENCE);
    registerBlock(Blocks::JUNGLE_FENCE);
    registerBlock(Blocks::DARK_OAK_FENCE);
    registerBlock(Blocks::ACACIA_FENCE);
    registerBlock(Blocks::PUMPKIN);
    registerBlock(Blocks::NETHERRACK);
    registerBlock(Blocks::SOUL_SAND);
    registerBlock(Blocks::GLOWSTONE);
    registerBlock(Blocks::LIT_PUMPKIN);
    registerBlock(Blocks::TRAPDOOR);
    auto* block66 = Blocks::MONSTER_EGG;
    auto* item67
        = new MultiBlockItem(Blocks::MONSTER_EGG, Blocks::MONSTER_EGG, ItemResolvers::MonsterEggBlockName, 0);
    auto* configured68 = item67->BlockItem::setDescriptionId(Blocks::MONSTER_EGG->getDescriptionId(-1));
    registerBlock(block66, configured68);
    auto* block69 = Blocks::STONEBRICK;
    auto* item70
        = new MultiBlockItem(Blocks::STONEBRICK, Blocks::STONEBRICK, ItemResolvers::StoneBrickBlockName, 0);
    auto* configured71 = item70->BlockItem::setDescriptionId(Blocks::STONEBRICK->getDescriptionId(-1));
    registerBlock(block69, configured71);
    auto* block72 = Blocks::BROWN_MUSHROOM_BLOCK;
    auto* item73 = new MultiBlockItem(Blocks::BROWN_MUSHROOM_BLOCK, Blocks::BROWN_MUSHROOM_BLOCK, 0, 0);
    auto* configured74
        = item73->BlockItem::setDescriptionId(Blocks::BROWN_MUSHROOM_BLOCK->getDescriptionId(-1));
    registerBlock(block72, configured74);
    auto* block75 = Blocks::RED_MUSHROOM_BLOCK;
    auto* item76 = new MultiBlockItem(Blocks::RED_MUSHROOM_BLOCK, Blocks::RED_MUSHROOM_BLOCK, 0, 0);
    auto* configured77
        = item76->BlockItem::setDescriptionId(Blocks::RED_MUSHROOM_BLOCK->getDescriptionId(-1));
    registerBlock(block75, configured77);
    registerBlock(Blocks::IRON_BARS);
    registerBlock(Blocks::GLASS_PANE);
    registerBlock(Blocks::MELON_BLOCK);
    auto* block78 = Blocks::VINE;
    auto* item79 = new TintedBlockItem(Blocks::VINE, 0);
    registerBlock(block78, item79);
    registerBlock(Blocks::FENCE_GATE);
    registerBlock(Blocks::SPRUCE_FENCE_GATE);
    registerBlock(Blocks::BIRCH_FENCE_GATE);
    registerBlock(Blocks::JUNGLE_FENCE_GATE);
    registerBlock(Blocks::DARK_OAK_FENCE_GATE);
    registerBlock(Blocks::ACACIA_FENCE_GATE);
    registerBlock(Blocks::BRICK_STAIRS);
    registerBlock(Blocks::STONE_BRICK_STAIRS);
    registerBlock(Blocks::MYCELIUM);
    auto* block80 = Blocks::WATERLILY;
    auto* item81 = new WaterLilyBlockItem(Blocks::WATERLILY);
    registerBlock(block80, item81);
    registerBlock(Blocks::NETHER_BRICK);
    registerBlock(Blocks::NETHER_BRICK_FENCE);
    registerBlock(Blocks::NETHER_BRICK_STAIRS);
    registerBlock(Blocks::ENCHANTING_TABLE);
    registerBlock(Blocks::END_PORTAL_FRAME);
    registerBlock(Blocks::END_STONE);
    registerBlock(Blocks::DRAGON_EGG);
    registerBlock(Blocks::REDSTONE_LAMP);
    auto* block82 = Blocks::WOODEN_SLAB;
    auto* item83 = new SlabBlockItem(Blocks::WOODEN_SLAB, static_cast<HalfSlabBlock*>(Blocks::WOODEN_SLAB),
                                     static_cast<HalfSlabBlock*>(Blocks::DOUBLE_WOODEN_SLAB));
    auto* configured84 = item83->BlockItem::setDescriptionId(Blocks::WOODEN_SLAB->getDescriptionId(-1));
    registerBlock(block82, configured84);
    registerBlock(Blocks::SANDSTONE_STAIRS);
    registerBlock(Blocks::EMERALD_ORE);
    registerBlock(Blocks::ENDER_CHEST);
    registerBlock(Blocks::TRIPWIRE_HOOK);
    registerBlock(Blocks::EMERALD_BLOCK);
    registerBlock(Blocks::SPRUCE_STAIRS);
    registerBlock(Blocks::BIRCH_STAIRS);
    registerBlock(Blocks::JUNGLE_STAIRS);
    registerBlock(Blocks::BEACON);
    auto* block85 = Blocks::COBBLESTONE_WALL;
    auto* item86 = new MultiBlockItem(Blocks::COBBLESTONE_WALL, Blocks::COBBLESTONE_WALL,
                                      ItemResolvers::WallBlockName, 0);
    auto* configured87 = item86->BlockItem::setDescriptionId(Blocks::COBBLESTONE_WALL->getDescriptionId(-1));
    registerBlock(block85, configured87);
    registerBlock(Blocks::WOODEN_BUTTON);
    auto* block88 = Blocks::ANVIL;
    auto* item89 = new AnvilBlockItem(Blocks::ANVIL);
    auto* configured90 = item89->BlockItem::setDescriptionId(Blocks::ANVIL->getDescriptionId(-1));
    registerBlock(block88, configured90);
    registerBlock(Blocks::TRAPPED_CHEST);
    registerBlock(Blocks::LIGHT_WEIGHTED_PRESSURE_PLATE);
    registerBlock(Blocks::HEAVY_WEIGHTED_PRESSURE_PLATE);
    registerBlock(Blocks::DAYLIGHT_DETECTOR);
    registerBlock(Blocks::REDSTONE_BLOCK);
    registerBlock(Blocks::QUARTZ_ORE);
    registerBlock(Blocks::HOPPER);
    auto* block91 = Blocks::QUARTZ_BLOCK;
    auto* item92
        = new MultiBlockItem(Blocks::QUARTZ_BLOCK, Blocks::QUARTZ_BLOCK, ItemResolvers::AnvilName, 0);
    auto* configured93 = item92->BlockItem::setDescriptionId(Blocks::QUARTZ_BLOCK->getDescriptionId(-1));
    registerBlock(block91, configured93);
    registerBlock(Blocks::QUARTZ_STAIRS);
    registerBlock(Blocks::ACTIVATOR_RAIL);
    registerBlock(Blocks::DROPPER);
    auto* block94 = Blocks::STAINED_HARDENED_CLAY;
    auto* item95 = new MultiBlockItem(Blocks::STAINED_HARDENED_CLAY, Blocks::STAINED_HARDENED_CLAY,
                                      ItemResolvers::StainedClayName, 0);
    auto* configured96
        = item95->BlockItem::setDescriptionId(Blocks::STAINED_HARDENED_CLAY->getDescriptionId(-1));
    registerBlock(block94, configured96);
    registerBlock(Blocks::BARRIER);
    registerBlock(Blocks::IRON_TRAPDOOR);
    registerBlock(Blocks::HAY_BLOCK);
    auto* block97 = Blocks::CARPET;
    auto* item98 = new MultiBlockItem(Blocks::CARPET, Blocks::CARPET, ItemResolvers::StainedGlassPaneName, 0);
    auto* configured99 = item98->BlockItem::setDescriptionId(Blocks::CARPET->getDescriptionId(-1));
    registerBlock(block97, configured99);
    registerBlock(Blocks::HARDENED_CLAY);
    registerBlock(Blocks::COAL_BLOCK);
    registerBlock(Blocks::PACKED_ICE);
    registerBlock(Blocks::ACACIA_STAIRS);
    registerBlock(Blocks::DARK_OAK_STAIRS);
    registerBlock(Blocks::SLIME);
    auto* block100 = Blocks::DOUBLE_PLANT;
    auto* item101
        = new MultiBlockItem(Blocks::DOUBLE_PLANT, Blocks::DOUBLE_PLANT, ItemResolvers::DoublePlantBlockName,
                             ItemResolvers::DoublePlantBlockDesc);
    auto* configured102 = item101->BlockItem::setDescriptionId(Blocks::DOUBLE_PLANT->getDescriptionId(-1));
    registerBlock(block100, configured102);
    auto* block103 = Blocks::STAINED_GLASS;
    auto* item104
        = new MultiBlockItem(Blocks::STAINED_GLASS, Blocks::STAINED_GLASS, ItemResolvers::CarpetName, 0);
    auto* configured105 = item104->BlockItem::setDescriptionId(Blocks::STAINED_GLASS->getDescriptionId(-1));
    registerBlock(block103, configured105);
    auto* block106 = Blocks::STAINED_GLASS_PANE;
    auto* item107 = new MultiBlockItem(Blocks::STAINED_GLASS_PANE, Blocks::STAINED_GLASS_PANE,
                                       ItemResolvers::StainedGlassName, 0);
    auto* configured108
        = item107->BlockItem::setDescriptionId(Blocks::STAINED_GLASS_PANE->getDescriptionId(-1));
    registerBlock(block106, configured108);
    auto* block109 = Blocks::PRISMARINE;
    auto* item110
        = new MultiBlockItem(Blocks::PRISMARINE, Blocks::PRISMARINE, ItemResolvers::PrismarineBlockName,
                             ItemResolvers::PrismarineBlockDesc);
    auto* configured111 = item110->BlockItem::setDescriptionId(Blocks::PRISMARINE->getDescriptionId(-1));
    configured111->setBaseItemTypeAndMaterial(0x14, 0x36);
    registerBlock(block109, configured111);
    registerBlock(Blocks::SEA_LANTERN);
    auto* block112 = Blocks::RED_SANDSTONE;
    auto* item113 = new MultiBlockItem(Blocks::RED_SANDSTONE, Blocks::RED_SANDSTONE,
                                       ItemResolvers::RedSandStoneBlockName, 0);
    auto* configured114 = item113->BlockItem::setDescriptionId(Blocks::RED_SANDSTONE->getDescriptionId(-1));
    registerBlock(block112, configured114);
    registerBlock(Blocks::RED_SANDSTONE_STAIRS);
    auto* block115 = Blocks::STONE_SLAB2;
    auto* item116 = new SlabBlockItem(Blocks::STONE_SLAB2, static_cast<HalfSlabBlock*>(Blocks::STONE_SLAB2),
                                      static_cast<HalfSlabBlock*>(Blocks::DOUBLE_STONE_SLAB2));
    auto* configured117 = item116->BlockItem::setDescriptionId(Blocks::STONE_SLAB2->getDescriptionId(-1));
    registerBlock(block115, configured117);
    registerBlock(Blocks::END_BRICKS);
    registerBlock(Blocks::BEETROOTS);
    registerBlock(Blocks::GRASS_PATH);
    registerBlock(Blocks::FROSTED_ICE);
    registerBlock(Blocks::MAGMA);
    registerBlock(Blocks::NETHER_WART_BLOCK);
    registerBlock(Blocks::RED_NETHER_BRICK);
    registerBlock(Blocks::BONE_BLOCK);
    registerBlock(Blocks::END_ROD);
    registerBlock(Blocks::CHORUS_PLANT);
    registerBlock(Blocks::CHORUS_FLOWER);
    registerBlock(Blocks::PURPUR_BLOCK);
    registerBlock(Blocks::PURPUR_PILLAR);
    registerBlock(Blocks::PURPUR_STAIRS);
    auto* block118 = Blocks::PURPUR_SLAB;
    auto* item119 = new SlabBlockItem(Blocks::PURPUR_SLAB, static_cast<HalfSlabBlock*>(Blocks::PURPUR_SLAB),
                                      static_cast<HalfSlabBlock*>(Blocks::PURPUR_DOUBLE_SLAB));
    auto* configured120 = item119->BlockItem::setDescriptionId(Blocks::PURPUR_SLAB->getDescriptionId(-1));
    registerBlock(block118, configured120);
    registerBlock(Blocks::OBSERVER);
    auto* block121 = Blocks::WHITE_SHULKER_BOX;
    auto* item122 = new ShulkerBoxBlockItem(Blocks::WHITE_SHULKER_BOX);
    registerBlock(block121, item122);
    auto* block123 = Blocks::ORANGE_SHULKER_BOX;
    auto* item124 = new ShulkerBoxBlockItem(Blocks::ORANGE_SHULKER_BOX);
    registerBlock(block123, item124);
    auto* block125 = Blocks::MAGENTA_SHULKER_BOX;
    auto* item126 = new ShulkerBoxBlockItem(Blocks::MAGENTA_SHULKER_BOX);
    registerBlock(block125, item126);
    auto* block127 = Blocks::LIGHT_BLUE_SHULKER_BOX;
    auto* item128 = new ShulkerBoxBlockItem(Blocks::LIGHT_BLUE_SHULKER_BOX);
    registerBlock(block127, item128);
    auto* block129 = Blocks::YELLOW_SHULKER_BOX;
    auto* item130 = new ShulkerBoxBlockItem(Blocks::YELLOW_SHULKER_BOX);
    registerBlock(block129, item130);
    auto* block131 = Blocks::LIME_SHULKER_BOX;
    auto* item132 = new ShulkerBoxBlockItem(Blocks::LIME_SHULKER_BOX);
    registerBlock(block131, item132);
    auto* block133 = Blocks::PINK_SHULKER_BOX;
    auto* item134 = new ShulkerBoxBlockItem(Blocks::PINK_SHULKER_BOX);
    registerBlock(block133, item134);
    auto* block135 = Blocks::GRAY_SHULKER_BOX;
    auto* item136 = new ShulkerBoxBlockItem(Blocks::GRAY_SHULKER_BOX);
    registerBlock(block135, item136);
    auto* block137 = Blocks::SILVER_SHULKER_BOX;
    auto* item138 = new ShulkerBoxBlockItem(Blocks::SILVER_SHULKER_BOX);
    registerBlock(block137, item138);
    auto* block139 = Blocks::CYAN_SHULKER_BOX;
    auto* item140 = new ShulkerBoxBlockItem(Blocks::CYAN_SHULKER_BOX);
    registerBlock(block139, item140);
    auto* block141 = Blocks::PURPLE_SHULKER_BOX;
    auto* item142 = new ShulkerBoxBlockItem(Blocks::PURPLE_SHULKER_BOX);
    registerBlock(block141, item142);
    auto* block143 = Blocks::BLUE_SHULKER_BOX;
    auto* item144 = new ShulkerBoxBlockItem(Blocks::BLUE_SHULKER_BOX);
    registerBlock(block143, item144);
    auto* block145 = Blocks::BROWN_SHULKER_BOX;
    auto* item146 = new ShulkerBoxBlockItem(Blocks::BROWN_SHULKER_BOX);
    registerBlock(block145, item146);
    auto* block147 = Blocks::GREEN_SHULKER_BOX;
    auto* item148 = new ShulkerBoxBlockItem(Blocks::GREEN_SHULKER_BOX);
    registerBlock(block147, item148);
    auto* block149 = Blocks::RED_SHULKER_BOX;
    auto* item150 = new ShulkerBoxBlockItem(Blocks::RED_SHULKER_BOX);
    registerBlock(block149, item150);
    auto* block151 = Blocks::BLACK_SHULKER_BOX;
    auto* item152 = new ShulkerBoxBlockItem(Blocks::BLACK_SHULKER_BOX);
    registerBlock(block151, item152);
    registerBlock(Blocks::WHITE_GLAZED_TERRACOTTA);
    registerBlock(Blocks::ORANGE_GLAZED_TERRACOTTA);
    registerBlock(Blocks::MAGENTA_GLAZED_TERRACOTTA);
    registerBlock(Blocks::LIGHT_BLUE_GLAZED_TERRACOTTA);
    registerBlock(Blocks::YELLOW_GLAZED_TERRACOTTA);
    registerBlock(Blocks::LIME_GLAZED_TERRACOTTA);
    registerBlock(Blocks::PINK_GLAZED_TERRACOTTA);
    registerBlock(Blocks::GRAY_GLAZED_TERRACOTTA);
    registerBlock(Blocks::SILVER_GLAZED_TERRACOTTA);
    registerBlock(Blocks::CYAN_GLAZED_TERRACOTTA);
    registerBlock(Blocks::PURPLE_GLAZED_TERRACOTTA);
    registerBlock(Blocks::BLUE_GLAZED_TERRACOTTA);
    registerBlock(Blocks::BROWN_GLAZED_TERRACOTTA);
    registerBlock(Blocks::GREEN_GLAZED_TERRACOTTA);
    registerBlock(Blocks::RED_GLAZED_TERRACOTTA);
    registerBlock(Blocks::BLACK_GLAZED_TERRACOTTA);
    auto* block153 = Blocks::CONCRETE;
    auto* item154 = new MultiBlockItem(Blocks::CONCRETE, Blocks::CONCRETE, ItemResolvers::ConcreteName, 0);
    auto* configured155 = item154->BlockItem::setDescriptionId(Blocks::CONCRETE->getDescriptionId(-1));
    registerBlock(block153, configured155);
    auto* block156 = Blocks::CONCRETE_POWDER;
    auto* item157 = new MultiBlockItem(Blocks::CONCRETE_POWDER, Blocks::CONCRETE_POWDER,
                                       ItemResolvers::ConcretePowderName, 0);
    auto* configured158 = item157->BlockItem::setDescriptionId(Blocks::CONCRETE_POWDER->getDescriptionId(-1));
    registerBlock(block156, configured158);
    {
        std::wstring name(L"iron_shovel");
        auto* item159 = new ShovelItem(Item::Tier::IRON);
        std::wstring icon(L"shovelIron");
        auto* configured160 = item159->setIconName(icon);
        configured160->setBaseItemTypeAndMaterial(2, 3);
        item159->setDescriptionId(StringIDs::IronShovel, StringIDs::UsedToDigDirtGrassSandGravelAnd);
        registerItem(0x100, name, item159);
    }
    {
        std::wstring name(L"iron_pickaxe");
        auto* item161 = new PickaxeItem(Item::Tier::IRON);
        std::wstring icon(L"pickaxeIron");
        auto* configured162 = item161->setIconName(icon);
        auto* configured163 = configured162->setBaseItemTypeAndMaterial(3, 3);
        configured163->setDescriptionId(StringIDs::IronPickaxe,
                                        StringIDs::RequiredToMineStoneRelatedBlocksAndOre);
        registerItem(0x101, name, item161);
    }
    {
        std::wstring name(L"iron_axe");
        auto* item164 = new AxeItem(Item::Tier::IRON);
        std::wstring icon(L"hatchetIron");
        auto* configured165 = item164->setIconName(icon);
        configured165->setBaseItemTypeAndMaterial(4, 3);
        item164->setDescriptionId(StringIDs::IronAxe, StringIDs::UsedToChopWoodRelatedBlocksFasterThan);
        registerItem(0x102, name, item164);
    }
    {
        std::wstring name(L"flint_and_steel");
        auto* item166 = new FlintAndSteelItem();
        std::wstring icon(L"flintAndSteel");
        auto* configured167 = item166->setIconName(icon);
        auto* configured168 = configured167->setBaseItemTypeAndMaterial(0x1c, 0x1a);
        configured168->setDescriptionId(StringIDs::FlintAndSteel,
                                        StringIDs::UsedToCreateFireIgniteTntAndCreepers);
        registerItem(0x103, name, item166);
    }
    {
        std::wstring name(L"apple");
        auto* item169 = new FoodItem(4, 0.3f, 0);
        std::wstring icon(L"apple");
        auto* configured170 = item169->setIconName(icon);
        configured170->setDescriptionId(StringIDs::Apple, StringIDs::Restores2IconShank01AndCanBe);
        registerItem(0x104, name, item169);
    }
    {
        std::wstring name(L"bow");
        auto* item171 = new BowItem();
        std::wstring icon(L"bow");
        auto* configured172 = item171->setIconName(icon);
        auto* configured173 = configured172->setBaseItemTypeAndMaterial(0x18, 0x11);
        configured173->setDescriptionId(StringIDs::Bow, 0x7341480);
        registerItem(0x105, name, item171);
    }
    {
        std::wstring name(L"arrow");
        auto* item174 = new ArrowItem();
        std::wstring icon(L"arrow");
        auto* configured175 = item174->setIconName(icon);
        auto* configured176 = configured175->setBaseItemTypeAndMaterial(0x18, 0x12);
        auto* configured177
            = configured176->setDescriptionId(StringIDs::Arrow, StringIDs::UsedAsAmmunitionForBows);
        configured177->setFlag78(1);
        registerItem(0x106, name, item174);
    }
    {
        std::wstring name(L"coal");
        auto* item178 = new CoalItem();
        std::wstring icon(L"coal");
        auto* configured179 = item178->setIconName(icon);
        auto* configured180 = configured179->setBaseItemTypeAndMaterial(0x1f, 0x31);
        configured180->setDescriptionId(StringIDs::Coal, StringIDs::UsedAsAFuelInAFurnaceOr);
        registerItem(0x107, name, item178);
    }
    {
        std::wstring name(L"diamond");
        auto* item181 = new Item();
        std::wstring icon(L"diamond");
        item181->setIconName(icon);
        auto* configured182 = item181->setBaseItemTypeAndMaterial(0x1f, 5);
        configured182->setDescriptionId(StringIDs::Diamond, StringIDs::UseseToCreateVeryStrongToolsWeaponsOr);
        registerItem(0x108, name, item181);
    }
    {
        std::wstring name(L"iron_ingot");
        auto* item183 = new Item();
        std::wstring icon(L"ingotIron");
        auto* configured184 = item183->setIconName(icon);
        configured184->setBaseItemTypeAndMaterial(0x1f, 3);
        item183->setDescriptionId(StringIDs::IronIngot, StringIDs::AShinyIngotWhichCanBeUsedTo);
        registerItem(0x109, name, item183);
    }
    {
        std::wstring name(L"gold_ingot");
        auto* item185 = new Item();
        std::wstring icon(L"ingotGold");
        auto* configured186 = item185->setIconName(icon);
        auto* configured187 = configured186->setBaseItemTypeAndMaterial(0x1f, 4);
        configured187->setDescriptionId(StringIDs::GoldIngot, StringIDs::AShinyIngotWhichCanBeUsedTo);
        registerItem(0x10a, name, item185);
    }
    {
        std::wstring name(L"iron_sword");
        auto* item188 = new SwordItem(Item::Tier::IRON);
        std::wstring icon(L"swordIron");
        auto* configured189 = item188->setIconName(icon);
        auto* configured190 = configured189->setBaseItemTypeAndMaterial(1, 3);
        configured190->setDescriptionId(StringIDs::IronSword, StringIDs::DealsMoreDamageThanByHand);
        registerItem(0x10b, name, item188);
    }
    {
        std::wstring name(L"wooden_sword");
        auto* item191 = new SwordItem(Item::Tier::WOOD);
        std::wstring icon(L"swordWood");
        auto* configured192 = item191->setIconName(icon);
        auto* configured193 = configured192->setBaseItemTypeAndMaterial(1, 1);
        configured193->setDescriptionId(StringIDs::WoodenSword, StringIDs::DealsMoreDamageThanByHand);
        registerItem(0x10c, name, item191);
    }
    {
        std::wstring name(L"wooden_shovel");
        auto* item194 = new ShovelItem(Item::Tier::WOOD);
        std::wstring icon(L"shovelWood");
        auto* configured195 = item194->setIconName(icon);
        auto* configured196 = configured195->setBaseItemTypeAndMaterial(2, 1);
        configured196->setDescriptionId(0xc9b0da1, StringIDs::UsedToDigDirtGrassSandGravelAnd);
        registerItem(0x10d, name, item194);
    }
    {
        std::wstring name(L"wooden_pickaxe");
        auto* item197 = new PickaxeItem(Item::Tier::WOOD);
        std::wstring icon(L"pickaxeWood");
        auto* configured198 = item197->setIconName(icon);
        auto* configured199 = configured198->setBaseItemTypeAndMaterial(3, 1);
        configured199->setDescriptionId(StringIDs::WoodenPickaxe,
                                        StringIDs::RequiredToMineStoneRelatedBlocksAndOre);
        registerItem(0x10e, name, item197);
    }
    {
        std::wstring name(L"wooden_axe");
        auto* item200 = new AxeItem(Item::Tier::WOOD);
        std::wstring icon(L"hatchetWood");
        auto* configured201 = item200->setIconName(icon);
        auto* configured202 = configured201->setBaseItemTypeAndMaterial(4, 1);
        configured202->setDescriptionId(StringIDs::WoodenAxe,
                                        StringIDs::UsedToChopWoodRelatedBlocksFasterThan);
        registerItem(0x10f, name, item200);
    }
    {
        std::wstring name(L"stone_sword");
        auto* item203 = new SwordItem(Item::Tier::STONE);
        std::wstring icon(L"swordStone");
        auto* configured204 = item203->setIconName(icon);
        auto* configured205 = configured204->setBaseItemTypeAndMaterial(1, 2);
        configured205->setDescriptionId(StringIDs::StoneSword, StringIDs::DealsMoreDamageThanByHand);
        registerItem(0x110, name, item203);
    }
    {
        std::wstring name(L"stone_shovel");
        auto* item206 = new ShovelItem(Item::Tier::STONE);
        std::wstring icon(L"shovelStone");
        auto* configured207 = item206->setIconName(icon);
        auto* configured208 = configured207->setBaseItemTypeAndMaterial(2, 2);
        configured208->setDescriptionId(StringIDs::StoneShovel, StringIDs::UsedToDigDirtGrassSandGravelAnd);
        registerItem(0x111, name, item206);
    }
    {
        std::wstring name(L"stone_pickaxe");
        auto* item209 = new PickaxeItem(Item::Tier::STONE);
        std::wstring icon(L"pickaxeStone");
        auto* configured210 = item209->setIconName(icon);
        auto* configured211 = configured210->setBaseItemTypeAndMaterial(3, 2);
        configured211->setDescriptionId(StringIDs::StonePickaxe,
                                        StringIDs::RequiredToMineStoneRelatedBlocksAndOre);
        registerItem(0x112, name, item209);
    }
    {
        std::wstring name(L"stone_axe");
        auto* item212 = new AxeItem(Item::Tier::STONE);
        std::wstring icon(L"hatchetStone");
        auto* configured213 = item212->setIconName(icon);
        auto* configured214 = configured213->setBaseItemTypeAndMaterial(4, 2);
        configured214->setDescriptionId(StringIDs::StoneAxe,
                                        StringIDs::UsedToChopWoodRelatedBlocksFasterThan);
        registerItem(0x113, name, item212);
    }
    {
        std::wstring name(L"diamond_sword");
        auto* item215 = new SwordItem(Item::Tier::DIAMOND);
        std::wstring icon(L"swordDiamond");
        auto* configured216 = item215->setIconName(icon);
        auto* configured217 = configured216->setBaseItemTypeAndMaterial(1, 5);
        configured217->setDescriptionId(StringIDs::DiamondSword, StringIDs::DealsMoreDamageThanByHand);
        registerItem(0x114, name, item215);
    }
    {
        std::wstring name(L"diamond_shovel");
        auto* item218 = new ShovelItem(Item::Tier::DIAMOND);
        std::wstring icon(L"shovelDiamond");
        auto* configured219 = item218->setIconName(icon);
        auto* configured220 = configured219->setBaseItemTypeAndMaterial(2, 5);
        configured220->setDescriptionId(StringIDs::DiamondShovel, StringIDs::UsedToDigDirtGrassSandGravelAnd);
        registerItem(0x115, name, item218);
    }
    {
        std::wstring name(L"diamond_pickaxe");
        auto* item221 = new PickaxeItem(Item::Tier::DIAMOND);
        std::wstring icon(L"pickaxeDiamond");
        auto* configured222 = item221->setIconName(icon);
        auto* configured223 = configured222->setBaseItemTypeAndMaterial(3, 5);
        configured223->setDescriptionId(StringIDs::DiamondPickaxe,
                                        StringIDs::RequiredToMineStoneRelatedBlocksAndOre);
        registerItem(0x116, name, item221);
    }
    {
        std::wstring name(L"diamond_axe");
        auto* item224 = new AxeItem(Item::Tier::DIAMOND);
        std::wstring icon(L"hatchetDiamond");
        auto* configured225 = item224->setIconName(icon);
        auto* configured226 = configured225->setBaseItemTypeAndMaterial(4, 5);
        configured226->setDescriptionId(StringIDs::DiamondAxe,
                                        StringIDs::UsedToChopWoodRelatedBlocksFasterThan);
        registerItem(0x117, name, item224);
    }
    {
        std::wstring name(L"stick");
        auto* item227 = new Item();
        std::wstring icon(L"stick");
        auto* configured228 = item227->setIconName(icon);
        auto* configured229 = configured228->setHandEquipped();
        auto* configured230 = configured229->setDescriptionId(
            StringIDs::Stick, StringIDs::UsedToCraftTorchesArrowsSignsLaddersFences);
        configured230->setBaseItemTypeAndMaterial(0x30, 1);
        registerItem(0x118, name, item227);
    }
    {
        std::wstring name(L"bowl");
        auto* item231 = new Item();
        std::wstring icon(L"bowl");
        auto* configured232 = item231->setIconName(icon);
        auto* configured233 = configured232->setBaseItemTypeAndMaterial(0x1a, 1);
        auto* configured234 = configured233->setDescriptionId(
            StringIDs::Bowl, StringIDs::UsedToHoldMushroomStewAndBeetrootSoup);
        configured234->setMaxStackSize(0x40);
        registerItem(0x119, name, item231);
    }
    {
        std::wstring name(L"mushroom_stew");
        auto* item235 = new BowlFoodItem(6);
        std::wstring icon(L"mushroomStew");
        auto* configured236 = item235->setIconName(icon);
        auto* configured237 = configured236->setBaseItemTypeAndMaterial(0x27, 0);
        configured237->setDescriptionId(StringIDs::MushroomStew, StringIDs::Restores3IconShank01);
        registerItem(0x11a, name, item235);
    }
    {
        std::wstring name(L"golden_sword");
        auto* item238 = new SwordItem(Item::Tier::GOLD);
        std::wstring icon(L"swordGold");
        auto* configured239 = item238->setIconName(icon);
        auto* configured240 = configured239->setBaseItemTypeAndMaterial(1, 4);
        configured240->setDescriptionId(StringIDs::GoldenSword, StringIDs::DealsMoreDamageThanByHand);
        registerItem(0x11b, name, item238);
    }
    {
        std::wstring name(L"golden_shovel");
        auto* item241 = new ShovelItem(Item::Tier::GOLD);
        std::wstring icon(L"shovelGold");
        auto* configured242 = item241->setIconName(icon);
        auto* configured243 = configured242->setBaseItemTypeAndMaterial(2, 4);
        configured243->setDescriptionId(StringIDs::GoldenShovel, StringIDs::UsedToDigDirtGrassSandGravelAnd);
        registerItem(0x11c, name, item241);
    }
    {
        std::wstring name(L"golden_pickaxe");
        auto* item244 = new PickaxeItem(Item::Tier::GOLD);
        std::wstring icon(L"pickaxeGold");
        auto* configured245 = item244->setIconName(icon);
        auto* configured246 = configured245->setBaseItemTypeAndMaterial(3, 4);
        configured246->setDescriptionId(StringIDs::GoldenPickaxe,
                                        StringIDs::RequiredToMineStoneRelatedBlocksAndOre);
        registerItem(0x11d, name, item244);
    }
    {
        std::wstring name(L"golden_axe");
        auto* item247 = new AxeItem(Item::Tier::GOLD);
        std::wstring icon(L"hatchetGold");
        auto* configured248 = item247->setIconName(icon);
        auto* configured249 = configured248->setBaseItemTypeAndMaterial(4, 4);
        configured249->setDescriptionId(StringIDs::GoldenAxe,
                                        StringIDs::UsedToChopWoodRelatedBlocksFasterThan);
        registerItem(0x11e, name, item247);
    }
    {
        std::wstring name(L"string");
        auto* item250 = new BlockPlanterItem(Blocks::TRIPWIRE);
        std::wstring icon(L"string");
        auto* configured251 = item250->setIconName(icon);
        configured251->setDescriptionId(StringIDs::String, StringIDs::CollectedByKillingASpiderCanBeCrafted);
        registerItem(0x11f, name, item250);
    }
    {
        std::wstring name(L"feather");
        auto* item252 = new Item();
        std::wstring icon(L"feather");
        auto* configured253 = item252->setIconName(icon);
        configured253->setDescriptionId(StringIDs::Feather,
                                        StringIDs::CollectedByKillingAChickenCanBeCrafted);
        registerItem(0x120, name, item252);
    }
    {
        std::wstring name(L"gunpowder");
        auto* item254 = new Item();
        std::wstring icon(L"sulphur");
        auto* configured255 = item254->setIconName(icon);
        configured255->setDescriptionId(StringIDs::Gunpowder,
                                        StringIDs::CollectedByKillingACreeperCanBeCrafted);
        registerItem(0x121, name, item254);
    }
    {
        std::wstring name(L"wooden_hoe");
        auto* item256 = new HoeItem(Item::Tier::WOOD);
        std::wstring icon(L"hoeWood");
        auto* configured257 = item256->setIconName(icon);
        configured257->setBaseItemTypeAndMaterial(5, 1);
        item256->setDescriptionId(StringIDs::WoodenHoe, StringIDs::UsedToTillDirtAndGrassBlocksTo);
        registerItem(0x122, name, item256);
    }
    {
        std::wstring name(L"stone_hoe");
        auto* item258 = new HoeItem(Item::Tier::STONE);
        std::wstring icon(L"hoeStone");
        auto* configured259 = item258->setIconName(icon);
        auto* configured260 = configured259->setBaseItemTypeAndMaterial(5, 2);
        configured260->setDescriptionId(StringIDs::StoneHoe, StringIDs::UsedToTillDirtAndGrassBlocksTo);
        registerItem(0x123, name, item258);
    }
    {
        std::wstring name(L"iron_hoe");
        auto* item261 = new HoeItem(Item::Tier::IRON);
        std::wstring icon(L"hoeIron");
        auto* configured262 = item261->setIconName(icon);
        auto* configured263 = configured262->setBaseItemTypeAndMaterial(5, 3);
        configured263->setDescriptionId(StringIDs::IronHoe, StringIDs::UsedToTillDirtAndGrassBlocksTo);
        registerItem(0x124, name, item261);
    }
    {
        std::wstring name(L"diamond_hoe");
        auto* item264 = new HoeItem(Item::Tier::DIAMOND);
        std::wstring icon(L"hoeDiamond");
        auto* configured265 = item264->setIconName(icon);
        auto* configured266 = configured265->setBaseItemTypeAndMaterial(5, 5);
        configured266->setDescriptionId(StringIDs::DiamondHoe, StringIDs::UsedToTillDirtAndGrassBlocksTo);
        registerItem(0x125, name, item264);
    }
    {
        std::wstring name(L"golden_hoe");
        auto* item267 = new HoeItem(Item::Tier::GOLD);
        std::wstring icon(L"hoeGold");
        auto* configured268 = item267->setIconName(icon);
        auto* configured269 = configured268->setBaseItemTypeAndMaterial(5, 4);
        configured269->setDescriptionId(0xf2c415b, StringIDs::UsedToTillDirtAndGrassBlocksTo);
        registerItem(0x126, name, item267);
    }
    {
        std::wstring name(L"wheat_seeds");
        auto* item270 = new SeedItem(Blocks::WHEAT, Blocks::FARMLAND);
        std::wstring icon(L"seeds");
        auto* configured271 = item270->setIconName(icon);
        configured271->setDescriptionId(StringIDs::Seeds, StringIDs::CanBePlantedInFarmlandToGrowCrops);
        registerItem(0x127, name, item270);
    }
    {
        std::wstring name(L"wheat");
        auto* item272 = new Item();
        std::wstring icon(L"wheat");
        auto* configured273 = item272->setIconName(icon);
        auto* configured274 = configured273->setBaseItemTypeAndMaterial(0x1f, 0x35);
        configured274->setDescriptionId(StringIDs::Wheat, StringIDs::HarvestedFromCropsCanBeUsedToCraft);
        registerItem(0x128, name, item272);
    }
    {
        std::wstring name(L"bread");
        auto* item275 = new FoodItem(5, 0.6f, 0);
        std::wstring icon(L"bread");
        auto* configured276 = item275->setIconName(icon);
        configured276->setDescriptionId(StringIDs::Bread, StringIDs::Restores25IconShank01);
        registerItem(0x129, name, item275);
    }
    {
        std::wstring name(L"leather_helmet");
        auto* item277 = new ArmorItem(ArmorItem::ArmorMaterial::LEATHER, 0, EquipmentSlot::HEAD);
        std::wstring icon(L"helmetCloth");
        auto* configured278 = item277->setIconName(icon);
        auto* configured279 = configured278->setBaseItemTypeAndMaterial(7, 6);
        configured279->setDescriptionId(StringIDs::LeatherCap, StringIDs::GivesUser05IconArmor01WhenWorn_3);
        registerItem(0x12a, name, item277);
    }
    {
        std::wstring name(L"leather_chestplate");
        auto* item280 = new ArmorItem(ArmorItem::ArmorMaterial::LEATHER, 0, EquipmentSlot::CHEST);
        std::wstring icon(L"chestplateCloth");
        auto* configured281 = item280->setIconName(icon);
        auto* configured282 = configured281->setBaseItemTypeAndMaterial(8, 6);
        configured282->setDescriptionId(StringIDs::LeatherTunic, 0x5e7b53b);
        registerItem(299, name, item280);
    }
    {
        std::wstring name(L"leather_leggings");
        auto* item283 = new ArmorItem(ArmorItem::ArmorMaterial::LEATHER, 0, EquipmentSlot::LEGS);
        std::wstring icon(L"leggingsCloth");
        auto* configured284 = item283->setIconName(icon);
        auto* configured285 = configured284->setBaseItemTypeAndMaterial(9, 6);
        configured285->setDescriptionId(StringIDs::LeatherPants, 0xf1b63f4);
        registerItem(300, name, item283);
    }
    {
        std::wstring name(L"leather_boots");
        auto* item286 = new ArmorItem(ArmorItem::ArmorMaterial::LEATHER, 0, EquipmentSlot::FEET);
        std::wstring icon(L"bootsCloth");
        item286->setIconName(icon);
        auto* configured287 = item286->setBaseItemTypeAndMaterial(10, 6);
        configured287->setDescriptionId(StringIDs::LeatherBoots, StringIDs::GivesUser05IconArmor01WhenWorn_2);
        registerItem(0x12d, name, item286);
    }
    {
        std::wstring name(L"chainmail_helmet");
        auto* item288 = new ArmorItem(ArmorItem::ArmorMaterial::CHAIN, 1, EquipmentSlot::HEAD);
        std::wstring icon(L"helmetChain");
        auto* configured289 = item288->setIconName(icon);
        auto* configured290 = configured289->setBaseItemTypeAndMaterial(7, 7);
        configured290->setDescriptionId(0x7003b21, StringIDs::GivesUser1IconArmor01WhenWorn_1);
        registerItem(0x12e, name, item288);
    }
    {
        std::wstring name(L"chainmail_chestplate");
        auto* item291 = new ArmorItem(ArmorItem::ArmorMaterial::CHAIN, 1, EquipmentSlot::CHEST);
        std::wstring icon(L"chestplateChain");
        auto* configured292 = item291->setIconName(icon);
        auto* configured293 = configured292->setBaseItemTypeAndMaterial(8, 7);
        configured293->setDescriptionId(0x128eb51, StringIDs::GivesUser25IconArmor01WhenWorn);
        registerItem(0x12f, name, item291);
    }
    {
        std::wstring name(L"chainmail_leggings");
        auto* item294 = new ArmorItem(ArmorItem::ArmorMaterial::CHAIN, 1, EquipmentSlot::LEGS);
        std::wstring icon(L"leggingsChain");
        auto* configured295 = item294->setIconName(icon);
        auto* configured296 = configured295->setBaseItemTypeAndMaterial(9, 7);
        configured296->setDescriptionId(StringIDs::ChainLeggings, StringIDs::GivesUser2IconArmor01WhenWorn);
        registerItem(0x130, name, item294);
    }
    {
        std::wstring name(L"chainmail_boots");
        auto* item297 = new ArmorItem(ArmorItem::ArmorMaterial::CHAIN, 1, EquipmentSlot::FEET);
        std::wstring icon(L"bootsChain");
        auto* configured298 = item297->setIconName(icon);
        auto* configured299 = configured298->setBaseItemTypeAndMaterial(10, 7);
        configured299->setDescriptionId(StringIDs::ChainBoots, StringIDs::GivesUser05IconArmor01WhenWorn);
        registerItem(0x131, name, item297);
    }
    {
        std::wstring name(L"iron_helmet");
        auto* item300 = new ArmorItem(ArmorItem::ArmorMaterial::IRON, 2, EquipmentSlot::HEAD);
        std::wstring icon(L"helmetIron");
        auto* configured301 = item300->setIconName(icon);
        auto* configured302 = configured301->setBaseItemTypeAndMaterial(7, 3);
        configured302->setDescriptionId(0xd8ed8c6, StringIDs::GivesUser1IconArmor01WhenWorn_3);
        registerItem(0x132, name, item300);
    }
    {
        std::wstring name(L"iron_chestplate");
        auto* item303 = new ArmorItem(ArmorItem::ArmorMaterial::IRON, 2, EquipmentSlot::CHEST);
        std::wstring icon(L"chestplateIron");
        auto* configured304 = item303->setIconName(icon);
        auto* configured305 = configured304->setBaseItemTypeAndMaterial(8, 3);
        configured305->setDescriptionId(StringIDs::IronChestplate, 0x9958b2a);
        registerItem(0x133, name, item303);
    }
    {
        std::wstring name(L"iron_leggings");
        auto* item306 = new ArmorItem(ArmorItem::ArmorMaterial::IRON, 2, EquipmentSlot::LEGS);
        std::wstring icon(L"leggingsIron");
        auto* configured307 = item306->setIconName(icon);
        auto* configured308 = configured307->setBaseItemTypeAndMaterial(9, 3);
        configured308->setDescriptionId(StringIDs::IronLeggings, 0xfa8857d);
        registerItem(0x134, name, item306);
    }
    {
        std::wstring name(L"iron_boots");
        auto* item309 = new ArmorItem(ArmorItem::ArmorMaterial::IRON, 2, EquipmentSlot::FEET);
        std::wstring icon(L"bootsIron");
        auto* configured310 = item309->setIconName(icon);
        auto* configured311 = configured310->setBaseItemTypeAndMaterial(10, 3);
        configured311->setDescriptionId(StringIDs::IronBoots, StringIDs::GivesUser1IconArmor01WhenWorn);
        registerItem(0x135, name, item309);
    }
    {
        std::wstring name(L"diamond_helmet");
        auto* item312 = new ArmorItem(ArmorItem::ArmorMaterial::DIAMOND, 3, EquipmentSlot::HEAD);
        std::wstring icon(L"helmetDiamond");
        auto* configured313 = item312->setIconName(icon);
        auto* configured314 = configured313->setBaseItemTypeAndMaterial(7, 5);
        configured314->setDescriptionId(0x1a29bf8, StringIDs::GivesUser15IconArmor01WhenWorn_2);
        registerItem(0x136, name, item312);
    }
    {
        std::wstring name(L"diamond_chestplate");
        auto* item315 = new ArmorItem(ArmorItem::ArmorMaterial::DIAMOND, 3, EquipmentSlot::CHEST);
        std::wstring icon(L"chestplateDiamond");
        auto* configured316 = item315->setIconName(icon);
        auto* configured317 = configured316->setBaseItemTypeAndMaterial(8, 5);
        configured317->setDescriptionId(StringIDs::DiamondChestplate,
                                        StringIDs::GivesUser4IconArmor01WhenWorn);
        registerItem(0x137, name, item315);
    }
    {
        std::wstring name(L"diamond_leggings");
        auto* item318 = new ArmorItem(ArmorItem::ArmorMaterial::DIAMOND, 3, EquipmentSlot::LEGS);
        std::wstring icon(L"leggingsDiamond");
        auto* configured319 = item318->setIconName(icon);
        auto* configured320 = configured319->setBaseItemTypeAndMaterial(9, 5);
        configured320->setDescriptionId(StringIDs::DiamondLeggings,
                                        StringIDs::GivesUser3IconArmor01WhenWorn_1);
        registerItem(0x138, name, item318);
    }
    {
        std::wstring name(L"diamond_boots");
        auto* item321 = new ArmorItem(ArmorItem::ArmorMaterial::DIAMOND, 3, EquipmentSlot::FEET);
        std::wstring icon(L"bootsDiamond");
        auto* configured322 = item321->setIconName(icon);
        auto* configured323 = configured322->setBaseItemTypeAndMaterial(10, 5);
        configured323->setDescriptionId(StringIDs::DiamondBoots, StringIDs::GivesUser15IconArmor01WhenWorn);
        registerItem(0x139, name, item321);
    }
    {
        std::wstring name(L"golden_helmet");
        auto* item324 = new ArmorItem(ArmorItem::ArmorMaterial::GOLD, 4, EquipmentSlot::HEAD);
        std::wstring icon(L"helmetGold");
        auto* configured325 = item324->setIconName(icon);
        auto* configured326 = configured325->setBaseItemTypeAndMaterial(7, 4);
        configured326->setDescriptionId(StringIDs::GoldenHelmet, StringIDs::GivesUser1IconArmor01WhenWorn_2);
        registerItem(0x13a, name, item324);
    }
    {
        std::wstring name(L"golden_chestplate");
        auto* item327 = new ArmorItem(ArmorItem::ArmorMaterial::GOLD, 4, EquipmentSlot::CHEST);
        std::wstring icon(L"chestplateGold");
        auto* configured328 = item327->setIconName(icon);
        auto* configured329 = configured328->setBaseItemTypeAndMaterial(8, 4);
        configured329->setDescriptionId(StringIDs::GoldenChestplate,
                                        StringIDs::GivesUser25IconArmor01WhenWorn_1);
        registerItem(0x13b, name, item327);
    }
    {
        std::wstring name(L"golden_leggings");
        auto* item330 = new ArmorItem(ArmorItem::ArmorMaterial::GOLD, 4, EquipmentSlot::LEGS);
        std::wstring icon(L"leggingsGold");
        auto* configured331 = item330->setIconName(icon);
        auto* configured332 = configured331->setBaseItemTypeAndMaterial(9, 4);
        configured332->setDescriptionId(StringIDs::GoldenLeggings, 0x9c244bf);
        registerItem(0x13c, name, item330);
    }
    {
        std::wstring name(L"golden_boots");
        auto* item333 = new ArmorItem(ArmorItem::ArmorMaterial::GOLD, 4, EquipmentSlot::FEET);
        std::wstring icon(L"bootsGold");
        auto* configured334 = item333->setIconName(icon);
        auto* configured335 = configured334->setBaseItemTypeAndMaterial(10, 4);
        configured335->setDescriptionId(StringIDs::GoldenBoots, StringIDs::GivesUser05IconArmor01WhenWorn_1);
        registerItem(0x13d, name, item333);
    }
    {
        std::wstring name(L"flint");
        auto* item336 = new Item();
        std::wstring icon(L"flint");
        auto* configured337 = item336->setIconName(icon);
        configured337->setDescriptionId(StringIDs::Flint, StringIDs::CollectedByDiggingGravelCanBeUsedTo);
        registerItem(0x13e, name, item336);
    }
    {
        std::wstring name(L"porkchop");
        auto* item338 = new FoodItem(3, 0.3f, 1);
        std::wstring icon(L"porkchopRaw");
        auto* configured339 = item338->setIconName(icon);
        configured339->setDescriptionId(StringIDs::RawPorkchop, StringIDs::Restores15IconShank01OrCan_1);
        registerItem(0x13f, name, item338);
    }
    {
        std::wstring name(L"cooked_porkchop");
        auto* item340 = new FoodItem(8, 0.8f, 1);
        std::wstring icon(L"porkchopCooked");
        auto* configured341 = item340->setIconName(icon);
        configured341->setDescriptionId(StringIDs::CookedPorkchop,
                                        StringIDs::Restores4IconShank01CreatedByCookingPorkchop);
        registerItem(0x140, name, item340);
    }
    {
        std::wstring name(L"painting");
        auto* item342 = new HangingEntityItem(static_cast<eINSTANCEOF>(0xa080001));
        std::wstring icon(L"painting");
        auto* configured343 = item342->setIconName(icon);
        auto* configured344 = configured343->setBaseItemTypeAndMaterial(0x22, 6);
        configured344->setDescriptionId(StringIDs::Painting, StringIDs::CanBeUsedAsDecoration_2);
        registerItem(0x141, name, item342);
    }
    {
        std::wstring name(L"golden_apple");
        auto* item345 = new GoldenAppleItem(4, 1.2f, 0);
        auto* food346 = item345->setAlwaysEat();
        std::wstring icon(L"appleGold");
        auto* configured347 = food346->setIconName(icon);
        auto* configured348 = configured347->setBaseItemTypeAndMaterial(0x26, 0x2e);
        configured348->setDescriptionId(StringIDs::GoldenApple);
        registerItem(0x142, name, food346);
    }
    {
        std::wstring name(L"sign");
        auto* item349 = new SignItem();
        std::wstring icon(L"sign");
        auto* configured350 = item349->setIconName(icon);
        auto* configured351 = configured350->setBaseItemTypeAndMaterial(0x22, 1);
        configured351->setDescriptionId(StringIDs::Sign, StringIDs::ShowsTextEnteredByYouOrOtherPlayers);
        registerItem(0x143, name, item349);
    }
    {
        std::wstring name(L"wooden_door");
        auto* item352 = new DoorItem(Blocks::WOODEN_DOOR);
        std::wstring icon(L"doorWood");
        auto* configured353 = item352->setIconName(icon);
        auto* configured354 = configured353->setBaseItemTypeAndMaterial(6, 1);
        configured354->setDescriptionId(StringIDs::OakDoor,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
        registerItem(0x144, name, item352);
    }
    auto* item355 = new BucketItem(Blocks::AIR);
    item355->setMaxStackSize(0x10);
    {
        std::wstring name(L"bucket");
        auto* configured356 = item355->setIconName(name);
        auto* configured357 = configured356->setBaseItemTypeAndMaterial(0x1a, 0x18);
        configured357->setDescriptionId(StringIDs::Bucket, StringIDs::UsedToHoldAndTransportWaterLavaAndMilk);
    }
    {
        std::wstring name(L"bucket");
        registerItem(0x145, name, item355);
    }
    {
        std::wstring name(L"water_bucket");
        auto* item358 = new BucketItem(Blocks::FLOWING_WATER);
        std::wstring icon(L"bucketWater");
        auto* configured359 = item358->setIconName(icon);
        auto* configured360
            = configured359->setDescriptionId(StringIDs::WaterBucket, StringIDs::UsedToHoldAndTransportWater);
        configured360->setCraftingRemainingItem(item355);
        registerItem(0x146, name, item358);
    }
    {
        std::wstring name(L"lava_bucket");
        auto* item361 = new BucketItem(Blocks::FLOWING_LAVA);
        std::wstring icon(L"bucketLava");
        auto* configured362 = item361->setIconName(icon);
        auto* configured363
            = configured362->setDescriptionId(StringIDs::LavaBucket, StringIDs::UsedToHoldAndTransportLava);
        configured363->setCraftingRemainingItem(item355);
        registerItem(0x147, name, item361);
    }
    {
        std::wstring name(L"minecart");
        auto* item364 = new MinecartItem(MinecartType::RIDEABLE);
        std::wstring icon(L"minecart");
        auto* configured365 = item364->setIconName(icon);
        configured365->setDescriptionId(StringIDs::Minecart_1, StringIDs::UsedToTransportYouAnAnimalOrA);
        registerItem(0x148, name, item364);
    }
    {
        std::wstring name(L"saddle");
        auto* item366 = new SaddleItem();
        std::wstring icon(L"saddle");
        auto* configured367 = item366->setIconName(icon);
        configured367->setDescriptionId(StringIDs::Saddle, StringIDs::WhenUsedOnAPigItAllowsYou);
        registerItem(0x149, name, item366);
    }
    {
        std::wstring name(L"iron_door");
        auto* item368 = new DoorItem(Blocks::IRON_DOOR);
        std::wstring icon(L"doorIron");
        auto* configured369 = item368->setIconName(icon);
        auto* configured370 = configured369->setBaseItemTypeAndMaterial(6, 3);
        configured370->setDescriptionId(StringIDs::IronDoor, StringIDs::IronDoorsCanOnlyBeOpenedByRedstone);
        registerItem(0x14a, name, item368);
    }
    {
        std::wstring name(L"redstone");
        auto* item371 = new RedStoneDustItem();
        std::wstring icon(L"redstone");
        auto* configured372 = item371->setIconName(icon);
        auto* configured373 = configured372->setBaseItemTypeAndMaterial(0x1f, 0x30);
        configured373->setDescriptionId(StringIDs::Redstone, StringIDs::CanBePlacedOnGroundToCarryAn);
        registerItem(0x14b, name, item371);
    }
    {
        std::wstring name(L"snowball");
        auto* item374 = new SnowballItem();
        std::wstring icon(L"snowball");
        auto* configured375 = item374->setIconName(icon);
        configured375->setDescriptionId(StringIDs::Snowball, StringIDs::CollectedByDiggingSnowCanBeThrown);
        registerItem(0x14c, name, item374);
    }
    {
        std::wstring name(L"boat");
        auto* item376 = new BoatItem(0);
        std::wstring icon(L"boat");
        auto* configured377 = item376->setIconName(icon);
        auto* configured378 = configured377->setDescriptionId(StringIDs::OakBoat,
                                                              StringIDs::UsedToTravelInWaterMoreQuicklyThan);
        configured378->setBaseItemTypeAndMaterial(0x37, 0x3f);
        registerItem(0x14d, name, item376);
    }
    {
        std::wstring name(L"leather");
        auto* item379 = new Item();
        std::wstring icon(L"leather");
        auto* configured380 = item379->setIconName(icon);
        auto* configured381 = configured380->setDescriptionId(StringIDs::Leather,
                                                              StringIDs::CollectedByKillingACowCanBeCrafted);
        configured381->setBaseItemTypeAndMaterial(0x35, 0);
        registerItem(0x14e, name, item379);
    }
    {
        std::wstring name(L"milk_bucket");
        auto* item382 = new MilkBucketItem();
        std::wstring icon(L"milk");
        auto* configured383 = item382->setIconName(icon);
        auto* configured384
            = configured383->setDescriptionId(StringIDs::MilkBucket, StringIDs::UsedToHoldAndTransportMilk);
        configured384->setCraftingRemainingItem(item355);
        registerItem(0x14f, name, item382);
    }
    {
        std::wstring name(L"brick");
        auto* item385 = new Item();
        std::wstring icon(L"brick");
        auto* configured386 = item385->setIconName(icon);
        configured386->setDescriptionId(StringIDs::Brick, 0x43fc433);
        registerItem(0x150, name, item385);
    }
    {
        std::wstring name(L"clay_ball");
        auto* item387 = new Item();
        std::wstring icon(L"clay");
        auto* configured388 = item387->setIconName(icon);
        configured388->setDescriptionId(StringIDs::Clay, StringIDs::CanBeBakedIntoBricksInAFurnace);
        registerItem(0x151, name, item387);
    }
    {
        std::wstring name(L"reeds");
        auto* item389 = new BlockPlanterItem(Blocks::REEDS);
        std::wstring icon(L"reeds");
        auto* configured390 = item389->setIconName(icon);
        configured390->setDescriptionId(StringIDs::SugarCanes, StringIDs::CanBeCraftedToCreateSugar);
        registerItem(0x152, name, item389);
    }
    {
        std::wstring name(L"paper");
        auto* item391 = new Item();
        std::wstring icon(L"paper");
        auto* configured392 = item391->setIconName(icon);
        auto* configured393 = configured392->setBaseItemTypeAndMaterial(0x2e, 0x32);
        configured393->setDescriptionId(StringIDs::Paper, StringIDs::UsedToCreateBooksMapsAndFireworks);
        registerItem(0x153, name, item391);
    }
    {
        std::wstring name(L"book");
        auto* item394 = new BookItem();
        std::wstring icon(L"book");
        auto* configured395 = item394->setIconName(icon);
        auto* configured396 = configured395->setBaseItemTypeAndMaterial(0x2e, 0x33);
        configured396->setDescriptionId(StringIDs::Book, StringIDs::CanBeUsedToCreateBookshelvesOrEnchanted);
        registerItem(0x154, name, item394);
    }
    {
        std::wstring name(L"slime_ball");
        auto* item397 = new Item();
        item397->setBaseItemTypeAndMaterial(0x1f, 0x39);
        std::wstring icon(L"slimeball");
        auto* configured398 = item397->setIconName(icon);
        configured398->setDescriptionId(StringIDs::Slimeball, 0x5db70ff);
        registerItem(0x155, name, item397);
    }
    {
        std::wstring name(L"chest_minecart");
        auto* item399 = new MinecartItem(MinecartType::CHEST);
        std::wstring icon(L"minecart_chest");
        auto* configured400 = item399->setIconName(icon);
        configured400->setDescriptionId(StringIDs::MinecartWithChest,
                                        StringIDs::UsedToTransportGoodsAlongRails);
        registerItem(0x156, name, item399);
    }
    {
        std::wstring name(L"furnace_minecart");
        auto* item401 = new MinecartItem(MinecartType::FURNACE);
        std::wstring icon(L"minecart_furnace");
        auto* configured402 = item401->setIconName(icon);
        configured402->setDescriptionId(StringIDs::MinecartWithFurnace,
                                        StringIDs::WillMoveAlongRailsAndCanPushOther);
        registerItem(0x157, name, item401);
    }
    {
        std::wstring name(L"egg");
        auto* item403 = new EggItem();
        std::wstring icon(L"egg");
        auto* configured404 = item403->setIconName(icon);
        configured404->setDescriptionId(StringIDs::Egg, StringIDs::DroppedRandomlyByChickensCanBeCraftedInto);
        registerItem(0x158, name, item403);
    }
    {
        std::wstring name(L"compass");
        auto* item405 = new CompassItem();
        std::wstring icon(L"compass");
        auto* configured406 = item405->setIconName(icon);
        auto* configured407 = configured406->setBaseItemTypeAndMaterial(0x19, 0x13);
        configured407->setDescriptionId(StringIDs::Compass, StringIDs::PointsToYourStartPoint);
        registerItem(0x159, name, item405);
    }
    {
        std::wstring name(L"fishing_rod");
        auto* item408 = new FishingRodItem();
        std::wstring icon(L"fishingRod");
        item408->setIconName(icon);
        auto* configured409 = item408->setBaseItemTypeAndMaterial(0x25, 1);
        configured409->setDescriptionId(StringIDs::FishingRod, StringIDs::UsedToCatchFish);
        registerItem(0x15a, name, item408);
    }
    {
        std::wstring name(L"clock");
        auto* item410 = new ClockItem();
        std::wstring icon(L"clock");
        auto* configured411 = item410->setIconName(icon);
        configured411->setBaseItemTypeAndMaterial(0x19, 0x14);
        item410->setDescriptionId(StringIDs::Clock, StringIDs::DisplaysPositionsOfSunAndMoon);
        registerItem(0x15b, name, item410);
    }
    {
        std::wstring name(L"glowstone_dust");
        auto* item412 = new Item();
        std::wstring icon(L"yellowDust");
        auto* configured413 = item412->setIconName(icon);
        configured413->setDescriptionId(StringIDs::GlowstoneDust,
                                        StringIDs::CollectedByMiningGlowstoneCanBeCraftedTo);
        registerItem(0x15c, name, item412);
    }
    {
        std::wstring name(L"fish");
        auto* item414 = new FishFoodItem(0);
        std::wstring icon(L"fishRaw");
        auto* configured415 = item414->setIconName(icon);
        auto* configured416 = configured415->setDescriptionId(
            0xb7484b1, StringIDs::Restores1IconShank01OrCanBeCanFedAnOcelotTame);
        configured416->setStackedByData(1);
        registerItem(0x15d, name, item414);
    }
    {
        std::wstring name(L"cooked_fish");
        auto* item417 = new FishFoodItem(1);
        std::wstring icon(L"fishCooked");
        auto* configured418 = item417->setIconName(icon);
        auto* configured419 = configured418->setDescriptionId(StringIDs::CookedFish,
                                                              StringIDs::Restores25IconShank01CreatedBy);
        configured419->setStackedByData(1);
        registerItem(0x15e, name, item417);
    }
    {
        std::wstring name(L"dye");
        auto* item420 = new DyeItem();
        std::wstring icon(L"dyePowder");
        auto* configured421 = item420->setIconName(icon);
        auto* configured422 = configured421->setBaseItemTypeAndMaterial(0x12, 0xc);
        configured422->setDescriptionId(StringIDs::DyePowder, 0xffffffff);
        registerItem(0x15f, name, item420);
    }
    {
        std::wstring name(L"bone");
        auto* item423 = new Item();
        std::wstring icon(L"bone");
        auto* configured424 = item423->setIconName(icon);
        auto* configured425 = configured424->setDescriptionId(
            StringIDs::Bone, StringIDs::CollectedByKillingASkeletonCanBeCrafted);
        configured425->setHandEquipped();
        registerItem(0x160, name, item423);
    }
    {
        std::wstring name(L"sugar");
        auto* item426 = new Item();
        std::wstring icon(L"sugar");
        auto* configured427 = item426->setIconName(icon);
        configured427->setDescriptionId(StringIDs::Sugar, StringIDs::UsedInCakeRecipeAndAsAnIngredient);
        registerItem(0x161, name, item426);
    }
    {
        std::wstring name(L"cake");
        auto* item428 = new BlockPlanterItem(Blocks::CAKE);
        std::wstring icon(L"cake");
        auto* configured429 = item428->setIconName(icon);
        configured429->setDescriptionId(StringIDs::Cake, StringIDs::Restores1IconShank01CanBeUsed7Times);
        registerItem(0x162, name, item428);
    }
    {
        std::wstring name(L"bed");
        auto* item430 = new BedItem();
        item430->setMaxStackSize(1);
        std::wstring icon(L"bed");
        auto* configured431 = item430->setIconName(icon);
        auto* configured432 = configured431->setBaseItemTypeAndMaterial(0x3a, 0x47);
        configured432->setDescriptionId(StringIDs::Bed, StringIDs::UsedToForwardTimeFromAnyTimeAt);
        registerItem(0x163, name, item430);
    }
    {
        std::wstring name(L"repeater");
        auto* item433 = new BlockPlanterItem(Blocks::UNPOWERED_REPEATER);
        std::wstring icon(L"diode");
        auto* configured434 = item433->setIconName(icon);
        auto* configured435 = configured434->setDescriptionId(StringIDs::RedstoneRepeater,
                                                              StringIDs::UsedInRedstoneCircuitsAsARepeaterA);
        configured435->setBaseItemTypeAndMaterial(0x3b, 0);
        registerItem(0x164, name, item433);
    }
    {
        std::wstring name(L"cookie");
        auto* item436 = new FoodItem(2, 0.1f, 0);
        std::wstring icon(L"cookie");
        auto* configured437 = item436->setIconName(icon);
        configured437->setDescriptionId(StringIDs::Cookie, StringIDs::Restores1IconShank01);
        registerItem(0x165, name, item436);
    }
    {
        std::wstring name(L"filled_map");
        auto* item438 = new MapItem();
        std::wstring icon(L"map");
        auto* configured439 = item438->setIconName(icon);
        auto* configured440 = configured439->setBaseItemTypeAndMaterial(0x19, 0x15);
        configured440->setDescriptionId(StringIDs::Map, StringIDs::WillCreateAnImageOfAnAreaExplored);
        registerItem(0x166, name, item438);
    }
    {
        std::wstring name(L"shears");
        auto* item441 = new ShearsItem();
        std::wstring icon(L"shears");
        auto* configured442 = item441->setIconName(icon);
        auto* configured443 = configured442->setBaseItemTypeAndMaterial(0x1c, 0x1b);
        configured443->setDescriptionId(0xa1c6b20, StringIDs::UsedToObtainWoolFromSheepAndHarvest);
        registerItem(0x167, name, item441);
    }
    {
        std::wstring name(L"melon");
        auto* item444 = new FoodItem(2, 0.3f, 0);
        std::wstring icon(L"melon");
        auto* configured445 = item444->setIconName(icon);
        configured445->setDescriptionId(StringIDs::MelonSlice, StringIDs::Restores1IconShank01_1);
        registerItem(0x168, name, item444);
    }
    {
        std::wstring name(L"pumpkin_seeds");
        auto* item446 = new SeedItem(Blocks::PUMPKIN_STEM, Blocks::FARMLAND);
        std::wstring icon(L"seeds_pumpkin");
        auto* configured447 = item446->setIconName(icon);
        auto* configured448 = configured447->setBaseItemTypeAndMaterial(0x21, 0x16);
        configured448->setDescriptionId(StringIDs::PumpkinSeeds, StringIDs::CanBePlantedToGrowPumpkins);
        registerItem(0x169, name, item446);
    }
    {
        std::wstring name(L"melon_seeds");
        auto* item449 = new SeedItem(Blocks::MELON_STEM, Blocks::FARMLAND);
        std::wstring icon(L"seeds_melon");
        auto* configured450 = item449->setIconName(icon);
        auto* configured451 = configured450->setBaseItemTypeAndMaterial(0x21, 0x25);
        configured451->setDescriptionId(StringIDs::MelonSeeds, StringIDs::CanBePlantedToGrowMelons);
        registerItem(0x16a, name, item449);
    }
    {
        std::wstring name(L"beef");
        auto* item452 = new FoodItem(3, 0.3f, 1);
        std::wstring icon(L"beefRaw");
        auto* configured453 = item452->setIconName(icon);
        configured453->setDescriptionId(StringIDs::RawBeef, StringIDs::Restores15IconShank01OrCan);
        registerItem(0x16b, name, item452);
    }
    {
        std::wstring name(L"cooked_beef");
        auto* item454 = new FoodItem(8, 0.8f, 1);
        std::wstring icon(L"beefCooked");
        auto* configured455 = item454->setIconName(icon);
        configured455->setDescriptionId(StringIDs::Steak, StringIDs::Restores4IconShank01CreatedByCooking);
        registerItem(0x16c, name, item454);
    }
    {
        std::wstring name(L"chicken");
        auto* item456 = new FoodItem(2, 0.3f, 1);
        auto* item457 = new MobEffectInstance(MobEffects::HUNGER, 600, 0);
        auto* food458 = item456->setEffect(item457, 0.3f);
        std::wstring icon(L"chickenRaw");
        auto* configured459 = food458->setIconName(icon);
        configured459->setDescriptionId(StringIDs::RawChicken, StringIDs::Restores1IconShank01OrCanBe);
        registerItem(0x16d, name, food458);
    }
    {
        std::wstring name(L"cooked_chicken");
        auto* item460 = new FoodItem(6, 0.6f, 1);
        std::wstring icon(L"chickenCooked");
        auto* configured461 = item460->setIconName(icon);
        configured461->setDescriptionId(StringIDs::CookedChicken,
                                        StringIDs::Restores3IconShank01CreatedByCooking);
        registerItem(0x16e, name, item460);
    }
    {
        std::wstring name(L"rotten_flesh");
        auto* item462 = new FoodItem(4, 0.1f, 1);
        auto* item463 = new MobEffectInstance(MobEffects::HUNGER, 600, 0);
        auto* food464 = item462->setEffect(item463, 0.8f);
        std::wstring icon(L"rottenFlesh");
        auto* configured465 = food464->setIconName(icon);
        configured465->setDescriptionId(StringIDs::RottenFlesh, StringIDs::Restores2IconShank01EatingThisCan);
        registerItem(0x16f, name, food464);
    }
    {
        std::wstring name(L"ender_pearl");
        auto* item466 = new EnderpearlItem();
        std::wstring icon(L"enderPearl");
        auto* configured467 = item466->setIconName(icon);
        configured467->setDescriptionId(StringIDs::EnderPearl,
                                        StringIDs::DroppedByEndermenWhenyDieThrowingAnEnder);
        registerItem(0x170, name, item466);
    }
    {
        std::wstring name(L"blaze_rod");
        auto* item468 = new Item();
        std::wstring icon(L"blazeRod");
        auto* configured469 = item468->setIconName(icon);
        auto* configured470 = configured469->setDescriptionId(
            StringIDs::BlazeRod, StringIDs::UsedInPotionBrewingAndForLocatingStrongholds);
        configured470->setHandEquipped();
        registerItem(0x171, name, item468);
    }
    {
        std::wstring name(L"ghast_tear");
        auto* item471 = new Item();
        std::wstring icon(L"ghastTear");
        auto* configured472 = item471->setIconName(icon);
        configured472->setDescriptionId(StringIDs::GhastTear,
                                        StringIDs::UsedInPotionBrewingDroppedByGhastsWheny);
        registerItem(0x172, name, item471);
    }
    {
        std::wstring name(L"gold_nugget");
        auto* item473 = new Item();
        std::wstring icon(L"goldNugget");
        auto* configured474 = item473->setIconName(icon);
        auto* configured475 = configured474->setBaseItemTypeAndMaterial(0x1f, 4);
        configured475->setDescriptionId(StringIDs::GoldNugget,
                                        StringIDs::DroppedByZombiePigmenWhenyDieZombiePigmen);
        registerItem(0x173, name, item473);
    }
    {
        std::wstring name(L"nether_wart");
        auto* item476 = new SeedItem(Blocks::NETHER_WART, Blocks::SOUL_SAND);
        std::wstring icon(L"netherStalkSeeds");
        auto* configured477 = item476->setIconName(icon);
        configured477->setDescriptionId(StringIDs::NetherWart, StringIDs::UsedInPotionBrewingThisCanBeFound);
        registerItem(0x174, name, item476);
    }
    {
        std::wstring name(L"potion");
        auto* item478 = new PotionItem();
        std::wstring icon(L"potion");
        auto* configured479 = item478->setIconName(icon);
        configured479->setDescriptionId(0xae6088d, StringIDs::WhenUsedCanHaveVariousEffectsDependingOn);
        registerItem(0x175, name, item478);
    }
    auto* item480 = new BottleItem();
    {
        std::wstring name(L"glassBottle");
        auto* configured481 = item480->setIconName(name);
        configured481->setBaseItemTypeAndMaterial(0x1a, 0x22);
        item480->setDescriptionId(StringIDs::GlassBottle, StringIDs::CanBeFilledWithWaterAndUsedAs);
    }
    {
        std::wstring name(L"glass_bottle");
        registerItem(0x176, name, item480);
    }
    {
        std::wstring name(L"spider_eye");
        auto* item482 = new FoodItem(2, 0.8f, 0);
        auto* item483 = new MobEffectInstance(MobEffects::POISON, 100, 0);
        auto* food484 = item482->setEffect(item483, 1.0f);
        std::wstring icon(L"spiderEye");
        auto* configured485 = food484->setIconName(icon);
        configured485->setDescriptionId(StringIDs::SpiderEye, StringIDs::ThisIsAPoisonousFoodAndBrewingItem);
        registerItem(0x177, name, food484);
    }
    {
        std::wstring name(L"fermented_spider_eye");
        auto* item486 = new Item();
        std::wstring icon(L"fermentedSpiderEye");
        auto* configured487 = item486->setIconName(icon);
        configured487->setDescriptionId(StringIDs::FermentedSpiderEye,
                                        StringIDs::UsedInPotionBrewingMainlyToCreatePotions);
        registerItem(0x178, name, item486);
    }
    {
        std::wstring name(L"blaze_powder");
        auto* item488 = new Item();
        std::wstring icon(L"blazePowder");
        auto* configured489 = item488->setIconName(icon);
        configured489->setDescriptionId(StringIDs::BlazePowder,
                                        StringIDs::UsedInPotionBrewingOrCraftedWithOther);
        registerItem(0x179, name, item488);
    }
    {
        std::wstring name(L"magma_cream");
        auto* item490 = new Item();
        std::wstring icon(L"magmaCream");
        auto* configured491 = item490->setIconName(icon);
        configured491->setDescriptionId(StringIDs::MagmaCream, StringIDs::UsedInPotionBrewing);
        registerItem(0x17a, name, item490);
    }
    {
        std::wstring name(L"brewing_stand");
        auto* item492 = new BlockPlanterItem(Blocks::BREWING_STAND);
        std::wstring icon(L"brewingStand");
        auto* configured493 = item492->setIconName(icon);
        auto* configured494 = configured493->setBaseItemTypeAndMaterial(0x1e, 0x23);
        configured494->setDescriptionId(StringIDs::BrewingStand_1,
                                        StringIDs::UsedForMakingPotionsAndSplashPotions);
        registerItem(0x17b, name, item492);
    }
    {
        std::wstring name(L"cauldron");
        auto* item495 = new BlockPlanterItem(Blocks::CAULDRON);
        std::wstring icon(L"cauldron");
        auto* configured496 = item495->setIconName(icon);
        auto* configured497 = configured496->setBaseItemTypeAndMaterial(0x1a, 3);
        configured497->setDescriptionId(0x5a1ba3a, StringIDs::UsedToMixDyesAndDyeArmorOr);
        registerItem(0x17c, name, item495);
    }
    {
        std::wstring name(L"ender_eye");
        auto* item498 = new EnderEyeItem();
        std::wstring icon(L"eyeOfEnder");
        auto* configured499 = item498->setIconName(icon);
        auto* configured500 = configured499->setBaseItemTypeAndMaterial(0x19, 0x21);
        configured500->setDescriptionId(StringIDs::EyeOfEnder, StringIDs::WhenThrownWillShowDirectionToAnEnd);
        registerItem(0x17d, name, item498);
    }
    {
        std::wstring name(L"speckled_melon");
        auto* item501 = new Item();
        std::wstring icon(L"speckledMelon");
        auto* configured502 = item501->setIconName(icon);
        auto* configured503 = configured502->setBaseItemTypeAndMaterial(0x26, 0x25);
        configured503->setDescriptionId(StringIDs::GlisteringMelon, StringIDs::UsedInPotionBrewing_1);
        registerItem(0x17e, name, item501);
    }
    {
        std::wstring name(L"spawn_egg");
        auto* item504 = new SpawnEggItem();
        std::wstring icon(L"monsterPlacer");
        auto* configured505 = item504->setIconName(icon);
        configured505->setDescriptionId(StringIDs::SpawnCreature,
                                        StringIDs::WhenThrownCanSpawnACreatureOfType);
        registerItem(0x17f, name, item504);
    }
    {
        std::wstring name(L"experience_bottle");
        auto* item506 = new ExperienceBottleItem();
        std::wstring icon(L"expBottle");
        auto* configured507 = item506->setIconName(icon);
        configured507->setDescriptionId(StringIDs::BottleOEnchanting,
                                        StringIDs::WhenThrownItDropsExperienceOrbsWhichIncrease);
        registerItem(0x180, name, item506);
    }
    {
        std::wstring name(L"fire_charge");
        auto* item508 = new FireChargeItem();
        std::wstring icon(L"fireball");
        auto* configured509 = item508->setIconName(icon);
        auto* configured510 = configured509->setBaseItemTypeAndMaterial(0x17, 0x26);
        configured510->setDescriptionId(StringIDs::FireCharge, StringIDs::UsefulForSettingThingsOnFireOrFor);
        registerItem(0x181, name, item508);
    }
    {
        std::wstring name(L"writable_book");
        auto* item511 = new WritableBookItem();
        std::wstring icon(L"writingBook");
        auto* configured512 = item511->setIconName(icon);
        auto* configured513 = configured512->setBaseItemTypeAndMaterial(0x2e, 0x33);
        configured513->setDescriptionId(StringIDs::BookAndQuill, StringIDs::ABookThatCanBeWrittenIn);
        registerItem(0x182, name, item511);
    }
    {
        std::wstring name(L"written_book");
        auto* item514 = new WrittenBookItem();
        std::wstring icon(L"writtenBook");
        auto* configured515 = item514->setIconName(icon);
        auto* configured516 = configured515->setDescriptionId(
            StringIDs::WrittenBook, StringIDs::ABookSignedByAuthorCannotBeWrittenIn);
        configured516->setMaxStackSize(0x10);
        registerItem(0x183, name, item514);
    }
    {
        std::wstring name(L"emerald");
        auto* item517 = new Item();
        std::wstring icon(L"emerald");
        item517->setIconName(icon);
        auto* configured518 = item517->setBaseItemTypeAndMaterial(0x1f, 0x2c);
        configured518->setDescriptionId(StringIDs::Emerald, StringIDs::CanBeTradedWithVillagers);
        registerItem(0x184, name, item517);
    }
    {
        std::wstring name(L"item_frame");
        auto* item519 = new HangingEntityItem(static_cast<eINSTANCEOF>(0xa080002));
        std::wstring icon(L"frame");
        auto* configured520 = item519->setIconName(icon);
        auto* configured521 = configured520->setBaseItemTypeAndMaterial(0x22, 0x22);
        configured521->setDescriptionId(StringIDs::ItemFrame,
                                        StringIDs::SimilarToADisplayCaseThisWillDisplay);
        registerItem(0x185, name, item519);
    }
    {
        std::wstring name(L"flower_pot");
        auto* item522 = new BlockPlanterItem(Blocks::FLOWER_POT);
        std::wstring icon(L"flowerPot");
        auto* configured523 = item522->setIconName(icon);
        auto* configured524 = configured523->setDescriptionId(
            StringIDs::FlowerPot, StringIDs::UsedAsADecorationFlowersSaplingsCactiAnd);
        configured524->setBaseItemTypeAndMaterial(0x35, 0);
        registerItem(0x186, name, item522);
    }
    {
        std::wstring name(L"carrot");
        auto* item525 = new SeedFoodItem(3, 0.6f, Blocks::CARROTS, Blocks::FARMLAND);
        std::wstring icon(L"carrots");
        auto* configured526 = item525->setIconName(icon);
        configured526->setDescriptionId(StringIDs::Carrot, StringIDs::Restores15IconShank01AndCan);
        registerItem(0x187, name, item525);
    }
    {
        std::wstring name(L"potato");
        auto* item527 = new SeedFoodItem(1, 0.3f, Blocks::POTATOES, Blocks::FARMLAND);
        std::wstring icon(L"potato");
        auto* configured528 = item527->setIconName(icon);
        configured528->setDescriptionId(StringIDs::Potato, StringIDs::Restores05IconShank01OrCan);
        registerItem(0x188, name, item527);
    }
    {
        std::wstring name(L"baked_potato");
        auto* item529 = new FoodItem(5, 0.6f, 0);
        std::wstring icon(L"potatoBaked");
        auto* configured530 = item529->setIconName(icon);
        configured530->setDescriptionId(0x9bbf079, StringIDs::Restores25IconShank01CreatedByPotato);
        registerItem(0x189, name, item529);
    }
    {
        std::wstring name(L"poisonous_potato");
        auto* item531 = new FoodItem(2, 0.3f, 0);
        auto* item532 = new MobEffectInstance(MobEffects::POISON, 100, 0);
        auto* food533 = item531->setEffect(item532, 0.6f);
        std::wstring icon(L"potatoPoisonous");
        auto* configured534 = food533->setIconName(icon);
        configured534->setDescriptionId(StringIDs::PoisonousPotato,
                                        StringIDs::Restores1IconShank01EatingThisCan);
        registerItem(0x18a, name, food533);
    }
    {
        std::wstring name(L"map");
        auto* item535 = new EmptyMapItem();
        std::wstring icon(L"map_empty");
        auto* configured536 = item535->setIconName(icon);
        configured536->setBaseItemTypeAndMaterial(0x19, 0x15);
        item535->setDescriptionId(StringIDs::EmptyMap, StringIDs::WhenUsedBecomesAMapOfPartOf);
        registerItem(0x18b, name, item535);
    }
    {
        std::wstring name(L"golden_carrot");
        auto* item537 = new FoodItem(6, 1.2f, 0);
        std::wstring icon(L"carrotGolden");
        auto* configured538 = item537->setIconName(icon);
        auto* configured539 = configured538->setBaseItemTypeAndMaterial(0x26, 0x2f);
        configured539->setDescriptionId(StringIDs::GoldenCarrot, StringIDs::Restores3IconShank01CraftedFromA);
        registerItem(0x18c, name, item537);
    }
    {
        std::wstring name(L"skull");
        auto* item540 = new SkullItem();
        std::wstring icon(L"");
        auto* configured541 = item540->setIconName(icon);
        configured541->setDescriptionId(StringIDs::Skull, StringIDs::MobHeadsCanBePlacedAsADecoration);
        registerItem(0x18d, name, item540);
    }
    {
        std::wstring name(L"carrot_on_a_stick");
        auto* item542 = new CarrotOnAStickItem();
        std::wstring icon(L"carrotOnAStick");
        auto* configured543 = item542->setIconName(icon);
        auto* configured544 = configured543->setBaseItemTypeAndMaterial(0x25, 0x2f);
        configured544->setDescriptionId(StringIDs::CarrotOnAStick,
                                        StringIDs::UsedToControlASaddledPigWhenRidingOnIt);
        registerItem(0x18e, name, item542);
    }
    {
        std::wstring name(L"nether_star");
        auto* item545 = new SimpleFoiledItem();
        std::wstring icon(L"nether_star");
        auto* configured546 = item545->setIconName(icon);
        configured546->setDescriptionId(StringIDs::NetherStar,
                                        StringIDs::DroppedByWitherUsedInCraftingBeacons);
        registerItem(399, name, item545);
    }
    {
        std::wstring name(L"pumpkin_pie");
        auto* item547 = new FoodItem(8, 0.3f, 0);
        std::wstring icon(L"pumpkinPie");
        auto* configured548 = item547->setIconName(icon);
        configured548->setDescriptionId(StringIDs::PumpkinPie, StringIDs::Restores4IconShank01);
        registerItem(400, name, item547);
    }
    {
        std::wstring name(L"fireworks");
        auto* item549 = new FireworksItem();
        std::wstring icon(L"fireworks");
        auto* configured550 = item549->setIconName(icon);
        auto* configured551 = configured550->setBaseItemTypeAndMaterial(0x2c, 0);
        configured551->setDescriptionId(StringIDs::FireworkRocket, 0xa644378);
        registerItem(0x191, name, item549);
    }
    {
        std::wstring name(L"firework_charge");
        auto* item552 = new FireworkChargeItem();
        std::wstring icon(L"fireworks_charge");
        auto* configured553 = item552->setIconName(icon);
        auto* configured554 = configured553->setBaseItemTypeAndMaterial(0x2c, 0);
        configured554->setDescriptionId(StringIDs::FireworkStar,
                                        StringIDs::UsedToDetermineColorEffectAndShapeOf);
        registerItem(0x192, name, item552);
    }
    {
        std::wstring name(L"enchanted_book");
        auto* item555 = new EnchantedBookItem();
        std::wstring icon(L"enchantedBook");
        auto* configured556 = item555->setIconName(icon);
        auto* configured557 = configured556->setMaxStackSize(1);
        configured557->setDescriptionId(StringIDs::EnchantedBook,
                                        StringIDs::UsedWithAnAnvilToEnchantWeaponsTools);
        registerItem(0x193, name, item555);
    }
    {
        std::wstring name(L"comparator");
        auto* item558 = new BlockPlanterItem(Blocks::UNPOWERED_COMPARATOR);
        std::wstring icon(L"comparator");
        auto* configured559 = item558->setIconName(icon);
        auto* configured560 = configured559->setDescriptionId(
            StringIDs::RedstoneComparator, StringIDs::UsedInRedstoneCircuitsToMaintainCompareOr);
        configured560->setBaseItemTypeAndMaterial(0x3b, 0);
        registerItem(0x194, name, item558);
    }
    {
        std::wstring name(L"netherbrick");
        auto* item561 = new Item();
        std::wstring icon(L"netherbrick");
        auto* configured562 = item561->setIconName(icon);
        configured562->setDescriptionId(StringIDs::NetherBrick,
                                        StringIDs::CreatedBySmeltingNetherrackInAFurnaceCan);
        registerItem(0x195, name, item561);
    }
    {
        std::wstring name(L"quartz");
        auto* item563 = new Item();
        std::wstring icon(L"netherquartz");
        auto* configured564 = item563->setIconName(icon);
        configured564->setDescriptionId(StringIDs::NetherQuartz,
                                        StringIDs::CreatedByMiningNetherQuartzOreCanBe);
        registerItem(0x196, name, item563);
    }
    {
        std::wstring name(L"tnt_minecart");
        auto* item565 = new MinecartItem(MinecartType::TNT);
        std::wstring icon(L"minecart_tnt");
        auto* configured566 = item565->setIconName(icon);
        configured566->setDescriptionId(StringIDs::MinecartWithTnt, StringIDs::ATypeOfMinecartThatActsAsA);
        registerItem(0x197, name, item565);
    }
    {
        std::wstring name(L"hopper_minecart");
        auto* item567 = new MinecartItem(MinecartType::HOPPER);
        std::wstring icon(L"minecart_hopper");
        auto* configured568 = item567->setIconName(icon);
        auto* configured569 = configured568->setDescriptionId(
            StringIDs::MinecartWithHopper, StringIDs::ASpecialTypeOfMinecartThatFunctionsSimilarly);
        configured569->setBaseItemTypeAndMaterial(0x33, 2);
        registerItem(0x198, name, item567);
    }
    {
        std::wstring name(L"prismarine_shard");
        auto* item570 = new Item();
        std::wstring icon(L"prismarine_shard");
        auto* configured571 = item570->setIconName(icon);
        auto* configured572 = configured571->setDescriptionId(
            StringIDs::PrismarineShard, StringIDs::DroppedByGuardiansAndElderGuardiansCanBe);
        configured572->setBaseItemTypeAndMaterial(0xd, 0);
        registerItem(0x199, name, item570);
    }
    {
        std::wstring name(L"prismarine_crystals");
        auto* item573 = new Item();
        std::wstring icon(L"prismarine_crystals");
        auto* configured574 = item573->setIconName(icon);
        auto* configured575 = configured574->setDescriptionId(
            StringIDs::PrismarineCrystals, StringIDs::ObtainedFromSeaLanternsOrByDefeatingGuardians);
        configured575->setBaseItemTypeAndMaterial(0xd, 0);
        registerItem(0x19a, name, item573);
    }
    {
        std::wstring name(L"rabbit");
        auto* item576 = new FoodItem(3, 0.3f, 1);
        std::wstring icon(L"rabbit_raw");
        auto* configured577 = item576->setIconName(icon);
        auto* configured578
            = configured577->setDescriptionId(StringIDs::RawRabbit, StringIDs::Restores15IconShank01OrCan_2);
        configured578->setBaseItemTypeAndMaterial(0x35, 0);
        registerItem(0x19b, name, item576);
    }
    {
        std::wstring name(L"cooked_rabbit");
        auto* item579 = new FoodItem(5, 0.6f, 1);
        std::wstring icon(L"rabbit_cooked");
        auto* configured580 = item579->setIconName(icon);
        configured580->setDescriptionId(StringIDs::CookedRabbit, StringIDs::Restores25IconShank01UsedTo);
        registerItem(0x19c, name, item579);
    }
    {
        std::wstring name(L"rabbit_stew");
        auto* item581 = new BowlFoodItem(10);
        item581->setBaseItemTypeAndMaterial(0x27, 0);
        std::wstring icon(L"rabbit_stew");
        auto* configured582 = item581->setIconName(icon);
        configured582->setDescriptionId(StringIDs::RabbitStew, StringIDs::Restores5IconShank01CookedUpWith);
        registerItem(0x19d, name, item581);
    }
    {
        std::wstring name(L"rabbit_foot");
        auto* item583 = new Item();
        std::wstring icon(L"rabbit_foot");
        auto* configured584 = item583->setIconName(icon);
        configured584->setDescriptionId(StringIDs::RabbitSFoot, 0x9ea74d9);
        registerItem(0x19e, name, item583);
    }
    {
        std::wstring name(L"rabbit_hide");
        auto* item585 = new Item();
        std::wstring icon(L"rabbit_hide");
        auto* configured586 = item585->setIconName(icon);
        configured586->setDescriptionId(StringIDs::RabbitHide, StringIDs::UsedInCraftingLeather);
        registerItem(0x19f, name, item585);
    }
    {
        std::wstring name(L"armor_stand");
        auto* item587 = new ArmorStandItem();
        auto* configured588 = item587->setBaseItemTypeAndMaterial(0x22, 1);
        configured588->setDescriptionId(StringIDs::ArmorStand_1,
                                        StringIDs::CanBeEquippedToDisplayArmorAndOther);
        std::wstring icon(L"wooden_armorstand");
        auto* configured589 = item587->setIconName(icon);
        configured589->setMaxStackSize(0x10);
        registerItem(0x1a0, name, item587);
    }
    {
        std::wstring name(L"iron_horse_armor");
        auto* item590 = new HorseArmorItem(2, 5, 0x69, L"meo");
        std::wstring icon(L"iron_horse_armor");
        auto* configured591 = item590->setIconName(icon);
        auto* configured592 = configured591->setMaxStackSize(1);
        configured592->setDescriptionId(StringIDs::IronHorseArmor, StringIDs::ASpecialTypeOfArmorThatCanBe2);
        registerItem(0x1a1, name, item590);
    }
    {
        std::wstring name(L"golden_horse_armor");
        auto* item593 = new HorseArmorItem(3, 7, 0x68, L"goo");
        std::wstring icon(L"gold_horse_armor");
        auto* configured594 = item593->setIconName(icon);
        auto* configured595 = configured594->setMaxStackSize(1);
        configured595->setDescriptionId(StringIDs::GoldHorseArmor, StringIDs::ASpecialTypeOfArmorThatCanBe3);
        registerItem(0x1a2, name, item593);
    }
    {
        std::wstring name(L"diamond_horse_armor");
        auto* item596 = new HorseArmorItem(4, 0xb, 0x67, L"dio");
        std::wstring icon(L"diamond_horse_armor");
        auto* configured597 = item596->setIconName(icon);
        auto* configured598 = configured597->setMaxStackSize(1);
        configured598->setDescriptionId(StringIDs::DiamondHorseArmor,
                                        StringIDs::ASpecialTypeOfArmorThatCanBe);
        registerItem(0x1a3, name, item596);
    }
    {
        std::wstring name(L"lead");
        auto* item599 = new LeadItem();
        std::wstring icon(L"lead");
        auto* configured600 = item599->setIconName(icon);
        auto* configured601 = configured600->setBaseItemTypeAndMaterial(0x19, 0);
        configured601->setDescriptionId(0x4f7491a, StringIDs::UsedToLeashMobsToPlayerOrFencePosts);
        registerItem(0x1a4, name, item599);
    }
    {
        std::wstring name(L"name_tag");
        auto* item602 = new NameTagItem();
        std::wstring icon(L"name_tag");
        auto* configured603 = item602->setIconName(icon);
        configured603->setDescriptionId(StringIDs::NameTag, StringIDs::UsedToNameMobsInWorld);
        registerItem(0x1a5, name, item602);
    }
    {
        std::wstring name(L"command_block_minecart");
        auto* item604 = new MinecartItem(MinecartType::COMMAND_BLOCK);
        std::wstring icon(L"minecart_command_block");
        auto* configured605 = item604->setIconName(icon);
        configured605->setDescriptionId(StringIDs::MinecartWithCommandBlock);
        registerItem(0x1a6, name, item604);
    }
    {
        std::wstring name(L"mutton");
        auto* item606 = new FoodItem(2, 0.3f, 1);
        std::wstring icon(L"mutton_raw");
        auto* configured607 = item606->setIconName(icon);
        configured607->setDescriptionId(StringIDs::RawMutton, StringIDs::Restores1IconShank01OrCanBe_3);
        registerItem(0x1a7, name, item606);
    }
    {
        std::wstring name(L"cooked_mutton");
        auto* item608 = new FoodItem(6, 0.8f, 1);
        std::wstring icon(L"mutton_cooked");
        auto* configured609 = item608->setIconName(icon);
        configured609->setDescriptionId(StringIDs::CookedMutton,
                                        StringIDs::Restores3IconShank01CreatedByCookingMutton);
        registerItem(0x1a8, name, item608);
    }
    {
        std::wstring name(L"banner");
        auto* item610 = new BannerItem();
        std::wstring icon(L"cookie");
        auto* configured611 = item610->setIconName(icon);
        auto* configured612 = configured611->setBaseItemTypeAndMaterial(0x36, 0);
        configured612->setDescriptionId(StringIDs::Banner);
        registerItem(0x1a9, name, item610);
    }
    {
        std::wstring name(L"end_crystal");
        auto* item613 = new EndCrystalItem();
        item613->setDescriptionId(StringIDs::EndCrystal, StringIDs::HealsEnderDragonAndCanBeUsedTo);
        registerItem(0x1aa, name, item613);
    }
    {
        std::wstring name(L"spruce_door");
        auto* item614 = new DoorItem(Blocks::SPRUCE_DOOR);
        std::wstring icon(L"door_spruce");
        auto* configured615 = item614->setIconName(icon);
        auto* configured616 = configured615->setBaseItemTypeAndMaterial(6, 0x27);
        configured616->setDescriptionId(StringIDs::SpruceDoor,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
        registerItem(0x1ab, name, item614);
    }
    {
        std::wstring name(L"birch_door");
        auto* item617 = new DoorItem(Blocks::BIRCH_DOOR);
        std::wstring icon(L"door_birch");
        auto* configured618 = item617->setIconName(icon);
        auto* configured619 = configured618->setBaseItemTypeAndMaterial(6, 0x28);
        configured619->setDescriptionId(StringIDs::BirchDoor,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
        registerItem(0x1ac, name, item617);
    }
    {
        std::wstring name(L"jungle_door");
        auto* item620 = new DoorItem(Blocks::JUNGLE_DOOR);
        std::wstring icon(L"door_jungle");
        auto* configured621 = item620->setIconName(icon);
        auto* configured622 = configured621->setBaseItemTypeAndMaterial(6, 0x29);
        configured622->setDescriptionId(StringIDs::JungleDoor,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
        registerItem(0x1ad, name, item620);
    }
    {
        std::wstring name(L"acacia_door");
        auto* item623 = new DoorItem(Blocks::ACACIA_DOOR);
        std::wstring icon(L"door_acacia");
        auto* configured624 = item623->setIconName(icon);
        auto* configured625 = configured624->setBaseItemTypeAndMaterial(6, 0x2a);
        configured625->setDescriptionId(StringIDs::AcaciaDoor,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
        registerItem(0x1ae, name, item623);
    }
    {
        std::wstring name(L"dark_oak_door");
        auto* item626 = new DoorItem(Blocks::DARK_OAK_DOOR);
        std::wstring icon(L"door_dark_oak");
        auto* configured627 = item626->setIconName(icon);
        auto* configured628 = configured627->setBaseItemTypeAndMaterial(6, 0x2b);
        configured628->setDescriptionId(StringIDs::DarkOakDoor,
                                        StringIDs::WoodenDoorsAreActivatedByUsingHittingmOr);
        registerItem(0x1af, name, item626);
    }
    {
        std::wstring name(L"chorus_fruit");
        auto* item629 = new ChorusFruitItem(4, 0.3f);
        auto* food630 = item629->setAlwaysEat();
        std::wstring icon(L"chorus_fruit");
        auto* configured631 = food630->setIconName(icon);
        configured631->setDescriptionId(StringIDs::ChorusFruit, StringIDs::EatingRestores2IconShank01AndMay);
        registerItem(0x1b0, name, food630);
    }
    {
        std::wstring name(L"chorus_fruit_popped");
        auto* item632 = new Item();
        std::wstring icon(L"chorus_fruit_popped");
        auto* configured633 = item632->setIconName(icon);
        configured633->setDescriptionId(StringIDs::PoppedChorusFruit,
                                        StringIDs::CreatedByCookingChorusFruitInAFurnace);
        registerItem(0x1b1, name, item632);
    }
    {
        std::wstring name(L"beetroot");
        auto* item634 = new FoodItem(1, 0.6f, 0);
        std::wstring icon(L"beetroot");
        auto* configured635 = item634->setIconName(icon);
        configured635->setDescriptionId(StringIDs::Beetroot, StringIDs::Restores05IconShank01WhenEaten);
        registerItem(0x1b2, name, item634);
    }
    {
        std::wstring name(L"beetroot_seeds");
        auto* item636 = new SeedItem(Blocks::BEETROOTS, Blocks::FARMLAND);
        std::wstring icon(L"beetroot_seeds");
        auto* configured637 = item636->setIconName(icon);
        auto* configured638 = configured637->setBaseItemTypeAndMaterial(0x21, 0);
        configured638->setDescriptionId(StringIDs::BeetrootSeeds,
                                        StringIDs::CanBePlantedInFarmlandToGrowBeetroot);
        registerItem(0x1b3, name, item636);
    }
    {
        std::wstring name(L"beetroot_soup");
        auto* item639 = new BowlFoodItem(6);
        std::wstring icon(L"beetroot_soup");
        auto* configured640 = item639->setIconName(icon);
        auto* configured641 = configured640->setBaseItemTypeAndMaterial(0x27, 0);
        configured641->setDescriptionId(StringIDs::BeetrootSoup, StringIDs::Restores3IconShank01WhenEaten);
        registerItem(0x1b4, name, item639);
    }
    {
        std::wstring name(L"dragon_breath");
        auto* item642 = new Item();
        std::wstring icon(L"dragon_breath");
        auto* configured643 = item642->setIconName(icon);
        auto* configured644 = configured643->setCraftingRemainingItem(item480);
        configured644->setDescriptionId(StringIDs::DragonSBreath,
                                        StringIDs::UsedInPotionBrewingObtainedByCapturingEnder);
        registerItem(0x1b5, name, item642);
    }
    {
        std::wstring name(L"splash_potion");
        auto* item645 = static_cast<SplashPotionItem*>(::operator new(sizeof(SplashPotionItem)));
        std::memset(static_cast<void*>(item645), 0, sizeof(SplashPotionItem));
        new (item645) SplashPotionItem();
        std::wstring icon(L"splash_potion");
        auto* configured646 = item645->setIconName(icon);
        configured646->setDescriptionId(StringIDs::SplashPotion, StringIDs::APotionThatCanBeThrown);
        registerItem(0x1b6, name, item645);
    }
    {
        std::wstring name(L"spectral_arrow");
        auto* item647 = new SpectralArrowItem();
        std::wstring icon(L"spectral_arrow");
        auto* configured648 = item647->setIconName(icon);
        configured648->setBaseItemTypeAndMaterial(0x18, 0x12);
        item647->setDescriptionId(0x558958e, StringIDs::GivesVictimAGlowingOutlineThatCanBe);
        registerItem(0x1b7, name, item647);
    }
    {
        std::wstring name(L"tipped_arrow");
        auto* item649 = static_cast<TippedArrowItem*>(::operator new(sizeof(TippedArrowItem)));
        std::memset(static_cast<void*>(item649), 0, sizeof(TippedArrowItem));
        new (item649) TippedArrowItem();
        std::wstring icon(L"tipped_arrow_base");
        auto* configured650 = item649->setIconName(icon);
        auto* configured651 = configured650->setBaseItemTypeAndMaterial(0x18, 0x12);
        configured651->setDescriptionId(StringIDs::TippedArrow,
                                        StringIDs::AnArrowThatAppliesAPotionEffectBased);
        registerItem(0x1b8, name, item649);
    }
    {
        std::wstring name(L"lingering_potion");
        auto* item652 = static_cast<LingeringPotionItem*>(::operator new(sizeof(LingeringPotionItem)));
        std::memset(static_cast<void*>(item652), 0, sizeof(LingeringPotionItem));
        new (item652) LingeringPotionItem();
        std::wstring icon(L"lingering_potion");
        auto* configured653 = item652->setIconName(icon);
        configured653->setDescriptionId(StringIDs::LingeringPotion,
                                        StringIDs::APotionThatCanBeThrownAndApplies);
        registerItem(0x1b9, name, item652);
    }
    {
        std::wstring name(L"elytra");
        auto* item654 = new ElytraItem();
        std::wstring icon(L"elytra");
        auto* configured655 = item654->setIconName(icon);
        configured655->setDescriptionId(StringIDs::Elytra_1, StringIDs::AllowsPlayerToGlideWhenWorn);
        registerItem(0x1bb, name, item654);
    }
    {
        std::wstring name(L"spruce_boat");
        auto* item656 = new BoatItem(1);
        std::wstring icon(L"spruce_boat");
        auto* configured657 = item656->setIconName(icon);
        configured657->setBaseItemTypeAndMaterial(0x37, 0x40);
        item656->setDescriptionId(StringIDs::SpruceBoat, StringIDs::UsedToTravelInWaterMoreQuicklyThan_5);
        registerItem(0x1bc, name, item656);
    }
    {
        std::wstring name(L"birch_boat");
        auto* item658 = new BoatItem(2);
        std::wstring icon(L"birch_boat");
        auto* configured659 = item658->setIconName(icon);
        auto* configured660 = configured659->setBaseItemTypeAndMaterial(0x37, 0x41);
        configured660->setDescriptionId(StringIDs::BirchBoat,
                                        StringIDs::UsedToTravelInWaterMoreQuicklyThan_2);
        registerItem(0x1bd, name, item658);
    }
    {
        std::wstring name(L"jungle_boat");
        auto* item661 = new BoatItem(3);
        std::wstring icon(L"jungle_boat");
        auto* configured662 = item661->setIconName(icon);
        auto* configured663 = configured662->setBaseItemTypeAndMaterial(0x37, 0x42);
        configured663->setDescriptionId(StringIDs::JungleBoat,
                                        StringIDs::UsedToTravelInWaterMoreQuicklyThan_4);
        registerItem(0x1be, name, item661);
    }
    {
        std::wstring name(L"acacia_boat");
        auto* item664 = new BoatItem(4);
        std::wstring icon(L"acacia_boat");
        auto* configured665 = item664->setIconName(icon);
        auto* configured666 = configured665->setBaseItemTypeAndMaterial(0x37, 0x43);
        configured666->setDescriptionId(StringIDs::AcaciaBoat,
                                        StringIDs::UsedToTravelInWaterMoreQuicklyThan_1);
        registerItem(0x1bf, name, item664);
    }
    {
        std::wstring name(L"dark_oak_boat");
        auto* item667 = new BoatItem(5);
        std::wstring icon(L"dark_oak_boat");
        auto* configured668 = item667->setIconName(icon);
        auto* configured669 = configured668->setBaseItemTypeAndMaterial(0x37, 0x44);
        configured669->setDescriptionId(StringIDs::DarkOakBoat,
                                        StringIDs::UsedToTravelInWaterMoreQuicklyThan_3);
        registerItem(0x1c0, name, item667);
    }
    {
        std::wstring name(L"totem_of_undying");
        auto* item670 = new Item();
        std::wstring icon(L"totem");
        auto* configured671 = item670->setIconName(icon);
        auto* configured672 = configured671->setDescriptionId(StringIDs::TotemOfUndying, 0x3b5e68a);
        configured672->setMaxStackSize(1);
        registerItem(0x1c1, name, item670);
    }
    {
        std::wstring name(L"shulker_shell");
        auto* item673 = new Item();
        std::wstring icon(L"shulker_shell");
        auto* configured674 = item673->setIconName(icon);
        configured674->setDescriptionId(StringIDs::ShulkerShell,
                                        StringIDs::SometimesDroppedByShulkersCanBeUsedTo);
        registerItem(0x1c2, name, item673);
    }
    {
        std::wstring name(L"iron_nugget");
        auto* item675 = new Item();
        std::wstring icon(L"iron_nugget");
        auto* configured676 = item675->setIconName(icon);
        auto* configured677 = configured676->setBaseItemTypeAndMaterial(0x1f, 3);
        configured677->setDescriptionId(StringIDs::IronNugget,
                                        StringIDs::CreatedBySmeltingIronArmourAndToolsIn);
        registerItem(0x1c4, name, item675);
    }
    {
        std::wstring name(L"leather_horse_armor");
        auto* item678 = new HorseArmorItem(1, 3, ItemBootstrap::LEATHER_ARMOR_TEXTURES, 2, L"lee");
        auto* configured679 = item678->setIconName(sBaseTierName);
        auto* configured680 = configured679->setMaxStackSize(1);
        auto* configured681 = configured680->setBaseItemTypeAndMaterial(0x3c, 6);
        configured681->setDescriptionId(StringIDs::LeatherHorseArmor,
                                        StringIDs::ASpecialTypeOfArmorThatCanBeDyedAnd1);
        registerItem(0x1c5, name, item678);
    }
    {
        std::wstring name(L"debug_fourj_item");
        auto* item682 = static_cast<DebugFourjItem*>(::operator new(sizeof(DebugFourjItem)));
        std::memset(static_cast<void*>(item682), 0, sizeof(DebugFourjItem));
        new (item682) DebugFourjItem();
        std::wstring icon(L"barrier");
        item682->setIconName(icon);
        registerItem(0x8cf, name, item682);
    }
    {
        std::wstring name(L"record_13");
        std::wstring icon(L"13");
        auto* item683 = new RecordItem(icon, StringIDs::C41813, SoundEvents::RECORD_13);
        item683->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d0, name, item683);
    }
    {
        std::wstring name(L"record_cat");
        std::wstring icon(L"cat");
        auto* item684 = new RecordItem(icon, StringIDs::C418Cat, SoundEvents::CAT);
        item684->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d1, name, item684);
    }
    {
        std::wstring name(L"record_blocks");
        std::wstring icon(L"blocks");
        auto* item685 = new RecordItem(icon, StringIDs::C418Blocks, SoundEvents::BLOCKS);
        item685->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d2, name, item685);
    }
    {
        std::wstring name(L"record_chirp");
        std::wstring icon(L"chirp");
        auto* item686 = new RecordItem(icon, StringIDs::C418Chirp, SoundEvents::CHIRP);
        item686->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d3, name, item686);
    }
    {
        std::wstring name(L"record_far");
        std::wstring icon(L"far");
        auto* item687 = new RecordItem(icon, 0x88245c3, SoundEvents::FAR);
        item687->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d4, name, item687);
    }
    {
        std::wstring name(L"record_mall");
        std::wstring icon(L"mall");
        auto* item688 = new RecordItem(icon, StringIDs::C418Mall, SoundEvents::MALL);
        item688->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d5, name, item688);
    }
    {
        std::wstring name(L"record_mellohi");
        std::wstring icon(L"mellohi");
        auto* item689 = new RecordItem(icon, StringIDs::C418Mellohi, SoundEvents::MELLOHI);
        item689->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d6, name, item689);
    }
    {
        std::wstring name(L"record_stal");
        std::wstring icon(L"stal");
        auto* item690 = new RecordItem(icon, StringIDs::C418Stal, SoundEvents::STAL);
        item690->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d7, name, item690);
    }
    {
        std::wstring name(L"record_strad");
        std::wstring icon(L"strad");
        auto* item691 = new RecordItem(icon, StringIDs::C418Strad, SoundEvents::STRAD);
        item691->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d8, name, item691);
    }
    {
        std::wstring name(L"record_ward");
        std::wstring icon(L"ward");
        auto* item692 = new RecordItem(icon, StringIDs::C418Ward, SoundEvents::WARD);
        item692->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8d9, name, item692);
    }
    {
        std::wstring name(L"record_11");
        std::wstring icon(L"11");
        auto* item693 = new RecordItem(icon, StringIDs::C41811, SoundEvents::RECORD_11);
        item693->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8da, name, item693);
    }
    {
        std::wstring name(L"record_wait");
        std::wstring icon(L"where are we now");
        auto* item694 = new RecordItem(icon, StringIDs::C418Wait, SoundEvents::WHERE_ARE_WE_NOW);
        item694->setDescriptionId(StringIDs::MusicDisc, StringIDs::CollectedByGettingASkeletonToKillA);
        registerItem(0x8db, name, item694);
    }
    Items::staticCtor();
}

Item* Item::setBaseItemTypeAndMaterial(int type, int material) {
    m_baseItemType = type;
    m_material = material;
    return this;
}

// name guessed
Item* Item::setDescriptionId(int name) {
    m_descriptionId = name;
    return this;
}

// name guessed
Item* Item::setUseDescriptionId(int description) {
    m_useDescriptionId = description;
    return this;
}

Item* Item::setDescriptionId(int name, int description) {
    return setDescriptionId(name)->setUseDescriptionId(description);
}

// name guessed
Item* Item::setCraftingRemainingItem(Item* item) {
    m_craftingRemainingItem = item;
    return this;
}

// name guessed
Item* Item::setMaxStackSize(int size) {
    m_maxStackSize = size;
    return this;
}

// name guessed
Item* Item::setHandEquipped() {
    m_handEquipped = true;
    return this;
}

// name guessed
Item* Item::setFlag78(bool value) {
    m_byte78 = value;
    return this;
}

void Item::registerItem(int id, const std::wstring& name, Item* item) {
    ResourceLocation key(name);
    registerItem(id, key, item);
}

void Item::setStackedByData(bool stackedByData) {
    m_stackedByData = stackedByData;
}
