#include "net/minecraft/world/entity/EntityIO.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/entity/EntityIOFactories.h"
#include "net/minecraft/world/entity/mob/MinecartType.h"

std::unordered_map<ResourceLocation, EntityIO::SpawnEggInfo*> EntityIO::SPAWN_EGGS;
ResourceLocation EntityIO::DEFAULT_TYPE(L"LightningBolt");
std::unordered_set<ResourceLocation> EntityIO::KNOWN_TYPES;

void EntityIO::bootStrap() {
    registerEntity(EntityIOFactories::createItem, 1, L"item", static_cast<eINSTANCEOF>(0x0800000a), L"Item");
    registerEntity(EntityIOFactories::createXpOrb, 2, L"xp_orb", static_cast<eINSTANCEOF>(0x08000003),
                   L"XPOrb");
    registerEntity(EntityIOFactories::createAreaEffectCloud, 3, L"area_effect_cloud",
                   static_cast<eINSTANCEOF>(0x0800000f), L"AreaEffectCloud");
    registerEntity(EntityIOFactories::createElderGuardian, 4, L"elder_guardian",
                   static_cast<eINSTANCEOF>(0x5d544001), L"ElderGuardian");
    registerEntity(EntityIOFactories::createWitherSkeleton, 5, L"wither_skeleton",
                   static_cast<eINSTANCEOF>(0x5d540402), L"WitherSkeleton");
    registerEntity(EntityIOFactories::createStray, 6, L"stray", static_cast<eINSTANCEOF>(0x5d540403),
                   L"Stray");
    registerEntity(EntityIOFactories::createEgg, 7, L"egg", static_cast<eINSTANCEOF>(0x8a200002),
                   L"ThrownEgg");
    registerEntity(EntityIOFactories::createLeashKnot, 8, L"leash_knot", static_cast<eINSTANCEOF>(0x0a080003),
                   L"LeashKnot");
    registerEntity(EntityIOFactories::createPainting, 9, L"painting", static_cast<eINSTANCEOF>(0x0a080001),
                   L"Painting");
    registerEntity(EntityIOFactories::createArrow, 10, L"arrow", static_cast<eINSTANCEOF>(0x8a020002),
                   L"Arrow");
    registerEntity(EntityIOFactories::createSnowball, 11, L"snowball", static_cast<eINSTANCEOF>(0x8a200001),
                   L"Snowball");
    registerEntity(EntityIOFactories::createFireball, 12, L"fireball", static_cast<eINSTANCEOF>(0x8a400003),
                   L"Fireball");
    registerEntity(EntityIOFactories::createSmallFireball, 13, L"small_fireball",
                   static_cast<eINSTANCEOF>(0x8a400004), L"SmallFireball");
    registerEntity(EntityIOFactories::createEnderPearl, 14, L"ender_pearl",
                   static_cast<eINSTANCEOF>(0x8a200003), L"ThrownEnderpearl");
    registerEntity(EntityIOFactories::createEyeOfEnderSignal, 15, L"eye_of_ender_signal",
                   static_cast<eINSTANCEOF>(0x88000004), L"EyeOfEnderSignal");
    registerEntity(EntityIOFactories::createPotion, 16, L"potion", static_cast<eINSTANCEOF>(0x8a200004),
                   L"ThrownPotion");
    registerEntity(EntityIOFactories::createXpBottle, 17, L"xp_bottle", static_cast<eINSTANCEOF>(0x8a200005),
                   L"ThrownExpBottle");
    registerEntity(EntityIOFactories::createItemFrame, 18, L"item_frame",
                   static_cast<eINSTANCEOF>(0x0a080002), L"ItemFrame");
    registerEntity(EntityIOFactories::createWitherSkull, 19, L"wither_skull",
                   static_cast<eINSTANCEOF>(0x8a400002), L"WitherSkull");
    registerEntity(EntityIOFactories::createTnt, 20, L"tnt", static_cast<eINSTANCEOF>(0x0800000b),
                   L"PrimedTnt");
    registerEntity(EntityIOFactories::createFallingBlock, 21, L"falling_block",
                   static_cast<eINSTANCEOF>(0x08000009), L"FallingSand");
    registerEntity(EntityIOFactories::createFireworksRocket, 22, L"fireworks_rocket",
                   static_cast<eINSTANCEOF>(0x88000005), L"FireworksRocketEntity");
    registerEntity(EntityIOFactories::createHusk, 23, L"husk", static_cast<eINSTANCEOF>(0x5d550003), L"Husk");
    registerEntity(EntityIOFactories::createSpectralArrow, 24, L"spectral_arrow",
                   static_cast<eINSTANCEOF>(0x8a020001), L"SpectralArrow");
    registerEntity(EntityIOFactories::createShulkerBullet, 25, L"shulker_bullet",
                   static_cast<eINSTANCEOF>(0x08000010), L"ShulkerBullet");
    registerEntity(EntityIOFactories::createDragonFireball, 26, L"dragon_fireball",
                   static_cast<eINSTANCEOF>(0x8a400001), L"DragonFireball");
    registerEntity(EntityIOFactories::createZombieVillager, 27, L"zombie_villager",
                   static_cast<eINSTANCEOF>(0x5d550002), L"ZombieVillager");
    registerEntity(EntityIOFactories::createSkeletonHorse, 28, L"skeleton_horse",
                   static_cast<eINSTANCEOF>(0x2d690002), L"SkeletonHorse");
    registerEntity(EntityIOFactories::createZombieHorse, 29, L"zombie_horse",
                   static_cast<eINSTANCEOF>(0x2d690003), L"ZombieHorse");
    registerEntity(EntityIOFactories::createArmorStand, 30, L"armor_stand",
                   static_cast<eINSTANCEOF>(0x0c000001), L"ArmorStand");
    registerEntity(EntityIOFactories::createDonkey, 31, L"donkey", static_cast<eINSTANCEOF>(0x2d698001),
                   L"Donkey");
    registerEntity(EntityIOFactories::createMule, 32, L"mule", static_cast<eINSTANCEOF>(0x2d698002), L"Mule");
    registerEntity(EntityIOFactories::createEvocationFangs, 33, L"evocation_fangs",
                   static_cast<eINSTANCEOF>(0x08000011), L"EvocationFangs");
    registerEntity(EntityIOFactories::createEvocationIllager, 34, L"evocation_illager",
                   static_cast<eINSTANCEOF>(0x5d541801), L"EvocationIllager");
    registerEntity(EntityIOFactories::createVex, 35, L"vex", static_cast<eINSTANCEOF>(0x5d540008), L"Vex");
    registerEntity(EntityIOFactories::createVindicationIllager, 36, L"vindication_illager",
                   static_cast<eINSTANCEOF>(0x5d541001), L"VindicationIllager");
    registerEntity(EntityIOFactories::createIllusionIllager, 37, L"illusion_illager",
                   static_cast<eINSTANCEOF>(0x5d541802), L"IllusionIllager");
    registerEntity(EntityIOFactories::createBoat, 41, L"boat", static_cast<eINSTANCEOF>(0x08000008), L"Boat");
    registerEntity(EntityIOFactories::createMinecart, 42, L"minecart", static_cast<eINSTANCEOF>(0x0a800001),
                   MinecartType::RIDEABLE->getName());
    registerEntity(EntityIOFactories::createChestMinecart, 43, L"chest_minecart",
                   static_cast<eINSTANCEOF>(0x0a840002), MinecartType::CHEST->getName());
    registerEntity(EntityIOFactories::createFurnaceMinecart, 44, L"furnace_minecart",
                   static_cast<eINSTANCEOF>(0x0a800003), MinecartType::FURNACE->getName());
    registerEntity(EntityIOFactories::createTntMinecart, 45, L"tnt_minecart",
                   static_cast<eINSTANCEOF>(0x0a800004), MinecartType::TNT->getName());
    registerEntity(EntityIOFactories::createHopperMinecart, 46, L"hopper_minecart",
                   static_cast<eINSTANCEOF>(0x0a840005), MinecartType::HOPPER->getName());
    registerEntity(EntityIOFactories::createSpawnerMinecart, 47, L"spawner_minecart",
                   static_cast<eINSTANCEOF>(0x0a800006), MinecartType::SPAWNER->getName());
    registerEntity(EntityIOFactories::createCreeper, 50, L"creeper", static_cast<eINSTANCEOF>(0x5d540001),
                   L"Creeper");
    registerEntity(EntityIOFactories::createSkeleton, 51, L"skeleton", static_cast<eINSTANCEOF>(0x5d540401),
                   L"Skeleton");
    registerEntity(EntityIOFactories::createSpider, 52, L"spider", static_cast<eINSTANCEOF>(0x5d560000),
                   L"Spider");
    registerEntity(EntityIOFactories::createGiant, 53, L"giant", static_cast<eINSTANCEOF>(0x5d540002),
                   L"Giant");
    registerEntity(EntityIOFactories::createZombie, 54, L"zombie", static_cast<eINSTANCEOF>(0x5d550000),
                   L"Zombie");
    registerEntity(EntityIOFactories::createSlime, 55, L"slime", static_cast<eINSTANCEOF>(0x5d108000),
                   L"Slime");
    registerEntity(EntityIOFactories::createGhast, 56, L"ghast", static_cast<eINSTANCEOF>(0x5d001001),
                   L"Ghast");
    registerEntity(EntityIOFactories::createZombiePigman, 57, L"zombie_pigman",
                   static_cast<eINSTANCEOF>(0x5d550001), L"PigZombie");
    registerEntity(EntityIOFactories::createEnderman, 58, L"enderman", static_cast<eINSTANCEOF>(0x5d540003),
                   L"Enderman");
    registerEntity(EntityIOFactories::createCaveSpider, 59, L"cave_spider",
                   static_cast<eINSTANCEOF>(0x5d560001), L"CaveSpider");
    registerEntity(EntityIOFactories::createSilverfish, 60, L"silverfish",
                   static_cast<eINSTANCEOF>(0x5d540004), L"Silverfish");
    registerEntity(EntityIOFactories::createBlaze, 61, L"blaze", static_cast<eINSTANCEOF>(0x5d540005),
                   L"Blaze");
    registerEntity(EntityIOFactories::createMagmaCube, 62, L"magma_cube",
                   static_cast<eINSTANCEOF>(0x5d108001), L"LavaSlime");
    registerEntity(EntityIOFactories::createEnderDragon, 63, L"ender_dragon",
                   static_cast<eINSTANCEOF>(0x0d000005), L"EnderDragon");
    registerEntity(EntityIOFactories::createWither, 64, L"wither", static_cast<eINSTANCEOF>(0x5d540007),
                   L"WitherBoss");
    registerEntity(EntityIOFactories::createBat, 65, L"bat", static_cast<eINSTANCEOF>(0x1d004001), L"Bat");
    registerEntity(EntityIOFactories::createWitch, 66, L"witch", static_cast<eINSTANCEOF>(0x5d540006),
                   L"Witch");
    registerEntity(EntityIOFactories::createEndermite, 67, L"endermite", static_cast<eINSTANCEOF>(0x4d54000b),
                   L"Endermite");
    registerEntity(EntityIOFactories::createGuardian, 68, L"guardian", static_cast<eINSTANCEOF>(0x5d544000),
                   L"Guardian");
    registerEntity(EntityIOFactories::createShulker, 69, L"shulker", static_cast<eINSTANCEOF>(0x4d580003),
                   L"Shulker");
    registerEntity(EntityIOFactories::createPig, 90, L"pig", static_cast<eINSTANCEOF>(0x2d680003), L"Pig");
    registerEntity(EntityIOFactories::createSheep, 91, L"sheep", static_cast<eINSTANCEOF>(0x2d680002),
                   L"Sheep");
    registerEntity(EntityIOFactories::createCow, 92, L"cow", static_cast<eINSTANCEOF>(0x2d6a0000), L"Cow");
    registerEntity(EntityIOFactories::createChicken, 93, L"chicken", static_cast<eINSTANCEOF>(0x0d680004),
                   L"Chicken");
    registerEntity(EntityIOFactories::createSquid, 94, L"squid", static_cast<eINSTANCEOF>(0x0d102001),
                   L"Squid");
    registerEntity(EntityIOFactories::createWolf, 95, L"wolf", static_cast<eINSTANCEOF>(0x0d6c0002), L"Wolf");
    registerEntity(EntityIOFactories::createMooshroom, 96, L"mooshroom", static_cast<eINSTANCEOF>(0x2d6a0001),
                   L"MushroomCow");
    registerEntity(EntityIOFactories::createSnowman, 97, L"snowman", static_cast<eINSTANCEOF>(0x2d580001),
                   L"SnowMan");
    registerEntity(EntityIOFactories::createOcelot, 98, L"ocelot", static_cast<eINSTANCEOF>(0x2d6c0001),
                   L"Ozelot");
    registerEntity(EntityIOFactories::createVillagerGolem, 99, L"villager_golem",
                   static_cast<eINSTANCEOF>(0x0d580002), L"VillagerGolem");
    registerEntity(EntityIOFactories::createHorse, 100, L"horse", static_cast<eINSTANCEOF>(0x2d690001),
                   L"Horse");
    registerEntity(EntityIOFactories::createRabbit, 101, L"rabbit", static_cast<eINSTANCEOF>(0x2d680005),
                   L"Rabbit");
    registerEntity(EntityIOFactories::createPolarBear, 102, L"polar_bear",
                   static_cast<eINSTANCEOF>(0x2d680006), L"PolarBear");
    registerEntity(EntityIOFactories::createLlama, 103, L"llama", static_cast<eINSTANCEOF>(0x2d698003),
                   L"Llama");
    registerEntity(EntityIOFactories::createLlamaSpit, 104, L"llama_spit",
                   static_cast<eINSTANCEOF>(0x88000012), L"LlamaSpit");
    registerEntity(EntityIOFactories::createParrot, 105, L"parrot", static_cast<eINSTANCEOF>(0x2d6c0003),
                   L"Parrot");
    registerEntity(EntityIOFactories::createVillager, 120, L"villager", static_cast<eINSTANCEOF>(0x0d600001),
                   L"Villager");
    registerEntity(EntityIOFactories::createEnderCrystal, 200, L"ender_crystal",
                   static_cast<eINSTANCEOF>(0x0800000e), L"EnderCrystal");

    registerEgg(StringIDs::Bat, L"bat", 323, 324);
    registerEgg(StringIDs::Blaze, L"blaze", 301, 302);
    registerEgg(StringIDs::CaveSpider, L"cave_spider", 297, 298);
    registerEgg(StringIDs::Chicken, L"chicken", 311, 312);
    registerEgg(StringIDs::Cow, L"cow", 309, 310);
    registerEgg(StringIDs::Creeper, L"creeper", 281, 282);
    registerEgg(StringIDs::Donkey, L"donkey", 345, 346);
    registerEgg(StringIDs::ElderGuardian, L"elder_guardian", 339, 340);
    registerEgg(StringIDs::Enderman, L"enderman", 295, 296);
    registerEgg(StringIDs::Endermite, L"endermite", 329, 330);
    registerEgg(StringIDs::Evoker, L"evocation_illager", 341, 342);
    registerEgg(StringIDs::Ghast, L"ghast", 291, 292);
    registerEgg(StringIDs::Guardian, L"guardian", 331, 332);
    registerEgg(StringIDs::Horse_1, L"horse", 327, 328);
    registerEgg(StringIDs::Husk, L"husk", 355, 356);
    registerEgg(StringIDs::Llama, L"llama", 343, 344);
    registerEgg(StringIDs::MagmaCube, L"magma_cube", 303, 304);
    registerEgg(StringIDs::Mooshroom, L"mooshroom", 317, 318);
    registerEgg(StringIDs::Mule, L"mule", 351, 352);
    registerEgg(StringIDs::Ocelot, L"ocelot", 319, 320);
    registerEgg(StringIDs::Parrot, L"parrot", 363, 364);
    registerEgg(StringIDs::Pig, L"pig", 305, 306);
    registerEgg(StringIDs::PolarBear, L"polar_bear", 335, 336);
    registerEgg(StringIDs::Rabbit, L"rabbit", 333, 334);
    registerEgg(StringIDs::Sheep, L"sheep", 307, 308);
    registerEgg(StringIDs::Shulker, L"shulker", 337, 338);
    registerEgg(StringIDs::Silverfish, L"silverfish", 299, 300);
    registerEgg(StringIDs::Skeleton, L"skeleton", 283, 284);
    registerEgg(StringIDs::SkeletonHorse, L"skeleton_horse", 347, 348);
    registerEgg(StringIDs::Slime, L"slime", 289, 290);
    registerEgg(StringIDs::Spider, L"spider", 285, 286);
    registerEgg(StringIDs::Squid, L"squid", 313, 314);
    registerEgg(StringIDs::Stray, L"stray", 353, 354);
    registerEgg(StringIDs::Vex, L"vex", 357, 358);
    registerEgg(StringIDs::Villager, L"villager", 321, 322);
    registerEgg(StringIDs::Vindicator, L"vindication_illager", 359, 360);
    registerEgg(StringIDs::Witch_1, L"witch", 325, 326);
    registerEgg(StringIDs::WitherSkeleton, L"wither_skeleton", 365, 366);
    registerEgg(StringIDs::Wolf, L"wolf", 315, 316);
    registerEgg(StringIDs::Zombie, L"zombie", 287, 288);
    registerEgg(StringIDs::ZombieHorse, L"zombie_horse", 349, 350);
    registerEgg(StringIDs::ZombiePigman, L"zombie_pigman", 293, 294);
    registerEgg(StringIDs::ZombieVillager, L"zombie_villager", 361, 362);
    KNOWN_TYPES.insert(DEFAULT_TYPE);
}
