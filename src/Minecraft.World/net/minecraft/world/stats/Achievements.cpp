#include "net/minecraft/world/item/BowItem.h"
#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/stats/Achievement.h"

std::vector<Achievement*>* Achievements::ALL = new std::vector<Achievement*>;
Achievement* Achievements::OPEN_INVENTORY;
Achievement* Achievements::MINE_WOOD;
Achievement* Achievements::BUILD_WORK_BENCH;
Achievement* Achievements::BUILD_PICKAXE;
Achievement* Achievements::BUILD_FURNACE;
Achievement* Achievements::ACQUIRE_IRON;
Achievement* Achievements::BUILD_HOE;
Achievement* Achievements::MAKE_BREAD;
Achievement* Achievements::BAKE_CAKE;
Achievement* Achievements::BUILD_BETTER_PICKAXE;
Achievement* Achievements::COOK_FISH;
Achievement* Achievements::ON_ARAIL;
Achievement* Achievements::BUILD_SWORD;
Achievement* Achievements::KILL_ENEMY;
Achievement* Achievements::KILL_COW;
Achievement* Achievements::FLY_PIG;
Achievement* Achievements::LEADER_OF_THE_PACK;
Achievement* Achievements::MOARTOOLS;
Achievement* Achievements::DISPENSE_WITH_THIS;
Achievement* Achievements::IN_TO_THE_NETHER;
Achievement* Achievements::MINE100_BLOCKS;
Achievement* Achievements::KILL10_CREEPERS;
Achievement* Achievements::EAT_PORK_CHOP;
Achievement* Achievements::PLAY100_DAYS;
Achievement* Achievements::ARROW_KILL_CREEPER;
Achievement* Achievements::SOCIAL_POST;
Achievement* Achievements::SNIPE_SKELETON;
Achievement* Achievements::DIAMONDS;
Achievement* Achievements::GHAST;
Achievement* Achievements::BLAZE_ROD;
Achievement* Achievements::POTION;
Achievement* Achievements::THE_END;
Achievement* Achievements::THE_END2;
Achievement* Achievements::ENCHANTMENTS;
Achievement* Achievements::OVERKILL;
Achievement* Achievements::BOOKCASE;
Achievement* Achievements::ADVENTURING_TIME;
Achievement* Achievements::REPOPULATION;
Achievement* Achievements::DIAMONDS_TO_YOU;
Achievement* Achievements::THE_HAGGLER;
Achievement* Achievements::POT_PLANTER;
Achievement* Achievements::ITS_ASIGN;
Achievement* Achievements::IRON_BELLY;
Achievement* Achievements::HAVE_ASHEARFUL_DAY;
Achievement* Achievements::RAINBOW_COLLECTION;
Achievement* Achievements::STAYING_FROSTY;
Achievement* Achievements::CHESTFUL_OF_COBBLESTONE;
Achievement* Achievements::RENEWABLE_ENERGY;
Achievement* Achievements::MUSIC_TO_MY_EARS;
Achievement* Achievements::BODY_GUARD;
Achievement* Achievements::IRON_MAN;
Achievement* Achievements::ZOMBIE_DOCTOR;
Achievement* Achievements::LION_TAMER;
Achievement* Achievements::SPAWN_WITHER;
Achievement* Achievements::KILL_WITHER;
Achievement* Achievements::FULL_BEACON;
Achievement* Achievements::OVERPOWERED;
Achievement* Achievements::THE_DYE_OUTFIT;
Achievement* Achievements::TRAMPOLINE;
Achievement* Achievements::THE_STUDENT;
Achievement* Achievements::HAS_BECOME_THE_MASTER;
Achievement* Achievements::TIS_BUT_ASCRATCH;
Achievement* Achievements::CUPID;
Achievement* Achievements::YOU_WONT_LIKE_ME_WHEN_IM_HUNGRY;
Achievement* Achievements::MINE;
Achievement* Achievements::THE_END_AGAIN;
Achievement* Achievements::YOU_NEED_AMINT;
Achievement* Achievements::SUPER_SONIC;
Achievement* Achievements::DRY_SPELL;
Achievement* Achievements::FREE_DIVER;
Achievement* Achievements::SUPER_FUEL;
Achievement* Achievements::SADDLE_UP;
Achievement* Achievements::TASTE_OF_YOUR_OWN_MEDICINE;
Achievement* Achievements::BEAM_ME_UP;
Achievement* Achievements::MAP_ROOM;
Achievement* Achievements::CAMOUFLAGE;
Achievement* Achievements::BACK_FROM_THE_DEAD;
Achievement* Achievements::EQUIP_YOUR_FISTS;
Achievement* Achievements::TENACIOUS_BALL;
Achievement* Achievements::DEADSHOT;
Achievement* Achievements::SUCK_MY_SNOWBALLS;
Achievement* Achievements::MOUNTAIN_TOP;
Achievement* Achievements::WILL_LIKE_NO_OTHER;
Achievement* Achievements::THE_DEEP_END;
Achievement* Achievements::GREAT_VIEW_FROM_UP_HERE;
Achievement* Achievements::CHANGE_OF_SHEETS;
Achievement* Achievements::CHEATING_DEATH;
Achievement* Achievements::SO_IGOT_THAT_GOING_FOR_ME;
Achievement* Achievements::LET_IT_GO;
Achievement* Achievements::FEELING_ILL;
Achievement* Achievements::RABBIT_SEASON;
Achievement* Achievements::ORGANIZATIONAL_WIZARD;
Achievement* Achievements::GLIDER;
Achievement* Achievements::PILOT;
Achievement* Achievements::GO_GREEN;
Achievement* Achievements::GO_YELLOW;
Achievement* Achievements::GO_BLUE;
Achievement* Achievements::REPOPULATION_ALIAS;
Achievement* Achievements::ADVENTURING_TIME_ALIAS;

void Achievements::staticCtor() {
    OPEN_INVENTORY
        = (new Achievement(0, L"openInventory", 0, 0, Items::BOOK, nullptr))->setFlag()->registerStat(true);
    MINE_WOOD = (new Achievement(1, L"mineWood", 2, 1, Blocks::LOG, OPEN_INVENTORY))->registerStat(true);
    BUILD_WORK_BENCH = (new Achievement(2, L"buildWorkBench", 4, -1, Blocks::CRAFTING_TABLE, MINE_WOOD))
                           ->registerStat(true);
    BUILD_PICKAXE = (new Achievement(3, L"buildPickaxe", 4, 2, Items::WOODEN_PICKAXE, BUILD_WORK_BENCH))
                        ->registerStat(true);
    BUILD_FURNACE
        = (new Achievement(4, L"buildFurnace", 3, 4, Blocks::FURNACE, BUILD_PICKAXE))->registerStat(true);
    ACQUIRE_IRON
        = (new Achievement(5, L"acquireIron", 1, 4, Items::IRON_INGOT, BUILD_FURNACE))->registerStat(true);
    BUILD_HOE
        = (new Achievement(6, L"buildHoe", 2, -3, Items::WOODEN_HOE, BUILD_WORK_BENCH))->registerStat(true);
    MAKE_BREAD = (new Achievement(7, L"makeBread", -1, -3, Items::BREAD, BUILD_HOE))->registerStat(true);
    BAKE_CAKE = (new Achievement(8, L"bakeCake", 0, -5, Items::CAKE, BUILD_HOE))->registerStat(true);
    BUILD_BETTER_PICKAXE
        = (new Achievement(9, L"buildBetterPickaxe", 6, 2, Items::STONE_PICKAXE, BUILD_PICKAXE))
              ->registerStat(true);
    COOK_FISH
        = (new Achievement(10, L"cookFish", 2, 6, Items::COOKED_FISH, BUILD_FURNACE))->registerStat(true);
    ON_ARAIL = (new Achievement(11, L"onARail", 2, 3, Blocks::RAIL, ACQUIRE_IRON))
                   ->setSpecial()
                   ->registerStat(true);
    BUILD_SWORD = (new Achievement(12, L"buildSword", 6, -1, Items::WOODEN_SWORD, BUILD_WORK_BENCH))
                      ->registerStat(true);
    KILL_ENEMY = (new Achievement(13, L"killEnemy", 8, -1, Items::BONE, BUILD_SWORD))->registerStat(true);
    KILL_COW = (new Achievement(14, L"killCow", 7, -3, Items::LEATHER, BUILD_SWORD))->registerStat(true);
    FLY_PIG
        = (new Achievement(15, L"flyPig", 8, -4, Items::SADDLE, KILL_COW))->setSpecial()->registerStat(true);
    LEADER_OF_THE_PACK = (new Achievement(16, L"leaderOfThePack", 0, 0, Blocks::LOG, BUILD_SWORD))
                             ->setFlag()
                             ->registerStat(true);
    MOARTOOLS
        = (new Achievement(17, L"MOARTools", 0, 0, Blocks::LOG, BUILD_SWORD))->setFlag()->registerStat(true);
    DISPENSE_WITH_THIS
        = (new Achievement(18, L"dispenseWithThis", 0, 0, Blocks::LOG, BUILD_SWORD))->registerStat(true);
    IN_TO_THE_NETHER
        = (new Achievement(19, L"InToTheNether", 0, 0, Blocks::LOG, BUILD_SWORD))->registerStat(true);
    MINE100_BLOCKS = (new Achievement(20, L"mine100Blocks", 0, 0, Blocks::LOG, BUILD_SWORD))
                         ->setFlag()
                         ->registerStat(true);
    KILL10_CREEPERS = (new Achievement(21, L"kill10Creepers", 0, 0, Blocks::LOG, BUILD_SWORD))
                          ->setFlag()
                          ->registerStat(true);
    EAT_PORK_CHOP = (new Achievement(22, L"eatPorkChop", 0, 0, Blocks::LOG, BUILD_SWORD))
                        ->setFlag()
                        ->registerStat(true);
    PLAY100_DAYS = (new Achievement(23, L"play100Days", 0, 0, Blocks::LOG, BUILD_SWORD))
                       ->setFlag()
                       ->registerStat(true);
    ARROW_KILL_CREEPER
        = (new Achievement(24, L"arrowKillCreeper", 0, 0, Blocks::LOG, BUILD_SWORD))->registerStat(true);
    SOCIAL_POST = (new Achievement(25, L"socialPost", 0, 0, Blocks::LOG, BUILD_SWORD))->registerStat(true);
    SNIPE_SKELETON = (new Achievement(26, L"snipeSkeleton", 7, 0, Items::BOW, KILL_ENEMY))
                         ->setSpecial()
                         ->registerStat(true)
                         ->setIndependent();
    DIAMONDS = (new Achievement(27, L"diamonds", -1, 5, Items::DIAMOND, ACQUIRE_IRON))
                   ->registerStat(true)
                   ->setIndependent();
    GHAST = (new Achievement(29, L"ghast", -4, 8, Items::GHAST_TEAR, GHAST))
                ->setSpecial()
                ->registerStat(true)
                ->setIndependent();
    BLAZE_ROD = (new Achievement(30, L"blazeRod", 0, 9, Items::BLAZE_ROD, BLAZE_ROD))
                    ->registerStat(true)
                    ->setIndependent();
    POTION
        = (new Achievement(31, L"potion", 2, 8, Items::POTION, POTION))->registerStat(true)->setIndependent();
    THE_END = (new Achievement(32, L"theEnd", 3, 10, Items::ENDER_EYE, THE_END))
                  ->setSpecial()
                  ->registerStat(true)
                  ->setIndependent();
    THE_END2 = (new Achievement(33, L"theEnd2", 4, 13, Blocks::DRAGON_EGG, THE_END2))
                   ->setSpecial()
                   ->registerStat(true)
                   ->setIndependent();
    ENCHANTMENTS = (new Achievement(34, L"enchantments", -4, 4, Blocks::ENCHANTING_TABLE, ENCHANTMENTS))
                       ->registerStat(true)
                       ->setIndependent();
    OVERKILL = (new Achievement(35, L"overkill", -4, 1, Items::DIAMOND_SWORD, ENCHANTMENTS))
                   ->setSpecial()
                   ->registerStat(true)
                   ->setIndependent();
    BOOKCASE = (new Achievement(36, L"bookcase", -3, 6, Blocks::BOOKSHELF, ENCHANTMENTS))
                   ->registerStat(true)
                   ->setIndependent();
    ADVENTURING_TIME = (new Achievement(37, L"adventuringTime", 0, 0, Blocks::BOOKSHELF, nullptr))
                           ->setFlag()
                           ->registerStat(true)
                           ->setIndependent();
    REPOPULATION = (new Achievement(38, L"repopulation", 0, 0, Blocks::BOOKSHELF, nullptr))
                       ->registerStat(true)
                       ->setIndependent();
    DIAMONDS_TO_YOU = (new Achievement(39, L"diamondsToYou", 0, 0, Blocks::BOOKSHELF, nullptr))
                          ->registerStat(true)
                          ->setIndependent();
    THE_HAGGLER = (new Achievement(40, L"theHaggler", 0, 0, Blocks::BOOKSHELF, nullptr))
                      ->setFlag()
                      ->registerStat(true)
                      ->setIndependent();
    POT_PLANTER = (new Achievement(41, L"potPlanter", 0, 0, Blocks::BOOKSHELF, nullptr))
                      ->setFlag()
                      ->registerStat(true)
                      ->setIndependent();
    ITS_ASIGN = (new Achievement(42, L"itsASign", 0, 0, Blocks::BOOKSHELF, nullptr))
                    ->setFlag()
                    ->registerStat(true)
                    ->setIndependent();
    IRON_BELLY = (new Achievement(43, L"ironBelly", 0, 0, Blocks::BOOKSHELF, nullptr))
                     ->registerStat(true)
                     ->setIndependent();
    HAVE_ASHEARFUL_DAY = (new Achievement(44, L"haveAShearfulDay", 0, 0, Blocks::BOOKSHELF, nullptr))
                             ->registerStat(true)
                             ->setIndependent();
    RAINBOW_COLLECTION = (new Achievement(45, L"rainbowCollection", 0, 0, Blocks::BOOKSHELF, nullptr))
                             ->setFlag()
                             ->registerStat(true)
                             ->setIndependent();
    STAYING_FROSTY = (new Achievement(46, L"stayingFrosty", 0, 0, Blocks::BOOKSHELF, nullptr))
                         ->registerStat(true)
                         ->setIndependent();
    CHESTFUL_OF_COBBLESTONE
        = (new Achievement(47, L"chestfulOfCobblestone", 0, 0, Blocks::BOOKSHELF, nullptr))
              ->setFlag()
              ->registerStat(true)
              ->setIndependent();
    RENEWABLE_ENERGY = (new Achievement(48, L"renewableEnergy", 0, 0, Blocks::BOOKSHELF, nullptr))
                           ->registerStat(true)
                           ->setIndependent();
    MUSIC_TO_MY_EARS = (new Achievement(49, L"musicToMyEars", 0, 0, Blocks::BOOKSHELF, nullptr))
                           ->registerStat(true)
                           ->setIndependent();
    BODY_GUARD = (new Achievement(50, L"bodyGuard", 0, 0, Blocks::BOOKSHELF, nullptr))
                     ->registerStat(true)
                     ->setIndependent();
    IRON_MAN = (new Achievement(51, L"ironMan", 0, 0, Blocks::BOOKSHELF, nullptr))
                   ->setFlag()
                   ->registerStat(true)
                   ->setIndependent();
    ZOMBIE_DOCTOR = (new Achievement(52, L"zombieDoctor", 0, 0, Blocks::BOOKSHELF, nullptr))
                        ->registerStat(true)
                        ->setIndependent();
    LION_TAMER = (new Achievement(53, L"lionTamer", 0, 0, Blocks::BOOKSHELF, nullptr))
                     ->registerStat(true)
                     ->setIndependent();
    REPOPULATION_ALIAS = REPOPULATION;
    SPAWN_WITHER = (new Achievement(54, L"spawnWither", 0, 0, Blocks::BOOKSHELF, nullptr))
                       ->registerStat(true)
                       ->setIndependent();
    KILL_WITHER = (new Achievement(55, L"killWither", 0, 0, Blocks::BOOKSHELF, SPAWN_WITHER))
                      ->registerStat(true)
                      ->setIndependent();
    FULL_BEACON = (new Achievement(56, L"fullBeacon", 0, 0, Blocks::BOOKSHELF, KILL_WITHER))
                      ->registerStat(true)
                      ->setIndependent();
    ADVENTURING_TIME_ALIAS = ADVENTURING_TIME;
    OVERPOWERED = (new Achievement(57, L"overpowered", 0, 0, Blocks::BOOKSHELF, BUILD_BETTER_PICKAXE))
                      ->registerStat(true)
                      ->setIndependent();
    THE_DYE_OUTFIT = (new Achievement(58, L"theDyeOutfit", 0, 0, Blocks::BOOKSHELF, nullptr))
                         ->setFlag()
                         ->registerStat(true)
                         ->setIndependent();
    TRAMPOLINE = (new Achievement(59, L"trampoline", 0, 0, Blocks::BOOKSHELF, nullptr))
                     ->setFlag()
                     ->registerStat(true)
                     ->setIndependent();
    THE_STUDENT = (new Achievement(60, L"theStudent", 0, 0, Blocks::LOG, nullptr))
                      ->setFlag()
                      ->registerStat(true)
                      ->setIndependent();
    HAS_BECOME_THE_MASTER = (new Achievement(61, L"hasBecomeTheMaster", 0, 0, Blocks::LOG, nullptr))
                                ->setFlag()
                                ->registerStat(true)
                                ->setIndependent();
    TIS_BUT_ASCRATCH = (new Achievement(62, L"tisButAScratch", 0, 0, Blocks::LOG, nullptr))
                           ->registerStat(true)
                           ->setIndependent();
    CUPID = (new Achievement(63, L"cupid", 0, 0, Blocks::LOG, nullptr))->registerStat(true)->setIndependent();
    YOU_WONT_LIKE_ME_WHEN_IM_HUNGRY
        = (new Achievement(64, L"youWontLikeMeWhenImHungry,", 0, 0, Blocks::LOG, nullptr))
              ->registerStat(true)
              ->setIndependent();
    MINE = (new Achievement(65, L"mine,", 0, 0, Blocks::LOG, nullptr))->registerStat(true)->setIndependent();
    THE_END_AGAIN = (new Achievement(66, L"theEndAgain", 0, 0, Blocks::LOG, nullptr))
                        ->registerStat(true)
                        ->setIndependent();
    YOU_NEED_AMINT = (new Achievement(67, L"youNeedAMint", 0, 0, Blocks::LOG, nullptr))
                         ->registerStat(true)
                         ->setIndependent();
    SUPER_SONIC = (new Achievement(68, L"superSonic", 0, 0, Blocks::LOG, nullptr))
                      ->setFlag()
                      ->registerStat(true)
                      ->setIndependent();
    DRY_SPELL = (new Achievement(69, L"drySpell", 0, 0, Blocks::LOG, nullptr))
                    ->registerStat(true)
                    ->setIndependent();
    FREE_DIVER = (new Achievement(70, L"freeDiver", 0, 0, Blocks::LOG, nullptr))
                     ->setFlag()
                     ->registerStat(true)
                     ->setIndependent();
    SUPER_FUEL = (new Achievement(71, L"superFuel", 0, 0, Blocks::LOG, nullptr))
                     ->registerStat(true)
                     ->setIndependent();
    SADDLE_UP = (new Achievement(72, L"saddleUp", 0, 0, Blocks::LOG, nullptr))
                    ->registerStat(true)
                    ->setIndependent();
    TASTE_OF_YOUR_OWN_MEDICINE = (new Achievement(73, L"tasteOfYourOwnMedicine", 0, 0, Blocks::LOG, nullptr))
                                     ->registerStat(true)
                                     ->setIndependent();
    BEAM_ME_UP = (new Achievement(74, L"beamMeUp", 0, 0, Blocks::LOG, nullptr))
                     ->registerStat(true)
                     ->setIndependent();
    MAP_ROOM
        = (new Achievement(75, L"mapRoom", 0, 0, Blocks::LOG, nullptr))->registerStat(true)->setIndependent();
    CAMOUFLAGE = (new Achievement(76, L"camouflage", 0, 0, Blocks::LOG, nullptr))
                     ->registerStat(true)
                     ->setIndependent();
    BACK_FROM_THE_DEAD = (new Achievement(77, L"backFromTheDead", 0, 0, Blocks::LOG, nullptr))
                             ->registerStat(true)
                             ->setIndependent();
    EQUIP_YOUR_FISTS = (new Achievement(78, L"equipYourFists", 0, 0, Blocks::LOG, nullptr))
                           ->registerStat(true)
                           ->setIndependent();
    TENACIOUS_BALL = (new Achievement(79, L"tenaciousBall", 0, 0, Blocks::LOG, nullptr))
                         ->registerStat(true)
                         ->setIndependent();
    DEADSHOT = (new Achievement(80, L"deadshot", 0, 0, Blocks::LOG, nullptr))
                   ->registerStat(true)
                   ->setIndependent();
    SUCK_MY_SNOWBALLS = (new Achievement(81, L"suckMySnowballs", 0, 0, Blocks::LOG, nullptr))
                            ->registerStat(true)
                            ->setIndependent();
    MOUNTAIN_TOP = (new Achievement(82, L"mountainTop", 0, 0, Blocks::LOG, nullptr))
                       ->registerStat(true)
                       ->setIndependent();
    WILL_LIKE_NO_OTHER = (new Achievement(83, L"willLikeNoOther", 0, 0, Blocks::LOG, nullptr))
                             ->registerStat(true)
                             ->setIndependent();
    THE_DEEP_END = (new Achievement(84, L"theDeepEnd", 0, 0, Blocks::LOG, nullptr))
                       ->registerStat(true)
                       ->setIndependent();
    GREAT_VIEW_FROM_UP_HERE = (new Achievement(85, L"greatViewFromUpHere", 0, 0, Blocks::LOG, nullptr))
                                  ->registerStat(true)
                                  ->setIndependent();
    CHANGE_OF_SHEETS = (new Achievement(86, L"changeOfSheets", 0, 0, Blocks::LOG, nullptr))
                           ->registerStat(true)
                           ->setIndependent();
    CHEATING_DEATH = (new Achievement(87, L"cheatingDeath", 0, 0, Blocks::LOG, nullptr))
                         ->registerStat(true)
                         ->setIndependent();
    SO_IGOT_THAT_GOING_FOR_ME = (new Achievement(88, L"soIGotThatGoingForMe", 0, 0, Blocks::LOG, nullptr))
                                    ->registerStat(true)
                                    ->setIndependent();
    LET_IT_GO = (new Achievement(89, L"letItGo", 0, 0, Blocks::LOG, nullptr))
                    ->setFlag()
                    ->registerStat(true)
                    ->setIndependent();
    FEELING_ILL = (new Achievement(90, L"feelingIll", 0, 0, Blocks::LOG, nullptr))
                      ->registerStat(true)
                      ->setIndependent();
    RABBIT_SEASON = (new Achievement(91, L"rabbitSeason", 0, 0, Blocks::LOG, BUILD_SWORD))
                        ->setFlag()
                        ->registerStat(true);
    ORGANIZATIONAL_WIZARD = (new Achievement(92, L"organizationalWizard", 0, 0, Blocks::LOG, nullptr))
                                ->registerStat(true)
                                ->setIndependent();
    GLIDER
        = (new Achievement(93, L"glider", 0, 0, Blocks::LOG, nullptr))->registerStat(true)->setIndependent();
    PILOT = (new Achievement(94, L"pilot", 0, 0, Blocks::LOG, nullptr))->registerStat(true)->setIndependent();
    GO_GREEN
        = (new Achievement(95, L"goGreen", 0, 0, Blocks::LOG, nullptr))->registerStat(true)->setIndependent();
    GO_YELLOW = (new Achievement(96, L"goYellow", 0, 0, Blocks::LOG, nullptr))
                    ->registerStat(true)
                    ->setIndependent();
    GO_BLUE
        = (new Achievement(97, L"goBlue", 0, 0, Blocks::LOG, nullptr))->registerStat(true)->setIndependent();
}
