#pragma once

#include "net/minecraft/client/ui/StringIDs.h"

void RegisterAwardsWithProfileManager();

struct AwardInfo {
    long mIdx; // 64 bit sized on NX but only 32 bit sized on wiiu
    const wchar_t* mId;
    int mIdx2;
    unsigned int mName; // TODO: are these meant to be unsigned? It throws errors if not.
    unsigned int mDesc;
};

enum eAwardType {
    _0 = 0
};

// I have doubts that this should be in UIScene_AchievementsMenu
// maybe cAchievements?
// or it's some NMW shit since afaik it was in ghs UnityWorld static thing
struct Awards {
    static constexpr int sAchievementSlots[] // also used to register the textures
    = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6,  0x7,  0x8,  0x9,
        0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13,
        0x16, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
        0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34,
        0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
        0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
        0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52,
        0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A };

    static constexpr AwardInfo sAwards[] = {
        {0x00,  L"MCTrophy_00", 1, StringIDs::TakingInventory, StringIDs::OpenYourInventory},
        {0x01,  L"MCTrophy_01", 2, StringIDs::GettingWood, StringIDs::PunchATreeUntilABlockOfWoodPopsOut},
        {0x02,  L"MCTrophy_02", 3, StringIDs::Benchmarking, StringIDs::CraftAWorkbenchWithFourBlocksOfWooden},
        {0x03,  L"MCTrophy_10", 4, StringIDs::TimeToMine, StringIDs::UsePlanksAndSticksToMakeAPickaxe},
        {0x04,  L"MCTrophy_12", 5, StringIDs::HotTopic, StringIDs::ConstructAFurnaceOutOfEightCobblestoneBlocks},
        {0x05,  L"MCTrophy_14", 6, StringIDs::AcquireHardware, StringIDs::SmeltAnIronIngot},
        {0x06,  L"MCTrophy_03", 7, StringIDs::TimeToFarm, StringIDs::MakeAHoe},
        {0x07,  L"MCTrophy_04", 8, StringIDs::BakeBread, StringIDs::TurnWheatIntoBread},
        {0x08,  L"MCTrophy_05", 9, StringIDs::TheLie, StringIDs::BakeACakeUsingWheatSugarMilkAndEggs},
        {0x09,  L"MCTrophy_11", 0xA, StringIDs::GettingAnUpgrade, StringIDs::ConstructABetterPickaxe},
        {0xA,  L"MCTrophy_13", 0xB, StringIDs::DeliciousFish, StringIDs::CatchAndCookFish},
        {0xB,  L"MCTrophy_15", 0xC, StringIDs::OnARail, StringIDs::TravelByMinecartToAPointAtLeast},
        {0xC,  L"MCTrophy_06", 0xD, StringIDs::TimeToStrike, StringIDs::UsePlanksAndSticksToMakeASword},
        {0xD,  L"MCTrophy_07", 0xE, StringIDs::MonsterHunter, StringIDs::AttackAndDestroyAMonster},
        {0xE,  L"MCTrophy_08", 0xF, StringIDs::CowTipper, StringIDs::HarvestSomeLeather},
        {0xF,  L"MCTrophy_09", 0x10, StringIDs::WhenPigsFly, StringIDs::UseASaddleToRideAPigAndn},
        {0x10,  L"MCTrophy_16", 0x11, StringIDs::LeaderOfPack, StringIDs::BefriendFiveWolves},
        {0x11,  L"MCTrophy_17", 0x12, StringIDs::MoarTools, StringIDs::ConstructOneTypeOfEachTool},
        {0x12,  L"MCTrophy_18", 0x13, StringIDs::DispenseWithThis, StringIDs::ConstructADispenser},
        {0x13,  L"MCTrophy_19", 0x14, StringIDs::IntoTheNether, StringIDs::ConstructANetherPortal},
        {0x14,  L"", 0, 0, 0},
        {0x15,  L"", 0, 0, 0},
        {0x16,  L"MCTrophy_33", 0x22, StringIDs::PorkChop, StringIDs::CookAndEatAPorkChop},
        {0x17,  L"MCTrophy_34", 0x23, StringIDs::PassingTime, StringIDs::PlayFor100Days},
        {0x18,  L"MCTrophy_35", 0x24, StringIDs::Archer, StringIDs::KillACreeperWithArrows},
        {0x19,  L"", 0, 0, 0},
        {0x1A,  L"MCTrophy_20", 0x15, StringIDs::SniperDuel, StringIDs::KillASkeletonWithAnArrowFromMore},
        {0x1B,  L"MCTrophy_21", 0x16, StringIDs::Diamonds, StringIDs::AcquireDiamondsWithYourIronTools},
        {0x1C,  L"", 0, 0, 0},
        {0x1D,  L"MCTrophy_22", 0x17, StringIDs::ReturnToSender, StringIDs::DestroyAGhastWithAFireball},
        {0x1E,  L"MCTrophy_23", 0x18, StringIDs::IntoFire, StringIDs::RelieveABlazeOfItsRod},
        {0x1F,  L"MCTrophy_24", 0x19, StringIDs::LocalBrewery, StringIDs::BrewAPotion},
        {0x20,  L"MCTrophy_25", 0x1A, StringIDs::TheEnd, StringIDs::EnterAnEndPortal},
        {0x21,  L"MCTrophy_26", 0x1B, StringIDs::TheEnd_1, StringIDs::KillEnderdragon},
        {0x22,  L"MCTrophy_27", 0x1C, StringIDs::Enchanter, StringIDs::ConstructAnEnchantmentTable},
        {0x23,  L"MCTrophy_28", 0x1D, StringIDs::Overkill, StringIDs::DealNineHeartsOfDamageInASingleHit},
        {0x24,  L"MCTrophy_29", 0x1E, StringIDs::Librarian, StringIDs::BuildSomeBookshelvesToImproveYourEnchantmentTable},
        {0x25,  L"MCTrophy_30", 0x1F, StringIDs::AdventuringTime, StringIDs::Discover17Of40DifferentBiomes},
        {0x26,  L"MCTrophy_31", 0x20, StringIDs::Repopulation, StringIDs::BreedTwoCowsWithWheat},
        {0x27,  L"MCTrophy_32", 0x21, StringIDs::DiamondsToYou, StringIDs::ThrowDiamondsAtAnotherPlayer},
        {0x28,  L"MCTrophy_36", 0x25, StringIDs::TheHaggler, StringIDs::MineOrPurchase30Emeralds},
        {0x29,  L"MCTrophy_37", 0x26, StringIDs::PotPlanter, StringIDs::CraftAndPlaceAFlowerPot},
        {0x2A,  L"MCTrophy_38", 0x27, StringIDs::ItSASign, StringIDs::CraftAndPlaceASign},
        {0x2B,  L"MCTrophy_39", 0x28, StringIDs::IronBelly, StringIDs::StopStarvationUsingRottenFlesh},
        {0x2C,  L"MCTrophy_40", 0x29, StringIDs::HaveAShearfulDay, StringIDs::UseShearsToObtainWoolFromASheep},
        {0x2D,  L"MCTrophy_41", 0x2A, StringIDs::RainbowCollection, StringIDs::GatherAll16ColorsOfWool},
        {0x2E,  L"MCTrophy_42", 0x2B, StringIDs::StayinFrosty, StringIDs::SwimInLavaWhileHavingFireResistanceEffect},
        {0x2F,  L"MCTrophy_43", 0x2C, StringIDs::ChestfulOfCobblestone, StringIDs::Mine1728CobblestoneAndPlaceItInAChest},
        {0x30,  L"MCTrophy_44", 0x2D, StringIDs::RenewableEnergy, StringIDs::SmeltWoodTrunksUsingCharcoalToMakeMore},
        {0x31,  L"MCTrophy_45", 0x2E, StringIDs::MusicToMyEars, StringIDs::PlayAMusicDiscInAJukebox},
        {0x32,  L"MCTrophy_46", 0x2F, StringIDs::BodyGuard, StringIDs::CreateAnIronGolem},
        {0x33,  L"MCTrophy_47", 0x30, StringIDs::IronMan, StringIDs::WearAFullSuitOfIronArmor},
        {0x34,  L"MCTrophy_48", 0x31, StringIDs::ZombieDoctor, StringIDs::CureAZombieVillager},
        {0x35,  L"MCTrophy_49", 0x32, StringIDs::LionTamer, StringIDs::TameAnOcelot},
        {0x36,  L"MCTrophy_50", 0x33, StringIDs::TheBeginning, StringIDs::SpawnWither},
        {0x37,  L"MCTrophy_51", 0x34, StringIDs::TheBeginning_1, StringIDs::KillWither},
        {0x38,  L"MCTrophy_52", 0x35, StringIDs::Beaconator, StringIDs::CreateAndFullyPowerABeacon},
        {0x39,  L"MCTrophy_53", 0x36, StringIDs::Overpowered, StringIDs::EatANotchApple},
        {0x3A,  L"MCTrophy_54", 0x37, StringIDs::TieDyeOutfit, StringIDs::DyeAll4UniquePiecesOfLeatherArmor},
        {0x3B,  L"MCTrophy_55", 0x3B, StringIDs::Trampoline, StringIDs::Bounce30BlocksUpwardOffASlimeBlock},
        {0x3C,  L"MCTrophy_56", 0x3C, StringIDs::TheStudent, StringIDs::WinAPublicBattleMiniGame},
        {0x3D,  L"MCTrophy_57", 0x3D, StringIDs::HasBecomeMaster, StringIDs::Win3PublicBattleMiniGamesInARow},
        {0x3E,  L"MCTrophy_58", 0x3E, StringIDs::TisButAScratch, StringIDs::Take100DamageInARoundOfA},
        {0x3F,  L"MCTrophy_59", 0x3F, StringIDs::Cupid, StringIDs::Kill2PlayersInARoundOfPublic},
        {0x40,  L"MCTrophy_60", 0x40, StringIDs::HungerPain, StringIDs::KillAPlayerWhileYouAreStarvingIn},
        {0x41,  L"MCTrophy_61", 0x41, StringIDs::Mine, StringIDs::OpenEveryChestInABattleMiniGame},
        {0x42,  L"MCTrophy_62", 0x42, StringIDs::TheEndAgain, StringIDs::RespawnEnderdragon},
        {0x43,  L"MCTrophy_63", 0x43, StringIDs::YouNeedAMint, StringIDs::CollectDragonSBreathInAGlassBottle},
        {0x44,  L"MCTrophy_64", 0x44, StringIDs::SuperSonic, StringIDs::UseAnElytraToFlyThroughA1},
        {0x45,  L"MCTrophy_65", 0x45, StringIDs::DrySpell, StringIDs::DryASpongeInAFurnace},
        {0x46,  L"MCTrophy_66", 0x46, StringIDs::FreeDiver, StringIDs::StayUnderwaterFor2Minutes},
        {0x47,  L"MCTrophy_67", 0x47, StringIDs::SuperFuel, StringIDs::PowerAFurnaceWithLava},
        {0x48,  L"MCTrophy_68", 0x48, StringIDs::SaddleUp, StringIDs::TameAHorse},
        {0x49,  L"MCTrophy_69", 0x49, StringIDs::TasteOfYourOwnMedicine, StringIDs::PoisonAWitchWithASplashPotion},
        {0x4A,  L"MCTrophy_70", 0x4A, StringIDs::BeamMeUp, StringIDs::TeleportOver100MetersFromASingleThrow},
        {0x4B,  L"MCTrophy_71", 0x4B, StringIDs::MapRoom_1, StringIDs::PlaceAFullyExploredMapIntoAnItemFrame_1},
        {0x4C,  L"MCTrophy_72", 0x4C, StringIDs::Camouflage_1, StringIDs::KillAMobWhileWearingSameTypeOfMobHead_1},
        {0x4D,  L"MCTrophy_73", 0x4D, StringIDs::BackFromDead, StringIDs::Win3RoundsInARowAfterOne},
        {0x4E,  L"MCTrophy_74", 0x4E, StringIDs::SNoThrow, StringIDs::WinASingleRoundOfSnowballTumbleWithout},
        {0x4F,  L"MCTrophy_75", 0x4F, StringIDs::SnowStorm, StringIDs::HitASinglePlayerWith25SnowballsIn},
        {0x50,  L"MCTrophy_76", 0x50, StringIDs::Hotshot, StringIDs::HitAPlayerWithASnowballWhileFalling},
        {0x51,  L"MCTrophy_77", 0x51, StringIDs::Snowplough, StringIDs::PushThreePlayersIntoLavaUsingSnowballs},
        {0x52,  L"MCTrophy_78", 0x52, StringIDs::Overlord, StringIDs::StayOnTopLayerWhileWinningARound},
        {0x53,  L"MCTrophy_79", 0x53, StringIDs::Underdog, StringIDs::WinATumbleGameWhilstOnLowestLayer},
        {0x54, L"MCTrophy_80", 0x54, StringIDs::TheDeepEnd, StringIDs::DefeatAnElderGuardian},
        {0x55, L"MCTrophy_81", 0x55, StringIDs::GreatViewFromUpHere, StringIDs::LevitateUp50BlocksFromAttacksOfAShulker},
        {0x56, L"MCTrophy_82", 0x56, StringIDs::ChangeOfSheets, StringIDs::DyeYourBedADifferentColor},
        {0x57, L"MCTrophy_83", 0x57, StringIDs::CheatingDeath, StringIDs::UseTotemOfUndyingToCheatDeath},
        {0x58, L"MCTrophy_84", 0x58, StringIDs::SoIGotThatGoingForMe, StringIDs::LeadACaravanContainingAtLeast5Llamas},
        {0x59, L"MCTrophy_85", 0x59, StringIDs::LetItGo, StringIDs::WalkAcrossSurfaceOfADeepOceanBy},
        {0x5A, L"MCTrophy_86", 0x5A, StringIDs::FeelingIll, StringIDs::DefeatAnEvoker},
    };
};
