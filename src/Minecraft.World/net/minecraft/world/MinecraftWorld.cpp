#include "../../../../Minecraft.Client/net/minecraft/client/renderer/FaceInfo.h"
#include "MinecraftWorld.h"
#include "entity/item/EnderCrystal.h"
#include "entity/item/FallingBlockEntity.h"
#include "entity/item/FireworksRocketEntity.h"
#include "entity/item/ItemEntity.h"
#include "entity/mob/AgableMob.h"
#include "entity/mob/Animal.h"
#include "entity/mob/AreaEffectCloud.h"
#include "entity/mob/ArmorStand.h"
#include "entity/mob/Bat.h"
#include "entity/mob/Blaze.h"
#include "entity/mob/Boat.h"
#include "entity/mob/Chicken.h"
#include "entity/mob/Creeper.h"
#include "entity/mob/EnderDragon.h"
#include "entity/mob/EnderMan.h"
#include "entity/mob/FishingHook.h"
#include "entity/mob/Ghast.h"
#include "entity/mob/Guardian.h"
#include "entity/mob/Horse.h"
#include "entity/mob/ItemFrame.h"
#include "entity/mob/Llama.h"
#include "entity/mob/Minecart.h"
#include "entity/mob/MinecartCommandBlock.h"
#include "entity/mob/MinecartFurnace.h"
#include "entity/mob/Mob.h"
#include "entity/mob/Ocelot.h"
#include "entity/mob/Parrot.h"
#include "entity/mob/Pig.h"
#include "entity/mob/PolarBear.h"
#include "entity/mob/PrimedTnt.h"
#include "entity/mob/Rabbit.h"
#include "entity/mob/Sheep.h"
#include "entity/mob/Shulker.h"
#include "entity/mob/Slime.h"
#include "entity/mob/SnowMan.h"
#include "entity/mob/SpellcasterIllager.h"
#include "entity/mob/Spider.h"
#include "entity/mob/TamableAnimal.h"
#include "entity/mob/ThrownPotion.h"
#include "entity/mob/Vex.h"
#include "entity/mob/Villager.h"
#include "entity/mob/VillagerGolem.h"
#include "entity/mob/Witch.h"
#include "entity/mob/WitherBoss.h"
#include "entity/mob/WitherSkull.h"
#include "entity/mob/Wolf.h"
#include "entity/mob/Zombie.h"
#include "entity/mob/ZombieVillager.h"
#include "entity/mob/abstract/AbstractChestedHorse.h"
#include "entity/mob/abstract/AbstractHorse.h"
#include "entity/mob/abstract/AbstractIllager.h"
#include "entity/mob/abstract/AbstractSkeleton.h"
#include "entity/projectile/TippableArrow.h"
#include "inventory/InventoryMenu.h"
#include "item/ArmorItem.h"
#include "item/AxeItem.h"
#include "item/PickaxeItem.h"
#include "item/ShovelItem.h"
#include "level/biome/JungleBiome.h"
#include "level/biome/MesaBiome.h"
#include "level/block/entity/BeaconBlockEntity.h"
#include "level/block/entity/BlockEntity.h"
#include "level/chunk/storage/McRegionChunkStorage.h"
#include "level/levelgen/feature/BirchFeature.h"
#include "level/levelgen/feature/MegaPineTreeFeature.h"
#include "level/levelgen/feature/OceanMonumentFeature.h"
#include "level/levelgen/feature/PineFeature.h"
#include "level/levelgen/feature/RandomScatteredLargeFeature.h"
#include "level/levelgen/feature/RoofTreeFeature.h"
#include "level/levelgen/feature/SavannaTreeFeature.h"
#include "level/levelgen/feature/SpruceFeature.h"
#include "level/levelgen/feature/TreeFeature.h"
#include "level/levelgen/feature/VillageFeature.h"
#include "level/levelgen/feature/WoodlandMansionFeature.h"
#include "net/minecraft/SharedConstants.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/server/ServerLevel.h"
#include "net/minecraft/sounds/SoundEvents.h"
#include "net/minecraft/stats/Stats.h"
#include "net/minecraft/util/datafix/BlockEntityIdFix.h"
#include "net/minecraft/util/datafix/ItemIdFix.h"
#include "net/minecraft/util/datafix/ItemPotionFix.h"
#include "net/minecraft/util/datafix/walker/ItemInstanceBlockEntityTagWalker.h"
#include "net/minecraft/world/BannerPattern.h"
#include "net/minecraft/world/DefaultVertexFormat.h"
#include "net/minecraft/world/DispenserBootstrap.h"
#include "net/minecraft/world/Potion.h"
#include "net/minecraft/world/PotionBrewing.h"
#include "net/minecraft/world/Potions.h"
#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/effect/MobEffects.h"
#include "net/minecraft/world/entity/EntityIO.h"
#include "net/minecraft/world/entity/MobCategory.h"
#include "net/minecraft/world/entity/ai/goal/EatBlockGoal.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/item/DyeColor.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/crafting/Recipes.h"
#include "net/minecraft/world/item/crafting/recipe/FurnaceRecipes.h"
#include "net/minecraft/world/item/crafting/recipe/MapExtendingRecipe.h"
#include "net/minecraft/world/item/enchantment/Enchantments.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/SoundType.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/gamemode/GameType.h"
#include "net/minecraft/world/level/levelgen/feature/DesertWellFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SwampTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/pieces/OceanMonumentPieces.h"
#include "net/minecraft/world/level/levelgen/feature/pieces/ScatteredFeaturePieces.h"
#include "net/minecraft/world/level/levelgen/feature/pieces/StrongholdPieces.h"
#include "net/minecraft/world/level/levelgen/feature/pieces/VillagePieces.h"
#include "net/minecraft/world/level/levelgen/structure/StructureFeatureIO.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include "net/minecraft/world/level/storage/loot/BuiltInLootTables.h"
#include "stats/CommonStats.h"

void MinecraftWorld_RunStaticCtors() {
    Direction::staticCtor();
    Packet::staticCtor();
    SoundEvents::staticCtor();
    SoundType::staticCtor();
    MaterialColor::staticCtor();
    DyeColor::staticCtor();
    MaterialColor::staticCtorAfterDyeColor();
    Material::staticCtor();
    Block::staticCtor();
    Blocks::staticInit();
    AxeItem::staticCtor();
    PickaxeItem::staticCtor();
    ShovelItem::staticCtor();
    JungleBiome::staticCtor();
    MesaBiome::staticCtor();
    Biome::staticCtor();
    MobEffect::staticCtor();
    MobEffects::staticCtor();
    EquipmentSlot::staticCtor();
    InventoryMenu::staticCtor();
    ArmorItem::staticCtor();
    Item::staticCtor();
    FurnaceRecipes::staticCtor();
    MapExtendingRecipe::StaticCtor();
    BannerPattern::staticCtor();
    Potion::StaticCtor();
    Potions::StaticCtor();
    Recipes::staticCtor();

    CommonStats::setInstance(new CommonStats());

    Stats::staticCtor();
    BlockEntity::staticCtor();
    EntityIO::bootStrap();
    MobCategory::staticCtor();
    BlockEntityIdFix::staticCtor();
    ItemPotionFix::staticCtor();
    Item::staticInit();
    LevelChunk::staticCtor();
    LevelType::staticCtor();
    StructureFeatureIO::staticCtor();
    VillagePieces::Smithy::staticCtor();
    VillageFeature::staticCtor();
    OceanMonumentFeature::staticCtor();
    RandomScatteredLargeFeature::staticCtor();
    OceanMonumentPieces::OceanMonumentPiece::staticCtor();
    DesertWellFeature::staticCtor();
    ScatteredFeaturePieces::JunglePyramidPiece::staticCtor();
    SwampTreeFeature::staticCtor();
    StrongholdPieces::staticCtor();
    WoodlandMansionFeature::staticCtor();
    Entity::staticCtor();
    LivingEntity::staticCtor();
    ArmorStand::staticCtor();
    Mob::staticCtor();
    SynchedEntityData::defineId(eMob, eUnknownMob); // I wonder if these just register categories or whatever
    AgableMob::staticCtor();
    Animal::staticCtor();
    Villager::staticCtor();
    TamableAnimal::staticCtor();
    Ocelot::staticCtor();
    Wolf::staticCtor();
    SynchedEntityData::defineId(eAnimal, eAbstractHorse);
    AbstractHorse::staticCtor();
    SynchedEntityData::defineId(eAbstractHorse, eAbstractChestedHorse);
    AbstractChestedHorse::staticCtor();
    Horse::staticCtor();
    Llama::staticCtor();
    SynchedEntityData::defineId(eAnimal, eUnknownAnimal);
    Parrot::staticCtor();
    Sheep::staticCtor();
    Pig::staticCtor();
    Chicken::staticCtor();
    Rabbit::staticCtor();
    PolarBear::staticCtor();
    SynchedEntityData::defineId(eUnknownMob, eGolem);
    SnowMan::staticCtor();
    VillagerGolem::staticCtor();
    Shulker::staticCtor();
    SynchedEntityData::defineId(eUnknownMob, eMonster);
    Spider::staticCtor();
    Zombie::staticCtor();
    ZombieVillager::staticCtor();
    Creeper::staticCtor();
    AbstractSkeleton::staticCtor();
    EnderMan::staticCtor();
    Blaze::staticCtor();
    Witch::staticCtor();
    WitherBoss::staticCtor();
    Guardian::staticCtor();
    Vex::staticCtor();
    SynchedEntityData::defineId(eMonster, eAbstractIllager);
    AbstractIllager::staticCtor();
    SynchedEntityData::defineId(eAbstractIllager, eSpellcasterIllager);
    SpellcasterIllager::staticCtor();
    SynchedEntityData::defineId(eMob, eAmbientCreature);
    Bat::staticCtor();
    SynchedEntityData::defineId(eMob, eUnknownMob3);
    Ghast::staticCtor();
    Slime::staticCtor();
    EnderDragon::staticCtor();
    Player::staticCtor();
    Minecart::staticCtor();
    MinecartCommandBlock::staticCtor();
    MinecartFurnace::staticCtor();
    Arrow::staticCtor();
    TippableArrow::staticCtor();
    SynchedEntityData::defineId(eSerializer, eFireball);
    WitherSkull::staticCtor();
    SynchedEntityData::defineId(eSerializer, eThrowableProjectile);
    ThrownPotion::staticCtor();
    SynchedEntityData::defineId(eSerializer, eHangingEntity);
    ItemFrame::staticCtor();
    PrimedTnt::staticCtor();
    FireworksRocketEntity::staticCtor();
    EnderCrystal::staticCtor();
    FishingHook::staticCtor();
    FallingBlockEntity::staticCtor();
    ItemEntity::staticCtor();
    Boat::staticCtor();
    AreaEffectCloud::staticCtor();
    PotionBrewing::StaticCtor();
    Enchantment::staticCtor();
    SharedConstants::staticCtor();
    ServerLevel::staticCtor();
    SparseLightStorage::staticCtor();
    CompressedBlockStorage::staticCtor();
    SparseDataStorage::staticCtor();
    McRegionChunkStorage::staticCtor();
    GameType::staticCtor();
    BeaconBlockEntity::staticCtor();
    DefaultVertexFormat::staticCtor();
    FaceInfo::staticCtor();
    EatBlockGoal::staticCtor();
    BirchFeature::staticCtor();
    MegaPineTreeFeature::staticCtor();
    PineFeature::staticCtor();
    RoofTreeFeature::staticCtor();
    SavannaTreeFeature::staticCtor();
    SpruceFeature::staticCtor();
    SwampTreeFeature::staticCtor();
    TreeFeature::staticCtor();
    BuiltInLootTables::staticCtor();
    Enchantments::staticCtor();
    DispenserBootstrap::StaticCtor();
    ItemIdFix::staticCtor();
    ItemInstanceBlockEntityTagWalker::staticCtor();
}
