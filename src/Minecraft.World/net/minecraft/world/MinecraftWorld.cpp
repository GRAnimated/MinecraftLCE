#include "net/minecraft/world/MinecraftWorld.h"

#include "net/minecraft/SharedConstants.h"
#include "net/minecraft/client/renderer/FaceInfo.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/server/ServerLevel.h"
#include "net/minecraft/sounds/SoundEvents.h"
#include "net/minecraft/stats/Stats.h"
#include "net/minecraft/util/datafix/fixes/BlockEntityIdFix.h"
#include "net/minecraft/util/datafix/fixes/ItemIdFix.h"
#include "net/minecraft/util/datafix/fixes/ItemPotionFix.h"
#include "net/minecraft/util/datafix/walker/ItemInstanceBlockEntityTagWalker.h"
#include "net/minecraft/world/DefaultVertexFormat.h"
#include "net/minecraft/world/DispenserBootstrap.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/effect/MobEffect.h"
#include "net/minecraft/world/effect/MobEffects.h"
#include "net/minecraft/world/entity/EntityIO.h"
#include "net/minecraft/world/entity/MobCategory.h"
#include "net/minecraft/world/entity/ai/goal/EatBlockGoal.h"
#include "net/minecraft/world/entity/item/EnderCrystal.h"
#include "net/minecraft/world/entity/item/FallingBlockEntity.h"
#include "net/minecraft/world/entity/item/FireworksRocketEntity.h"
#include "net/minecraft/world/entity/item/ItemEntity.h"
#include "net/minecraft/world/entity/mob/AgableMob.h"
#include "net/minecraft/world/entity/mob/Animal.h"
#include "net/minecraft/world/entity/mob/AreaEffectCloud.h"
#include "net/minecraft/world/entity/mob/ArmorStand.h"
#include "net/minecraft/world/entity/mob/Bat.h"
#include "net/minecraft/world/entity/mob/Blaze.h"
#include "net/minecraft/world/entity/mob/Boat.h"
#include "net/minecraft/world/entity/mob/Chicken.h"
#include "net/minecraft/world/entity/mob/Creeper.h"
#include "net/minecraft/world/entity/mob/EnderDragon.h"
#include "net/minecraft/world/entity/mob/EnderMan.h"
#include "net/minecraft/world/entity/mob/FishingHook.h"
#include "net/minecraft/world/entity/mob/Ghast.h"
#include "net/minecraft/world/entity/mob/Guardian.h"
#include "net/minecraft/world/entity/mob/Horse.h"
#include "net/minecraft/world/entity/mob/ItemFrame.h"
#include "net/minecraft/world/entity/mob/Llama.h"
#include "net/minecraft/world/entity/mob/Minecart.h"
#include "net/minecraft/world/entity/mob/MinecartCommandBlock.h"
#include "net/minecraft/world/entity/mob/MinecartFurnace.h"
#include "net/minecraft/world/entity/mob/Mob.h"
#include "net/minecraft/world/entity/mob/Ocelot.h"
#include "net/minecraft/world/entity/mob/Parrot.h"
#include "net/minecraft/world/entity/mob/Pig.h"
#include "net/minecraft/world/entity/mob/PolarBear.h"
#include "net/minecraft/world/entity/mob/PrimedTnt.h"
#include "net/minecraft/world/entity/mob/Rabbit.h"
#include "net/minecraft/world/entity/mob/Sheep.h"
#include "net/minecraft/world/entity/mob/Shulker.h"
#include "net/minecraft/world/entity/mob/Slime.h"
#include "net/minecraft/world/entity/mob/SnowMan.h"
#include "net/minecraft/world/entity/mob/SpellcasterIllager.h"
#include "net/minecraft/world/entity/mob/Spider.h"
#include "net/minecraft/world/entity/mob/TamableAnimal.h"
#include "net/minecraft/world/entity/mob/ThrownPotion.h"
#include "net/minecraft/world/entity/mob/Vex.h"
#include "net/minecraft/world/entity/mob/Villager.h"
#include "net/minecraft/world/entity/mob/VillagerGolem.h"
#include "net/minecraft/world/entity/mob/Witch.h"
#include "net/minecraft/world/entity/mob/WitherBoss.h"
#include "net/minecraft/world/entity/mob/WitherSkull.h"
#include "net/minecraft/world/entity/mob/Wolf.h"
#include "net/minecraft/world/entity/mob/Zombie.h"
#include "net/minecraft/world/entity/mob/ZombieVillager.h"
#include "net/minecraft/world/entity/mob/abstract/AbstractChestedHorse.h"
#include "net/minecraft/world/entity/mob/abstract/AbstractHorse.h"
#include "net/minecraft/world/entity/mob/abstract/AbstractIllager.h"
#include "net/minecraft/world/entity/mob/abstract/AbstractSkeleton.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/entity/projectile/TippableArrow.h"
#include "net/minecraft/world/inventory/InventoryMenu.h"
#include "net/minecraft/world/item/ArmorItem.h"
#include "net/minecraft/world/item/AxeItem.h"
#include "net/minecraft/world/item/DyeColor.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/PickaxeItem.h"
#include "net/minecraft/world/item/ShovelItem.h"
#include "net/minecraft/world/item/alchemy/Potion.h"
#include "net/minecraft/world/item/alchemy/PotionBrewing.h"
#include "net/minecraft/world/item/alchemy/Potions.h"
#include "net/minecraft/world/item/crafting/Recipes.h"
#include "net/minecraft/world/item/crafting/recipe/FurnaceRecipes.h"
#include "net/minecraft/world/item/crafting/recipe/MapExtendingRecipe.h"
#include "net/minecraft/world/item/enchantment/Enchantments.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/biome/JungleBiome.h"
#include "net/minecraft/world/level/biome/MesaBiome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/SoundType.h"
#include "net/minecraft/world/level/block/entity/BannerPattern.h"
#include "net/minecraft/world/level/block/entity/BeaconBlockEntity.h"
#include "net/minecraft/world/level/block/entity/BlockEntity.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/chunk/storage/McRegionChunkStorage.h"
#include "net/minecraft/world/level/gamemode/GameType.h"
#include "net/minecraft/world/level/levelgen/feature/BirchFeature.h"
#include "net/minecraft/world/level/levelgen/feature/DesertWellFeature.h"
#include "net/minecraft/world/level/levelgen/feature/MegaPineTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/OceanMonumentFeature.h"
#include "net/minecraft/world/level/levelgen/feature/PineFeature.h"
#include "net/minecraft/world/level/levelgen/feature/RandomScatteredLargeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/RoofTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SavannaTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SpruceFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SwampTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/TreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/VillageFeature.h"
#include "net/minecraft/world/level/levelgen/feature/VillagePieces.h"
#include "net/minecraft/world/level/levelgen/feature/WoodlandMansionFeature.h"
#include "net/minecraft/world/level/levelgen/structure/OceanMonumentPieces.h"
#include "net/minecraft/world/level/levelgen/structure/ScatteredFeaturePieces.h"
#include "net/minecraft/world/level/levelgen/structure/StrongholdPieces.h"
#include "net/minecraft/world/level/levelgen/structure/StructureFeatureIO.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include "net/minecraft/world/level/storage/loot/BuiltInLootTables.h"
#include "net/minecraft/world/stats/CommonStats.h"

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
    SynchedEntityData::defineId(eMob,
                                ePathfinderMob);  // I wonder if these just register categories or whatever
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
    SynchedEntityData::defineId(eAnimal, eTamableAnimal);
    Parrot::staticCtor();
    Sheep::staticCtor();
    Pig::staticCtor();
    Chicken::staticCtor();
    Rabbit::staticCtor();
    PolarBear::staticCtor();
    SynchedEntityData::defineId(ePathfinderMob, eGolem);
    SnowMan::staticCtor();
    VillagerGolem::staticCtor();
    Shulker::staticCtor();
    SynchedEntityData::defineId(ePathfinderMob, eMonster);
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
