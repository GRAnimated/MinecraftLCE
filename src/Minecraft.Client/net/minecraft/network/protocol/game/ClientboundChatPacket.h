#pragma once

#include "net/minecraft/network/protocol/FlexiblePacket.h"

class ClientboundChatPacket : public FlexiblePacket,
                              public std::enable_shared_from_this<ClientboundChatPacket> {
public:
    static std::shared_ptr<Packet> create();

    // clang-format off
    enum EChatPacketMessage {
        EChatPacketMessage_ThisBedIsOccupied = 1,                                                          // 0xD08616D9
        EChatPacketMessage_YouCanOnlySleepAtNight = 2,                                                     // 0xFA2A57FA
        EChatPacketMessage_YourHomeBedWasMissingOrObstructed = 3,                                          // 0xE08B6A47
        EChatPacketMessage_YouMayNotRestNowReAreMonstersNearby = 4,                                        // 0x16C81B7F
        EChatPacketMessage_YouMayNotRestNowBedIsTooFarAway = 5,                                            // 0xF084EC0C
        EChatPacketMessage_PlayerWentUpInFlames = 13,                                                      // 0xEFC9FEF0
        EChatPacketMessage_PlayerWasStruckByLightning = 14,                                                // 0xF4980932
        EChatPacketMessage_PlayerBurnedToDeath = 15,                                                       // 0xD711D936
        EChatPacketMessage_PlayerTriedToSwimInLava = 16,                                                   // 0x5EFF1005
        EChatPacketMessage_PlayerSuffocatedInAWall = 17,                                                   // 0x6AE921B6
        EChatPacketMessage_PlayerDrowned = 19,                                                             // 0x576593EF
        EChatPacketMessage_PlayerStarvedToDeath = 20,                                                      // 0xF244DF30
        EChatPacketMessage_PlayerWasPrickedToDeath = 21,                                                   // 0x2BF5A7DC
        EChatPacketMessage_PlayerHitGroundTooHard = 22,                                                    // 0xD63D2190
        EChatPacketMessage_PlayerExperiencedKineticEnergy = 23,                                            // 0x15C8F4AE
        EChatPacketMessage_PlayerFellOutOfWorld = 24,                                                      // 0x6F2C7352
        EChatPacketMessage_PlayerDied = 26,                                                                // 0xD98E2236
        EChatPacketMessage_PlayerWasKilledByMagic = 28,                                                    // 0x189C795E
        EChatPacketMessage_PlayerWasSlainBySource = 29,                                                    // 0x4BEC30BF
        EChatPacketMessage_PlayerWasSlainBySource_1 = 30,                                                  // 0x3C5DA2B4
        EChatPacketMessage_PlayerWasShotBySource = 31,                                                     // 0x7A2A89AE
        EChatPacketMessage_PlayerWasFireballedBySource = 32,                                               // 0x242D45C
        EChatPacketMessage_PlayerWasPummeledBySource = 33,                                                 // 0xB3FB4F7F
        EChatPacketMessage_PlayerWasKilledBySourceUsingMagic = 34,                                         // 0x3FC22003
        EChatPacketMessage_PlayerWasKilledByEnderDragonBreath = 35,                                        // 0x2DCF5941
        EChatPacketMessage_PlayerWasSquashedByAFallingAnvil = 36,                                          // 0xD235D4B
        EChatPacketMessage_PlayerWasSquashedByAFallingBlock = 37,                                          // 0xA1216033
        EChatPacketMessage_PlayerWasKilledTryingToHurtSource = 39,                                         // 0x5AC8AFBB
        EChatPacketMessage_PlayerFellOffALadder = 41,                                                      // 0x62F8280D
        EChatPacketMessage_PlayerFellOffSomeVines = 42,                                                    // 0x461BA4E8
        EChatPacketMessage_PlayerFellOutOfWater = 43,                                                      // 0xC130636A
        EChatPacketMessage_PlayerFellFromAHighPlace = 44,                                                  // 0x44E2DD06
        EChatPacketMessage_PlayerWasDoomedToFall = 45,                                                     // 0x8BC1A50E
        EChatPacketMessage_PlayerWasDoomedToFallBySource = 46,                                             // 0x1ECE8CFC
        EChatPacketMessage_PlayerWasDoomedToFallBySourceUsing = 47,                                        // 0xD871BB46
        EChatPacketMessage_PlayerFellTooFarAndWasFinishedByUsingItem = 49,                                 // 0x3EC0C74A
        EChatPacketMessage_PlayerWalkedIntoFireWhilstFightingSource = 50,                                  // 0xC30A962C
        EChatPacketMessage_PlayerWasStruckByLightning_1 = 51,                                              // 0xF4980932
        EChatPacketMessage_PlayerWasBurntToACrispWhilstFighting = 52,                                      // 0x48FFBD9A
        EChatPacketMessage_PlayerTriedToSwimInLavaToEscape = 53,                                           // 0xE2B2D991
        EChatPacketMessage_PlayerDrownedWhilstTryingToEscapeSource = 54,                                   // 0xCF30BEFB
        EChatPacketMessage_PlayerWalkedIntoACactusWhilstTryingTo = 55,                                     // 0x7AD1A880
        EChatPacketMessage_PlayerWasBlownUpBySource = 56,                                                  // 0xAF29A206
        EChatPacketMessage_PlayerWitheredAway = 57,                                                        // 0x516DB1A2
        EChatPacketMessage_PlayerWasSlainBySourceUsingItem = 58,                                           // 0x31C3794E
        EChatPacketMessage_PlayerWasShotBySourceUsingItem = 59,                                            // 0xF0EBA2E4
        EChatPacketMessage_PlayerWasFireballedBySourceUsingItem = 60,                                      // 0x31B789A6
        EChatPacketMessage_PlayerWasPummeledBySourceUsingItem = 61,                                        // 0xE3BE8E0D
        EChatPacketMessage_PlayerDiscoveredFloorWasLava = 62,                                              // 0x1A3B16DB
        EChatPacketMessage_PlayerWalkedIntoDangerZoneDueToSource = 63,                                     // 0x9EEFF8CF
        EChatPacketMessage_PlayerWasKilledBySourceUsingItem = 64,                                          // 0x6046121
        EChatPacketMessage_CantUseSpawnEggAtMomentTheMaximumAnimalsExcludingWolvesChickensAnd = 67,        // 0x9F8BFFAE
        EChatPacketMessage_CantUseSpawnEggAtMomentTheMaximumChickens = 68,                                 // 0x82460728
        EChatPacketMessage_CantUseSpawnEggAtMomentTheMaximumSquid = 69,                                    // 0x1E0D17D0
        EChatPacketMessage_CantUseSpawnEggAtMomentTheMaximumMooshrooms = 70,                               // 0x3E35B6E8
        EChatPacketMessage_CantUseSpawnEggAtMomentTheMaximumWolves = 71,                                   // 0x70EDC806
        EChatPacketMessage_CantUseSpawnEggAtMomentTheMaximumEnemies = 73,                                  // 0xA82B5A66
        EChatPacketMessage_CantUseSpawnEggAtMomentTheMaximumVillagers = 74,                                // 0x16972FBF
        EChatPacketMessage_TheMaximumNumberOfPaintingsItemFramesIn = 75,                                   // 0x1EE681BA
        EChatPacketMessage_TheMaximumNumberOfArmorStandsInA = 76,                                          // 0x8ECD701E
        EChatPacketMessage_YouCantSpawnEnemiesInPeacefulMode = 77,                                         // 0xD97FDBA2
        EChatPacketMessage_ThisAnimalCantEnterLoveModeTheMaximumAnimalsExcludingWolvesAndMooshrooms = 79,  // 0xB399BD15
        EChatPacketMessage_ThisAnimalCantEnterLoveModeTheMaximum = 80,                                     // 0x99326383
        EChatPacketMessage_ThisAnimalCantEnterLoveModeTheMaximumMooshrooms = 81,                           // 0xFE5875
        EChatPacketMessage_ThisAnimalCantEnterLoveModeTheMaximumWolves = 82,                               // 0xEC344E3D
        EChatPacketMessage_CantShearThisMooshroomAtMomentTheMaximum = 83,                                  // 0x3221ECE8
        EChatPacketMessage_TheMaximumNumberOfBoatsInAWorld = 84,                                           // 0xB2145884
        EChatPacketMessage_TheMaximumNumberOfMinecartsInAWorld = 85,                                       // 0xB604AAFF
        EChatPacketMessage_CantUseSpawnEggAtMomentTheMaximum = 86,                                         // 0xFAB1DEB6
        EChatPacketMessage_TheMaximumNumberOfBannersInAWorld = 87,                                         // 0xFDF65C18
        EChatPacketMessage_TheMaximumNumberOfEnderCrystalsInA = 88,                                        // 0xC952E8B9
        EChatPacketMessage_TheMaximumNumberOfBeaconsInAWorld = 89,                                         // 0xEF12CC40
        EChatPacketMessage_PlayerTeleportedYouToirPosition = 91,                                           // 0x5C19FA7A
        EChatPacketMessage_PlayerTeleportedToYou = 92,                                                     // 0x186485A6
        EChatPacketMessage_FailedToSetWorldSpawnPointYouMust = 97,                                         // 0x334E4F83
        EChatPacketMessage_FailedToSetPlayerSSpawnPointYou = 99,                                           // 0xA7D52E1F
        EChatPacketMessage_ChangingToClearWeather = 100,                                                   // 0xB5F2B622
        EChatPacketMessage_ChangingToRainyWeather = 101,                                                   // 0x3CED883F
        EChatPacketMessage_ChangingToRainAndThunder = 102,                                                 // 0xA09D437
        EChatPacketMessage_SetOwnGameModeToMode = 103,                                                     // 0xDA993CC6
        EChatPacketMessage_YourGameModeHasChanged = 105,                                                   // 0xDD05C6B4
        EChatPacketMessage_PlayerCommand = 106,                                                            // 0xD2BD3683
        EChatPacketMessage_SelectingMode = 107,                                                            // 0xCFEB0335
        EChatPacketMessage_WaitingForDataLoad = 108,                                                       // 0x6E12057
        EChatPacketMessage_ChangingGame = 109,                                                             // 0x9760A9E7
        EChatPacketMessage_Starting = 110,                                                                 // 0x52F1EF84
        EChatPacketMessage_RoundStart = 111,                                                               // 0x7CCCD9D4
        EChatPacketMessage_EndingGame = 112,                                                               // 0x69E5CA0B
        EChatPacketMessage_RoundEnd = 113,                                                                 // 0xC4219DE3
        EChatPacketMessage_YouAreNowSpectating = 114,                                                      // 0xB0B23BCD
        EChatPacketMessage_InvulnerabilityHasWornOffFight = 118,                                           // 0xF53F833A
        EChatPacketMessage_WaitingForLessThanQuantityObjectToEvent = 124,                                  // 0x2FB55D20
        EChatPacketMessage_WaitingForNoMoreThanQuantityObjectTo = 125,                                     // 0xB8AF706D
        EChatPacketMessage_WaitingForMoreThanThanQuantityObjectTo = 126,                                   // 0xA19C12DB
        EChatPacketMessage_WaitingForAtLeastQuantityObjectToEvent = 127,                                   // 0x431EEECE
        EChatPacketMessage_QuantityOrMoreAdditionalPlayersAreRequiredTo = 129,                             // 0xAAE0D4FF
        EChatPacketMessage_WaitingForQuantityOrMorePlayersToBe = 130,                                      // 0x6ACB714A
        EChatPacketMessage_WeaponsAndFoodHaveSpawnedSomewhereInArena = 131,                                // 0xA292A825
        EChatPacketMessage_WeaponsAndFoodHaveSpawnedAtCenterOfArena = 132,                                 // 0x3041D7AC
        EChatPacketMessage_SpecialItemsHaveSpawnedSomewhereInArena = 133,                                  // 0x90C46BBB
        EChatPacketMessage_TeamsAreDisabled = 134,                                                         // 0xB7FC5190
        EChatPacketMessage_NotEnoughSurvivorsToTeamUp = 136,                                               // 0x9988B49
        EChatPacketMessage_PlayerInvitedYouToJoinTeam = 137,                                               // 0xC08F5C90
        EChatPacketMessage_PlayerWasAddedToTeam = 139,                                                     // 0xADC5F08E
        EChatPacketMessage_YouWereAddedToTeam = 140,                                                       // 0x87C37625
        EChatPacketMessage_PlayerIsLeavingTeam = 141,                                                      // 0xE9D46798
        EChatPacketMessage_YouAreLeavingTeam = 142,                                                        // 0x5BDBD6D3
        EChatPacketMessage_YouLeftTeam = 143,                                                              // 0x39B60856
        EChatPacketMessage_Fight = 146,                                                                    // 0xBC3B07CD
        EChatPacketMessage_ShowdownHasStartedMiiCharacterNamesAreNow = 147,                                // 0xD296C94C
        EChatPacketMessage_NoPlayersToSpectate = 149,                                                      // 0x6A14E1E7
    };
    // clang-format on

    ClientboundChatPacket(EChatPacketMessage message, int);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    char fill[2];
};
