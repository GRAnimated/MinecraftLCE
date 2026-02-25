#pragma once

#include "net/minecraft/client/ui/StringIDs.h"

void RegisterAwardsWithProfileManager();

struct AwardInfo {
    long m_idx;  // 64 bit sized on NX but only 32 bit sized on wiiu
    const wchar_t* m_id;
    int m_idx2;
    unsigned int m_name;  // TODO: are these meant to be unsigned? It throws errors if not.
    unsigned int m_desc;
};

enum eAwardType { _0 = 0 };

// I have doubts that this should be in UIScene_AchievementsMenu
// maybe cAchievements?
// or it's some NMW shit since afaik it was in ghs UnityWorld static thing
struct Awards {
    static constexpr int sAchievementSlots[]  // also used to register the textures
        = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 22, 23,
           24, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
           47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
           69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};

    static constexpr AwardInfo sAwards[] = {
        {0, L"MCTrophy_00", 1, StringIDs::TakingInventory, StringIDs::OpenYourInventory},
        {1, L"MCTrophy_01", 2, StringIDs::GettingWood, StringIDs::PunchATreeUntilABlockOfWoodPopsOut},
        {2, L"MCTrophy_02", 3, StringIDs::Benchmarking, StringIDs::CraftAWorkbenchWithFourBlocksOfWooden},
        {3, L"MCTrophy_10", 4, StringIDs::TimeToMine, StringIDs::UsePlanksAndSticksToMakeAPickaxe},
        {4, L"MCTrophy_12", 5, StringIDs::HotTopic, StringIDs::ConstructAFurnaceOutOfEightCobblestoneBlocks},
        {5, L"MCTrophy_14", 6, StringIDs::AcquireHardware, StringIDs::SmeltAnIronIngot},
        {6, L"MCTrophy_03", 7, StringIDs::TimeToFarm, StringIDs::MakeAHoe},
        {7, L"MCTrophy_04", 8, StringIDs::BakeBread, StringIDs::TurnWheatIntoBread},
        {8, L"MCTrophy_05", 9, StringIDs::TheLie, StringIDs::BakeACakeUsingWheatSugarMilkAndEggs},
        {9, L"MCTrophy_11", 10, StringIDs::GettingAnUpgrade, StringIDs::ConstructABetterPickaxe},
        {10, L"MCTrophy_13", 11, StringIDs::DeliciousFish, StringIDs::CatchAndCookFish},
        {11, L"MCTrophy_15", 12, StringIDs::OnARail, StringIDs::TravelByMinecartToAPointAtLeast},
        {12, L"MCTrophy_06", 13, StringIDs::TimeToStrike, StringIDs::UsePlanksAndSticksToMakeASword},
        {13, L"MCTrophy_07", 14, StringIDs::MonsterHunter, StringIDs::AttackAndDestroyAMonster},
        {14, L"MCTrophy_08", 15, StringIDs::CowTipper, StringIDs::HarvestSomeLeather},
        {15, L"MCTrophy_09", 16, StringIDs::WhenPigsFly, StringIDs::UseASaddleToRideAPigAndn},
        {16, L"MCTrophy_16", 17, StringIDs::LeaderOfPack, StringIDs::BefriendFiveWolves},
        {17, L"MCTrophy_17", 18, StringIDs::MoarTools, StringIDs::ConstructOneTypeOfEachTool},
        {18, L"MCTrophy_18", 19, StringIDs::DispenseWithThis, StringIDs::ConstructADispenser},
        {19, L"MCTrophy_19", 20, StringIDs::IntoTheNether, StringIDs::ConstructANetherPortal},
        {20, L"", 0, 0, 0},
        {21, L"", 0, 0, 0},
        {22, L"MCTrophy_33", 34, StringIDs::PorkChop, StringIDs::CookAndEatAPorkChop},
        {23, L"MCTrophy_34", 35, StringIDs::PassingTime, StringIDs::PlayFor100Days},
        {24, L"MCTrophy_35", 36, StringIDs::Archer, StringIDs::KillACreeperWithArrows},
        {25, L"", 0, 0, 0},
        {26, L"MCTrophy_20", 21, StringIDs::SniperDuel, StringIDs::KillASkeletonWithAnArrowFromMore},
        {27, L"MCTrophy_21", 22, StringIDs::Diamonds, StringIDs::AcquireDiamondsWithYourIronTools},
        {28, L"", 0, 0, 0},
        {29, L"MCTrophy_22", 23, StringIDs::ReturnToSender, StringIDs::DestroyAGhastWithAFireball},
        {30, L"MCTrophy_23", 24, StringIDs::IntoFire, StringIDs::RelieveABlazeOfItsRod},
        {31, L"MCTrophy_24", 25, StringIDs::LocalBrewery, StringIDs::BrewAPotion},
        {32, L"MCTrophy_25", 26, StringIDs::TheEnd, StringIDs::EnterAnEndPortal},
        {33, L"MCTrophy_26", 27, StringIDs::TheEnd_1, StringIDs::KillEnderdragon},
        {34, L"MCTrophy_27", 28, StringIDs::Enchanter, StringIDs::ConstructAnEnchantmentTable},
        {35, L"MCTrophy_28", 29, StringIDs::Overkill, StringIDs::DealNineHeartsOfDamageInASingleHit},
        {36, L"MCTrophy_29", 30, StringIDs::Librarian,
         StringIDs::BuildSomeBookshelvesToImproveYourEnchantmentTable},
        {37, L"MCTrophy_30", 31, StringIDs::AdventuringTime, StringIDs::Discover17Of40DifferentBiomes},
        {38, L"MCTrophy_31", 32, StringIDs::Repopulation, StringIDs::BreedTwoCowsWithWheat},
        {39, L"MCTrophy_32", 33, StringIDs::DiamondsToYou, StringIDs::ThrowDiamondsAtAnotherPlayer},
        {40, L"MCTrophy_36", 37, StringIDs::TheHaggler, StringIDs::MineOrPurchase30Emeralds},
        {41, L"MCTrophy_37", 38, StringIDs::PotPlanter, StringIDs::CraftAndPlaceAFlowerPot},
        {42, L"MCTrophy_38", 39, StringIDs::ItSASign, StringIDs::CraftAndPlaceASign},
        {43, L"MCTrophy_39", 40, StringIDs::IronBelly, StringIDs::StopStarvationUsingRottenFlesh},
        {44, L"MCTrophy_40", 41, StringIDs::HaveAShearfulDay, StringIDs::UseShearsToObtainWoolFromASheep},
        {45, L"MCTrophy_41", 42, StringIDs::RainbowCollection, StringIDs::GatherAll16ColorsOfWool},
        {46, L"MCTrophy_42", 43, StringIDs::StayinFrosty,
         StringIDs::SwimInLavaWhileHavingFireResistanceEffect},
        {47, L"MCTrophy_43", 44, StringIDs::ChestfulOfCobblestone,
         StringIDs::Mine1728CobblestoneAndPlaceItInAChest},
        {48, L"MCTrophy_44", 45, StringIDs::RenewableEnergy,
         StringIDs::SmeltWoodTrunksUsingCharcoalToMakeMore},
        {49, L"MCTrophy_45", 46, StringIDs::MusicToMyEars, StringIDs::PlayAMusicDiscInAJukebox},
        {50, L"MCTrophy_46", 47, StringIDs::BodyGuard, StringIDs::CreateAnIronGolem},
        {51, L"MCTrophy_47", 48, StringIDs::IronMan, StringIDs::WearAFullSuitOfIronArmor},
        {52, L"MCTrophy_48", 49, StringIDs::ZombieDoctor, StringIDs::CureAZombieVillager},
        {53, L"MCTrophy_49", 50, StringIDs::LionTamer, StringIDs::TameAnOcelot},
        {54, L"MCTrophy_50", 51, StringIDs::TheBeginning, StringIDs::SpawnWither},
        {55, L"MCTrophy_51", 52, StringIDs::TheBeginning_1, StringIDs::KillWither},
        {56, L"MCTrophy_52", 53, StringIDs::Beaconator, StringIDs::CreateAndFullyPowerABeacon},
        {57, L"MCTrophy_53", 54, StringIDs::Overpowered, StringIDs::EatANotchApple},
        {58, L"MCTrophy_54", 55, StringIDs::TieDyeOutfit, StringIDs::DyeAll4UniquePiecesOfLeatherArmor},
        {59, L"MCTrophy_55", 59, StringIDs::Trampoline, StringIDs::Bounce30BlocksUpwardOffASlimeBlock},
        {60, L"MCTrophy_56", 60, StringIDs::TheStudent, StringIDs::WinAPublicBattleMiniGame},
        {61, L"MCTrophy_57", 61, StringIDs::HasBecomeMaster, StringIDs::Win3PublicBattleMiniGamesInARow},
        {62, L"MCTrophy_58", 62, StringIDs::TisButAScratch, StringIDs::Take100DamageInARoundOfA},
        {63, L"MCTrophy_59", 63, StringIDs::Cupid, StringIDs::Kill2PlayersInARoundOfPublic},
        {64, L"MCTrophy_60", 64, StringIDs::HungerPain, StringIDs::KillAPlayerWhileYouAreStarvingIn},
        {65, L"MCTrophy_61", 65, StringIDs::Mine, StringIDs::OpenEveryChestInABattleMiniGame},
        {66, L"MCTrophy_62", 66, StringIDs::TheEndAgain, StringIDs::RespawnEnderdragon},
        {67, L"MCTrophy_63", 67, StringIDs::YouNeedAMint, StringIDs::CollectDragonSBreathInAGlassBottle},
        {68, L"MCTrophy_64", 68, StringIDs::SuperSonic, StringIDs::UseAnElytraToFlyThroughA1},
        {69, L"MCTrophy_65", 69, StringIDs::DrySpell, StringIDs::DryASpongeInAFurnace},
        {70, L"MCTrophy_66", 70, StringIDs::FreeDiver, StringIDs::StayUnderwaterFor2Minutes},
        {71, L"MCTrophy_67", 71, StringIDs::SuperFuel, StringIDs::PowerAFurnaceWithLava},
        {72, L"MCTrophy_68", 72, StringIDs::SaddleUp, StringIDs::TameAHorse},
        {73, L"MCTrophy_69", 73, StringIDs::TasteOfYourOwnMedicine, StringIDs::PoisonAWitchWithASplashPotion},
        {74, L"MCTrophy_70", 74, StringIDs::BeamMeUp, StringIDs::TeleportOver100MetersFromASingleThrow},
        {75, L"MCTrophy_71", 75, StringIDs::MapRoom_1, StringIDs::PlaceAFullyExploredMapIntoAnItemFrame_1},
        {76, L"MCTrophy_72", 76, StringIDs::Camouflage_1, StringIDs::KillAMobWhileWearingSameTypeOfMobHead_1},
        {77, L"MCTrophy_73", 77, StringIDs::BackFromDead, StringIDs::Win3RoundsInARowAfterOne},
        {78, L"MCTrophy_74", 78, StringIDs::SNoThrow, StringIDs::WinASingleRoundOfSnowballTumbleWithout},
        {79, L"MCTrophy_75", 79, StringIDs::SnowStorm, StringIDs::HitASinglePlayerWith25SnowballsIn},
        {80, L"MCTrophy_76", 80, StringIDs::Hotshot, StringIDs::HitAPlayerWithASnowballWhileFalling},
        {81, L"MCTrophy_77", 81, StringIDs::Snowplough, StringIDs::PushThreePlayersIntoLavaUsingSnowballs},
        {82, L"MCTrophy_78", 82, StringIDs::Overlord, StringIDs::StayOnTopLayerWhileWinningARound},
        {83, L"MCTrophy_79", 83, StringIDs::Underdog, StringIDs::WinATumbleGameWhilstOnLowestLayer},
        {84, L"MCTrophy_80", 84, StringIDs::TheDeepEnd, StringIDs::DefeatAnElderGuardian},
        {85, L"MCTrophy_81", 85, StringIDs::GreatViewFromUpHere,
         StringIDs::LevitateUp50BlocksFromAttacksOfAShulker},
        {86, L"MCTrophy_82", 86, StringIDs::ChangeOfSheets, StringIDs::DyeYourBedADifferentColor},
        {87, L"MCTrophy_83", 87, StringIDs::CheatingDeath, StringIDs::UseTotemOfUndyingToCheatDeath},
        {88, L"MCTrophy_84", 88, StringIDs::SoIGotThatGoingForMe,
         StringIDs::LeadACaravanContainingAtLeast5Llamas},
        {89, L"MCTrophy_85", 89, StringIDs::LetItGo, StringIDs::WalkAcrossSurfaceOfADeepOceanBy},
        {90, L"MCTrophy_86", 90, StringIDs::FeelingIll, StringIDs::DefeatAnEvoker},
    };
};
