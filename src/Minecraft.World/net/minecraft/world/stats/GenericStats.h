#pragma once

#include "net/minecraft/world/item/Item.h"
#include "types.h"
#include <memory>

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/eAward.h"
#include "net/minecraft/world/eINSTANCEOF.h"

class DamageSource;
class ItemInstance;
class Mob;
class Player;
class Stat;
class Item;

class GenericStats {
public:
    static GenericStats* sInstance;

    GenericStats() = default;

    virtual ~GenericStats() {}
    virtual Stat* get_stat(int) = 0;
    virtual Stat* get_achievement(eAward);
    virtual Stat* get_walkOneM();
    virtual Stat* get_swimOneM();
    virtual Stat* get_fallOneM();
    virtual Stat* get_climbOneM();
    virtual Stat* get_minecartOneM();
    virtual Stat* get_boatOneM();
    virtual Stat* get_pigOneM();
    virtual Stat* get_portalsCreated();
    virtual Stat* get_cowsMilked();
    virtual Stat* get_netherLavaCollected();
    virtual Stat* get_killMob();
    virtual Stat* get_killsZombie();
    virtual Stat* get_killsSkeleton();
    virtual Stat* get_killsCreeper();
    virtual Stat* get_killsSpider();
    virtual Stat* get_killsSpiderJockey();
    virtual Stat* get_killsZombiePigman();
    virtual Stat* get_killsSlime();
    virtual Stat* get_killsGhast();
    virtual Stat* get_killsNetherZombiePigman();
    virtual Stat* get_breedEntity(eINSTANCEOF);
    virtual Stat* get_tamedEntity(eINSTANCEOF);
    virtual Stat* get_curedEntity(eINSTANCEOF);
    virtual Stat* get_craftedEntity(eINSTANCEOF);
    virtual Stat* get_shearedEntity(eINSTANCEOF);
    virtual Stat* get_totalBlocksMined();
    virtual Stat* get_timePlayed();
    virtual Stat* get_blocksPlaced(int);
    virtual Stat* get_blocksMined(int);
    virtual Stat* get_itemsCollected(int, int);
    virtual Stat* get_itemsCrafted(int itemId);
    virtual Stat* get_itemsSmelted(int itemId);
    virtual Stat* get_itemsUsed(int itemId);
    virtual Stat* get_itemsBought(int);
    virtual Stat* get_armourDyed(int);
    virtual Stat* get_killsEnderdragon();
    virtual Stat* get_completeTheEnd();
    virtual Stat* get_changedDimension(int, int);
    virtual Stat* get_enteredBiome(int);
    virtual Stat* get_MG03_Score();
    virtual Stat* get_MG03_RingCount();
    virtual Stat* get_MG03_BestTimeScoreChallenge();
    virtual Stat* get_MG03_BestTime();

    virtual arrayWithLength<unsigned char> getParam_walkOneM(int);
    virtual arrayWithLength<unsigned char> getParam_swimOneM(int);
    virtual arrayWithLength<unsigned char> getParam_fallOneM(int);
    virtual arrayWithLength<unsigned char> getParam_climbOneM(int);
    virtual arrayWithLength<unsigned char> getParam_minecartOneM(int);
    virtual arrayWithLength<unsigned char> getParam_boatOneM(int);
    virtual arrayWithLength<unsigned char> getParam_pigOneM(int);
    virtual arrayWithLength<unsigned char> getParam_cowsMilked();
    virtual arrayWithLength<unsigned char> getParam_blocksPlaced(int, int, int);
    virtual arrayWithLength<unsigned char> getParam_blocksMined(int, int, int);
    virtual arrayWithLength<unsigned char> getParam_itemsCollected(int, int, int);
    virtual arrayWithLength<unsigned char> getParam_itemsCrafted(int, int, int);
    virtual arrayWithLength<unsigned char> getParam_itemsSmelted(int, int, int);
    virtual arrayWithLength<unsigned char> getParam_itemsUsed(std::shared_ptr<Player>,
                                                              not_null_ptr<ItemInstance>);
    virtual arrayWithLength<unsigned char> getParam_itemsBought(int, int, int);
    virtual arrayWithLength<unsigned char> getParam_mobKill(std::shared_ptr<Player>, std::shared_ptr<Mob>,
                                                            DamageSource*);
    virtual arrayWithLength<unsigned char> getParam_breedEntity(eINSTANCEOF);
    virtual arrayWithLength<unsigned char> getParam_tamedEntity(eINSTANCEOF);
    virtual arrayWithLength<unsigned char> getParam_curedEntity(eINSTANCEOF);
    virtual arrayWithLength<unsigned char> getParam_craftedEntity(eINSTANCEOF);
    virtual arrayWithLength<unsigned char> getParam_shearedEntity(eINSTANCEOF);
    virtual arrayWithLength<unsigned char> getParam_time(int);
    virtual arrayWithLength<unsigned char> getParam_changedDimension(int, int);
    virtual arrayWithLength<unsigned char> getParam_enteredBiome(int);
    virtual arrayWithLength<unsigned char> getParam_achievement(eAward);
    virtual arrayWithLength<unsigned char> getParam_onARail(int);
    virtual arrayWithLength<unsigned char> getParam_overkill(int);
    virtual arrayWithLength<unsigned char> getParam_openInventory(int);
    virtual arrayWithLength<unsigned char> getParam_chestfulOfCobblestone(int);
    virtual arrayWithLength<unsigned char> getParam_musicToMyEars(int);
    virtual arrayWithLength<unsigned char> getParam_MG03Score(int);
    virtual arrayWithLength<unsigned char> getParam_MG03RingCount(int);
    virtual arrayWithLength<unsigned char> getParam_MG03BestTime(unsigned int);
    virtual arrayWithLength<unsigned char> getParam_tieDyeOutfit(int);
    virtual arrayWithLength<unsigned char> getParam_trampoline(int);
    virtual arrayWithLength<unsigned char> getParam_spawnWither();
    virtual arrayWithLength<unsigned char> getParam_killWither();
    virtual arrayWithLength<unsigned char> getParam_fullBeacon();
    virtual arrayWithLength<unsigned char> getParam_overpowered();
    virtual arrayWithLength<unsigned char> getParam_smeltEverything();
    virtual arrayWithLength<unsigned char> getParam_camouflage();
    virtual arrayWithLength<unsigned char> getParam_freightStation();
    virtual arrayWithLength<unsigned char> getParam_theStudent();
    virtual arrayWithLength<unsigned char> getParam_hasBecomeTheMaster();
    virtual arrayWithLength<unsigned char> getParam_tisButAScratch();
    virtual arrayWithLength<unsigned char> getParam_cupid();
    virtual arrayWithLength<unsigned char> getParam_youWontLikeMeWhenImHungry();
    virtual arrayWithLength<unsigned char> getParam_mine();
    virtual arrayWithLength<unsigned char> getParam_superSonic(int);
    virtual arrayWithLength<unsigned char> getParam_freeDiver(int);
    virtual arrayWithLength<unsigned char> getParam_beamMeUp(int);
    virtual arrayWithLength<unsigned char> getParam_mapRoom(int);
    virtual arrayWithLength<unsigned char> getParam_tenaciousBall(int);
    virtual arrayWithLength<unsigned char> getParam_suckMySnowballs(int);
    virtual arrayWithLength<unsigned char> getParam_greatViewFromUpHere(int);
    virtual arrayWithLength<unsigned char> getParam_soIGotThatGoingForMe(int);
    virtual arrayWithLength<unsigned char> getParam_noArgs();

    static Stat* openInventory();
    static Stat* mineWood();
    static Stat* buildWorkbench();
    static Stat* buildPickaxe();
    static Stat* buildFurnace();
    static Stat* buildHoe();
    static Stat* makeBread();
    static Stat* bakeCake();
    static Stat* buildBetterPickaxe();
    static Stat* onARail();
    static Stat* buildSword();
    static Stat* killEnemy();
    static Stat* killCow();
    static Stat* flyPig();
    static Stat* snipeSkeleton();
    static Stat* diamonds();
    static Stat* ghast();
    static Stat* blazeRod();
    static Stat* potion();
    static Stat* theEnd();
    static Stat* winGame();
    static Stat* enchantments();
    static Stat* overkill();
    static Stat* bookcase();
    static Stat* leaderOfThePack();
    static Stat* MOARTools();
    static Stat* dispenseWithThis();
    static Stat* adventuringTime();
    static Stat* repopulation();
    static Stat* porkChop();
    static Stat* diamondsToYou();
    static Stat* passingTheTime();
    static Stat* archer();
    static Stat* theHaggler();
    static Stat* potPlanter();
    static Stat* itsASign();
    static Stat* haveAShearfulDay();
    static Stat* rainbowCollection();
    static Stat* stayinFrosty();
    static Stat* chestfulOfCobblestone();
    static Stat* musicToMyEars();
    static Stat* bodyGuard();
    static Stat* ironMan();
    static Stat* zombieDoctor();
    static Stat* lionTamer();
    static Stat* spawnWither();
    static Stat* killWither();
    static Stat* fullBeacon();
    static Stat* overpowered();
    static Stat* tieDyeOutfit();
    static Stat* trampoline();
    static Stat* theStudent();
    static Stat* hasBecomeTheMaster();
    static Stat* tisButAScratch();
    static Stat* cupid();
    static Stat* youWontLikeMeWhenImHungry();
    static Stat* mine();
    static Stat* theEndAgain();
    static Stat* youNeedAMint();
    static Stat* superSonic();
    static Stat* freeDiver();
    static Stat* tasteOfYourOwnMedicine();
    static Stat* beamMeUp();
    static Stat* mapRoom();
    static Stat* camouflage();
    static Stat* backFromTheDead();
    static Stat* equipYourFists();
    static Stat* tenaciousBall();
    static Stat* deadshot();
    static Stat* suckMySnowballs();
    static Stat* mountainTop();
    static Stat* willLikeNoOther();
    static Stat* theDeepEnd();
    static Stat* greatViewFromUpHere();
    static Stat* changeOfSheets();
    static Stat* cheatingDeath();
    static Stat* soIGotThatGoingForMe();
    static Stat* feelingIll();

    static Stat* getItemsUsedStat(Item* item) {  // guessed, this shouldn't be part of upper ones as the
                                                 // uppers ones aren't inlined on WiiU
        return GenericStats::sInstance->get_itemsUsed(Item::VALIDgetId(item));
    }

    static arrayWithLength<unsigned char> param_openInventory();
    static arrayWithLength<unsigned char> param_buildWorkbench();
    static arrayWithLength<unsigned char> param_buildPickaxe();
    static arrayWithLength<unsigned char> param_buildFurnace();
    static arrayWithLength<unsigned char> param_buildHoe();
    static arrayWithLength<unsigned char> param_makeBread();
    static arrayWithLength<unsigned char> param_bakeCake();
    static arrayWithLength<unsigned char> param_buildBetterPickaxe();
    static arrayWithLength<unsigned char> param_onARail(int);
    static arrayWithLength<unsigned char> param_buildSword();
    static arrayWithLength<unsigned char> param_flyPig();
    static arrayWithLength<unsigned char> param_snipeSkeleton();
    static arrayWithLength<unsigned char> param_diamonds();
    static arrayWithLength<unsigned char> param_ghast();
    static arrayWithLength<unsigned char> param_blazeRod();
    static arrayWithLength<unsigned char> param_potion();
    static arrayWithLength<unsigned char> param_theEnd();
    static arrayWithLength<unsigned char> param_winGame();
    static arrayWithLength<unsigned char> param_enchantments();
    static arrayWithLength<unsigned char> param_overkill(int);
    static arrayWithLength<unsigned char> param_bookcase();
    static arrayWithLength<unsigned char> param_dispenseWithThis();
    static arrayWithLength<unsigned char> param_theEndAgain();
    static arrayWithLength<unsigned char> param_youNeedAMint();
    static arrayWithLength<unsigned char> param_tasteOfYourOwnMedicine();
    static arrayWithLength<unsigned char> param_backFromTheDead();
    static arrayWithLength<unsigned char> param_equipYourFists();
    static arrayWithLength<unsigned char> param_deadshot();
    static arrayWithLength<unsigned char> param_mountainTop();
    static arrayWithLength<unsigned char> param_willLikeNoOther();
    static arrayWithLength<unsigned char> param_changeOfSheets();
    static arrayWithLength<unsigned char> param_adventuringTime();
    static arrayWithLength<unsigned char> param_porkChop();
    static arrayWithLength<unsigned char> param_diamondsToYou();
    static arrayWithLength<unsigned char> param_passingTheTime();
    static arrayWithLength<unsigned char> param_archer();
    static arrayWithLength<unsigned char> param_theHaggler();
    static arrayWithLength<unsigned char> param_potPlanter();
    static arrayWithLength<unsigned char> param_itsASign();
    static arrayWithLength<unsigned char> param_rainbowCollection();
    static arrayWithLength<unsigned char> param_stayinFrosty();
    static arrayWithLength<unsigned char> param_ironMan();
    static arrayWithLength<unsigned char> param_zombieDoctor();
    static arrayWithLength<unsigned char> param_itemsUsed(std::shared_ptr<Player>,
                                                          not_null_ptr<ItemInstance>);
};
