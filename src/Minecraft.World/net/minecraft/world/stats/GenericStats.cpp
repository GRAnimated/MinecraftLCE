#include "net/minecraft/world/stats/GenericStats.h"

Stat* GenericStats::get_achievement(eAward) {
    return nullptr;
}

Stat* GenericStats::get_walkOneM() {
    return nullptr;
}

Stat* GenericStats::get_swimOneM() {
    return nullptr;
}

Stat* GenericStats::get_fallOneM() {
    return nullptr;
}

Stat* GenericStats::get_climbOneM() {
    return nullptr;
}

Stat* GenericStats::get_minecartOneM() {
    return nullptr;
}

Stat* GenericStats::get_boatOneM() {
    return nullptr;
}

Stat* GenericStats::get_pigOneM() {
    return nullptr;
}

Stat* GenericStats::get_portalsCreated() {
    return nullptr;
}

Stat* GenericStats::get_cowsMilked() {
    return nullptr;
}

Stat* GenericStats::get_netherLavaCollected() {
    return nullptr;
}

Stat* GenericStats::get_killMob() {
    return nullptr;
}

Stat* GenericStats::get_killsZombie() {
    return nullptr;
}

Stat* GenericStats::get_killsSkeleton() {
    return nullptr;
}

Stat* GenericStats::get_killsCreeper() {
    return nullptr;
}

Stat* GenericStats::get_killsSpider() {
    return nullptr;
}

Stat* GenericStats::get_killsSpiderJockey() {
    return nullptr;
}

Stat* GenericStats::get_killsZombiePigman() {
    return nullptr;
}

Stat* GenericStats::get_killsSlime() {
    return nullptr;
}

Stat* GenericStats::get_killsGhast() {
    return nullptr;
}

Stat* GenericStats::get_killsNetherZombiePigman() {
    return nullptr;
}

Stat* GenericStats::get_breedEntity(eINSTANCEOF) {
    return nullptr;
}

Stat* GenericStats::get_tamedEntity(eINSTANCEOF) {
    return nullptr;
}

Stat* GenericStats::get_curedEntity(eINSTANCEOF) {
    return nullptr;
}

Stat* GenericStats::get_craftedEntity(eINSTANCEOF) {
    return nullptr;
}

Stat* GenericStats::get_shearedEntity(eINSTANCEOF) {
    return nullptr;
}

Stat* GenericStats::get_totalBlocksMined() {
    return nullptr;
}

Stat* GenericStats::get_timePlayed() {
    return nullptr;
}

Stat* GenericStats::get_blocksPlaced(int) {
    return nullptr;
}

Stat* GenericStats::get_blocksMined(int) {
    return nullptr;
}

Stat* GenericStats::get_itemsCollected(int, int) {
    return nullptr;
}

Stat* GenericStats::get_itemsCrafted(int) {
    return nullptr;
}

Stat* GenericStats::get_itemsSmelted(int itemId) {
    return get_itemsCrafted(itemId);
}

Stat* GenericStats::get_itemsUsed(int itemId) {
    return nullptr;
}

Stat* GenericStats::get_itemsBought(int) {
    return nullptr;
}

Stat* GenericStats::get_armourDyed(int) {
    return nullptr;
}

Stat* GenericStats::get_killsEnderdragon() {
    return nullptr;
}

Stat* GenericStats::get_completeTheEnd() {
    return nullptr;
}

Stat* GenericStats::get_changedDimension(int, int) {
    return nullptr;
}

Stat* GenericStats::get_enteredBiome(int) {
    return nullptr;
}

Stat* GenericStats::get_MG03_Score() {
    return nullptr;
}

Stat* GenericStats::get_MG03_RingCount() {
    return nullptr;
}

Stat* GenericStats::get_MG03_BestTimeScoreChallenge() {
    return nullptr;
}

Stat* GenericStats::get_MG03_BestTime() {
    return nullptr;
}

arrayWithLength<unsigned char> GenericStats::getParam_walkOneM(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_swimOneM(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_fallOneM(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_climbOneM(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_minecartOneM(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_boatOneM(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_pigOneM(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_cowsMilked() {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_blocksPlaced(int, int, int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_blocksMined(int, int, int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_itemsCollected(int, int, int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_itemsCrafted(int, int, int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_itemsSmelted(int a2, int a3, int a4) {
    return getParam_itemsCrafted(a2, a3, a4);
}

arrayWithLength<unsigned char> GenericStats::getParam_itemsUsed(std::shared_ptr<Player>,
                                                                not_null_ptr<ItemInstance>) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_itemsBought(int, int, int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_mobKill(std::shared_ptr<Player>, std::shared_ptr<Mob>,
                                                              DamageSource*) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_breedEntity(eINSTANCEOF) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_tamedEntity(eINSTANCEOF) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_curedEntity(eINSTANCEOF) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_craftedEntity(eINSTANCEOF) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_shearedEntity(eINSTANCEOF) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_time(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_changedDimension(int, int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_enteredBiome(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_achievement(eAward) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_onARail(int) {
    return getParam_achievement(eAward_ON_A_RAIL);
}

arrayWithLength<unsigned char> GenericStats::getParam_overkill(int) {
    return getParam_achievement(eAward_OVERKILL);
}

arrayWithLength<unsigned char> GenericStats::getParam_openInventory(int) {
    return getParam_achievement(eAward_OPEN_INVENTORY);
}

arrayWithLength<unsigned char> GenericStats::getParam_chestfulOfCobblestone(int) {
    return getParam_achievement(eAward_CHESTFUL_OF_COBBLESTONE);
}

arrayWithLength<unsigned char> GenericStats::getParam_musicToMyEars(int) {
    return getParam_achievement(eAward_MUSIC_TO_MY_EARS);
}

arrayWithLength<unsigned char> GenericStats::getParam_MG03Score(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_MG03RingCount(int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_MG03BestTime(unsigned int) {
    return getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_tieDyeOutfit(int) {
    return getParam_achievement(eAward_TIE_DYE_OUTFIT);
}

arrayWithLength<unsigned char> GenericStats::getParam_trampoline(int) {
    return getParam_achievement(eAward_TRAMPOLINE);
}

arrayWithLength<unsigned char> GenericStats::getParam_spawnWither() {
    return getParam_achievement(eAward_SPAWN_WITHER);
}

arrayWithLength<unsigned char> GenericStats::getParam_killWither() {
    return getParam_achievement(eAward_KILL_WITHER);
}

arrayWithLength<unsigned char> GenericStats::getParam_fullBeacon() {
    return getParam_achievement(eAward_FULL_BEACON);
}

arrayWithLength<unsigned char> GenericStats::getParam_overpowered() {
    return getParam_achievement(eAward_OVERPOWERED);
}

arrayWithLength<unsigned char> GenericStats::getParam_smeltEverything() {
    return sInstance->getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_camouflage() {
    return sInstance->getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_freightStation() {
    return sInstance->getParam_noArgs();
}

arrayWithLength<unsigned char> GenericStats::getParam_theStudent() {
    return getParam_achievement(eAward_THE_STUDENT);
}

arrayWithLength<unsigned char> GenericStats::getParam_hasBecomeTheMaster() {
    return getParam_achievement(eAward_HAS_BECOME_THE_MASTER);
}

arrayWithLength<unsigned char> GenericStats::getParam_tisButAScratch() {
    return getParam_achievement(eAward_TIS_BUT_A_SCRATCH);
}

arrayWithLength<unsigned char> GenericStats::getParam_cupid() {
    return getParam_achievement(eAward_CUPID);
}

arrayWithLength<unsigned char> GenericStats::getParam_youWontLikeMeWhenImHungry() {
    return getParam_achievement(eAward_YOU_WONT_LIKE_ME_WHEN_IM_HUNGRY);
}

arrayWithLength<unsigned char> GenericStats::getParam_mine() {
    return getParam_achievement(eAward_MINE);
}

arrayWithLength<unsigned char> GenericStats::getParam_superSonic(int) {
    return getParam_achievement(eAward_SUPER_SONIC);
}

arrayWithLength<unsigned char> GenericStats::getParam_freeDiver(int) {
    return getParam_achievement(eAward_FREE_DIVER);
}

arrayWithLength<unsigned char> GenericStats::getParam_beamMeUp(int) {
    return getParam_achievement(eAward_BEAM_ME_UP);
}

arrayWithLength<unsigned char> GenericStats::getParam_mapRoom(int) {
    return getParam_achievement(eAward_MAP_ROOM);
}

arrayWithLength<unsigned char> GenericStats::getParam_tenaciousBall(int) {
    return getParam_achievement(eAward_TENACIOUS_BALL);
}

arrayWithLength<unsigned char> GenericStats::getParam_suckMySnowballs(int) {
    return getParam_achievement(eAward_SUCK_MY_SNOWBALLS);
}

arrayWithLength<unsigned char> GenericStats::getParam_greatViewFromUpHere(int) {
    return getParam_achievement(eAward_GREAT_VIEW_FROM_UP_HERE);
}

arrayWithLength<unsigned char> GenericStats::getParam_soIGotThatGoingForMe(int) {
    return getParam_achievement(eAward_SO_I_GOT_THAT_GOING_FOR_ME);
}

arrayWithLength<unsigned char> GenericStats::getParam_noArgs() {
    return arrayWithLength<unsigned char>();
}

Stat* GenericStats::openInventory() {
    return sInstance->get_achievement(eAward_OPEN_INVENTORY);
}

Stat* GenericStats::mineWood() {
    return sInstance->get_achievement(eAward_MINE_WOOD);
}

Stat* GenericStats::buildWorkbench() {
    return sInstance->get_achievement(eAward_BUILD_WORKBENCH);
}

Stat* GenericStats::buildPickaxe() {
    return sInstance->get_achievement(eAward_BUILD_PICKAXE);
}

Stat* GenericStats::buildFurnace() {
    return sInstance->get_achievement(eAward_BUILD_FURNACE);
}

Stat* GenericStats::buildHoe() {
    return sInstance->get_achievement(eAward_BUILD_HOE);
}

Stat* GenericStats::makeBread() {
    return sInstance->get_achievement(eAward_MAKE_BREAD);
}

Stat* GenericStats::bakeCake() {
    return sInstance->get_achievement(eAward_BAKE_CAKE);
}

Stat* GenericStats::buildBetterPickaxe() {
    return sInstance->get_achievement(eAward_BUILD_BETTER_PICKAXE);
}

Stat* GenericStats::onARail() {
    return sInstance->get_achievement(eAward_ON_A_RAIL);
}

Stat* GenericStats::buildSword() {
    return sInstance->get_achievement(eAward_BUILD_SWORD);
}

Stat* GenericStats::killEnemy() {
    return sInstance->get_achievement(eAward_KILL_ENEMY);
}

Stat* GenericStats::killCow() {
    return sInstance->get_achievement(eAward_KILL_COW);
}

Stat* GenericStats::flyPig() {
    return sInstance->get_achievement(eAward_FLY_PIG);
}

Stat* GenericStats::snipeSkeleton() {
    return sInstance->get_achievement(eAward_SNIPE_SKELETON);
}

Stat* GenericStats::diamonds() {
    return sInstance->get_achievement(eAward_DIAMONDS);
}

Stat* GenericStats::ghast() {
    return sInstance->get_achievement(eAward_GHAST);
}

Stat* GenericStats::blazeRod() {
    return sInstance->get_achievement(eAward_BLAZE_ROD);
}

Stat* GenericStats::potion() {
    return sInstance->get_achievement(eAward_POTION);
}

Stat* GenericStats::theEnd() {
    return sInstance->get_achievement(eAward_THE_END);
}

Stat* GenericStats::winGame() {
    return sInstance->get_achievement(eAward_WIN_GAME);
}

Stat* GenericStats::enchantments() {
    return sInstance->get_achievement(eAward_ENCHANTMENTS);
}

Stat* GenericStats::overkill() {
    return sInstance->get_achievement(eAward_OVERKILL);
}

Stat* GenericStats::bookcase() {
    return sInstance->get_achievement(eAward_BOOKCASE);
}

Stat* GenericStats::leaderOfThePack() {
    return sInstance->get_achievement(eAward_LEADER_OF_THE_PACK);
}

Stat* GenericStats::MOARTools() {
    return sInstance->get_achievement(eAward_MOAR_TOOLS);
}

Stat* GenericStats::dispenseWithThis() {
    return sInstance->get_achievement(eAward_DISPENSE_WITH_THIS);
}

Stat* GenericStats::adventuringTime() {
    return sInstance->get_achievement(eAward_ADVENTURING_TIME);
}

Stat* GenericStats::repopulation() {
    return sInstance->get_achievement(eAward_REPOPULATION);
}

Stat* GenericStats::porkChop() {
    return sInstance->get_achievement(eAward_PORK_CHOP);
}

Stat* GenericStats::diamondsToYou() {
    return sInstance->get_achievement(eAward_DIAMONDS_TO_YOU);
}

Stat* GenericStats::passingTheTime() {
    return sInstance->get_achievement(eAward_PASSING_THE_TIME);
}

Stat* GenericStats::archer() {
    return sInstance->get_achievement(eAward_ARCHER);
}

Stat* GenericStats::theHaggler() {
    return sInstance->get_achievement(eAward_THE_HAGGLER);
}

Stat* GenericStats::potPlanter() {
    return sInstance->get_achievement(eAward_POT_PLANTER);
}

Stat* GenericStats::itsASign() {
    return sInstance->get_achievement(eAward_ITS_A_SIGN);
}

Stat* GenericStats::haveAShearfulDay() {
    return sInstance->get_achievement(eAward_HAVE_A_SHEARFUL_DAY);
}

Stat* GenericStats::rainbowCollection() {
    return sInstance->get_achievement(eAward_RAINBOW_COLLECTION);
}

Stat* GenericStats::stayinFrosty() {
    return sInstance->get_achievement(eAward_STAYIN_FROSTY);
}

Stat* GenericStats::chestfulOfCobblestone() {
    return sInstance->get_achievement(eAward_CHESTFUL_OF_COBBLESTONE);
}

Stat* GenericStats::musicToMyEars() {
    return sInstance->get_achievement(eAward_MUSIC_TO_MY_EARS);
}

Stat* GenericStats::bodyGuard() {
    return sInstance->get_achievement(eAward_BODY_GUARD);
}

Stat* GenericStats::ironMan() {
    return sInstance->get_achievement(eAward_IRON_MAN);
}

Stat* GenericStats::zombieDoctor() {
    return sInstance->get_achievement(eAward_ZOMBIE_DOCTOR);
}

Stat* GenericStats::lionTamer() {
    return sInstance->get_achievement(eAward_LION_TAMER);
}

Stat* GenericStats::spawnWither() {
    return sInstance->get_achievement(eAward_SPAWN_WITHER);
}

Stat* GenericStats::killWither() {
    return sInstance->get_achievement(eAward_KILL_WITHER);
}

Stat* GenericStats::fullBeacon() {
    return sInstance->get_achievement(eAward_FULL_BEACON);
}

Stat* GenericStats::overpowered() {
    return sInstance->get_achievement(eAward_OVERPOWERED);
}

Stat* GenericStats::tieDyeOutfit() {
    return sInstance->get_achievement(eAward_TIE_DYE_OUTFIT);
}

Stat* GenericStats::trampoline() {
    return sInstance->get_achievement(eAward_TRAMPOLINE);
}

Stat* GenericStats::theStudent() {
    return sInstance->get_achievement(eAward_THE_STUDENT);
}

Stat* GenericStats::hasBecomeTheMaster() {
    return sInstance->get_achievement(eAward_HAS_BECOME_THE_MASTER);
}

Stat* GenericStats::tisButAScratch() {
    return sInstance->get_achievement(eAward_TIS_BUT_A_SCRATCH);
}

Stat* GenericStats::cupid() {
    return sInstance->get_achievement(eAward_CUPID);
}

Stat* GenericStats::youWontLikeMeWhenImHungry() {
    return sInstance->get_achievement(eAward_YOU_WONT_LIKE_ME_WHEN_IM_HUNGRY);
}

Stat* GenericStats::mine() {
    return sInstance->get_achievement(eAward_MINE);
}

Stat* GenericStats::theEndAgain() {
    return sInstance->get_achievement(eAward_THE_END_AGAIN);
}

Stat* GenericStats::youNeedAMint() {
    return sInstance->get_achievement(eAward_YOU_NEED_A_MINT);
}

Stat* GenericStats::superSonic() {
    return sInstance->get_achievement(eAward_SUPER_SONIC);
}

Stat* GenericStats::freeDiver() {
    return sInstance->get_achievement(eAward_FREE_DIVER);
}

Stat* GenericStats::tasteOfYourOwnMedicine() {
    return sInstance->get_achievement(eAward_TASTE_OF_YOUR_OWN_MEDICINE);
}

Stat* GenericStats::beamMeUp() {
    return sInstance->get_achievement(eAward_BEAM_ME_UP);
}

Stat* GenericStats::mapRoom() {
    return sInstance->get_achievement(eAward_MAP_ROOM);
}

Stat* GenericStats::camouflage() {
    return sInstance->get_achievement(eAward_CAMOUFLAGE);
}

Stat* GenericStats::backFromTheDead() {
    return sInstance->get_achievement(eAward_BACK_FROM_THE_DEAD);
}

Stat* GenericStats::equipYourFists() {
    return sInstance->get_achievement(eAward_EQUIP_YOUR_FISTS);
}

Stat* GenericStats::tenaciousBall() {
    return sInstance->get_achievement(eAward_TENACIOUS_BALL);
}

Stat* GenericStats::deadshot() {
    return sInstance->get_achievement(eAward_DEADSHOT);
}

Stat* GenericStats::suckMySnowballs() {
    return sInstance->get_achievement(eAward_SUCK_MY_SNOWBALLS);
}

Stat* GenericStats::mountainTop() {
    return sInstance->get_achievement(eAward_MOUNTAIN_TOP);
}

Stat* GenericStats::willLikeNoOther() {
    return sInstance->get_achievement(eAward_WILL_LIKE_NO_OTHER);
}

Stat* GenericStats::theDeepEnd() {
    return sInstance->get_achievement(eAward_THE_DEEP_END);
}

Stat* GenericStats::greatViewFromUpHere() {
    return sInstance->get_achievement(eAward_GREAT_VIEW_FROM_UP_HERE);
}

Stat* GenericStats::changeOfSheets() {
    return sInstance->get_achievement(eAward_CHANGE_OF_SHEETS);
}

Stat* GenericStats::cheatingDeath() {
    return sInstance->get_achievement(eAward_CHEATING_DEATH);
}

Stat* GenericStats::soIGotThatGoingForMe() {
    return sInstance->get_achievement(eAward_SO_I_GOT_THAT_GOING_FOR_ME);
}

Stat* GenericStats::feelingIll() {
    return sInstance->get_achievement(eAward_FEELING_ILL);
}

arrayWithLength<unsigned char> GenericStats::param_openInventory() {
    return sInstance->getParam_achievement(eAward_OPEN_INVENTORY);
}

arrayWithLength<unsigned char> GenericStats::param_buildWorkbench() {
    return sInstance->getParam_achievement(eAward_BUILD_WORKBENCH);
}

arrayWithLength<unsigned char> GenericStats::param_buildPickaxe() {
    return sInstance->getParam_achievement(eAward_BUILD_PICKAXE);
}

arrayWithLength<unsigned char> GenericStats::param_buildFurnace() {
    return sInstance->getParam_achievement(eAward_BUILD_FURNACE);
}

arrayWithLength<unsigned char> GenericStats::param_buildHoe() {
    return sInstance->getParam_achievement(eAward_BUILD_HOE);
}

arrayWithLength<unsigned char> GenericStats::param_makeBread() {
    return sInstance->getParam_achievement(eAward_MAKE_BREAD);
}

arrayWithLength<unsigned char> GenericStats::param_bakeCake() {
    return sInstance->getParam_achievement(eAward_BAKE_CAKE);
}

arrayWithLength<unsigned char> GenericStats::param_buildBetterPickaxe() {
    return sInstance->getParam_achievement(eAward_BUILD_BETTER_PICKAXE);
}

arrayWithLength<unsigned char> GenericStats::param_onARail(int a1) {
    return sInstance->getParam_onARail(a1);
}

arrayWithLength<unsigned char> GenericStats::param_buildSword() {
    return sInstance->getParam_achievement(eAward_BUILD_SWORD);
}

arrayWithLength<unsigned char> GenericStats::param_flyPig() {
    return sInstance->getParam_achievement(eAward_FLY_PIG);
}

arrayWithLength<unsigned char> GenericStats::param_snipeSkeleton() {
    return sInstance->getParam_achievement(eAward_SNIPE_SKELETON);
}

arrayWithLength<unsigned char> GenericStats::param_diamonds() {
    return sInstance->getParam_achievement(eAward_DIAMONDS);
}

arrayWithLength<unsigned char> GenericStats::param_ghast() {
    return sInstance->getParam_achievement(eAward_GHAST);
}

arrayWithLength<unsigned char> GenericStats::param_blazeRod() {
    return sInstance->getParam_achievement(eAward_BLAZE_ROD);
}

arrayWithLength<unsigned char> GenericStats::param_potion() {
    return sInstance->getParam_achievement(eAward_POTION);
}

arrayWithLength<unsigned char> GenericStats::param_theEnd() {
    return sInstance->getParam_achievement(eAward_THE_END);
}

arrayWithLength<unsigned char> GenericStats::param_winGame() {
    return sInstance->getParam_achievement(eAward_WIN_GAME);
}

arrayWithLength<unsigned char> GenericStats::param_enchantments() {
    return sInstance->getParam_achievement(eAward_ENCHANTMENTS);
}

arrayWithLength<unsigned char> GenericStats::param_overkill(int a1) {
    return sInstance->getParam_overkill(a1);
}

arrayWithLength<unsigned char> GenericStats::param_bookcase() {
    return sInstance->getParam_achievement(eAward_BOOKCASE);
}

arrayWithLength<unsigned char> GenericStats::param_dispenseWithThis() {
    return sInstance->getParam_achievement(eAward_DISPENSE_WITH_THIS);
}

arrayWithLength<unsigned char> GenericStats::param_theEndAgain() {
    return sInstance->getParam_achievement(eAward_THE_END_AGAIN);
}

arrayWithLength<unsigned char> GenericStats::param_youNeedAMint() {
    return sInstance->getParam_achievement(eAward_YOU_NEED_A_MINT);
}

arrayWithLength<unsigned char> GenericStats::param_tasteOfYourOwnMedicine() {
    return sInstance->getParam_achievement(eAward_TASTE_OF_YOUR_OWN_MEDICINE);
}

arrayWithLength<unsigned char> GenericStats::param_backFromTheDead() {
    return sInstance->getParam_achievement(eAward_BACK_FROM_THE_DEAD);
}

arrayWithLength<unsigned char> GenericStats::param_equipYourFists() {
    return sInstance->getParam_achievement(eAward_EQUIP_YOUR_FISTS);
}

arrayWithLength<unsigned char> GenericStats::param_deadshot() {
    return sInstance->getParam_achievement(eAward_DEADSHOT);
}

arrayWithLength<unsigned char> GenericStats::param_mountainTop() {
    return sInstance->getParam_achievement(eAward_MOUNTAIN_TOP);
}

arrayWithLength<unsigned char> GenericStats::param_willLikeNoOther() {
    return sInstance->getParam_achievement(eAward_WILL_LIKE_NO_OTHER);
}

arrayWithLength<unsigned char> GenericStats::param_changeOfSheets() {
    return sInstance->getParam_achievement(eAward_CHANGE_OF_SHEETS);
}

arrayWithLength<unsigned char> GenericStats::param_adventuringTime() {
    return sInstance->getParam_achievement(eAward_ADVENTURING_TIME);
}

arrayWithLength<unsigned char> GenericStats::param_porkChop() {
    return sInstance->getParam_achievement(eAward_PORK_CHOP);
}

arrayWithLength<unsigned char> GenericStats::param_diamondsToYou() {
    return sInstance->getParam_achievement(eAward_DIAMONDS_TO_YOU);
}

arrayWithLength<unsigned char> GenericStats::param_passingTheTime() {
    return sInstance->getParam_achievement(eAward_PASSING_THE_TIME);
}

arrayWithLength<unsigned char> GenericStats::param_archer() {
    return sInstance->getParam_achievement(eAward_ARCHER);
}

arrayWithLength<unsigned char> GenericStats::param_theHaggler() {
    return sInstance->getParam_achievement(eAward_THE_HAGGLER);
}

arrayWithLength<unsigned char> GenericStats::param_potPlanter() {
    return sInstance->getParam_achievement(eAward_POT_PLANTER);
}

arrayWithLength<unsigned char> GenericStats::param_itsASign() {
    return sInstance->getParam_achievement(eAward_ITS_A_SIGN);
}

arrayWithLength<unsigned char> GenericStats::param_rainbowCollection() {
    return sInstance->getParam_achievement(eAward_RAINBOW_COLLECTION);
}

arrayWithLength<unsigned char> GenericStats::param_stayinFrosty() {
    return sInstance->getParam_achievement(eAward_STAYIN_FROSTY);
}

arrayWithLength<unsigned char> GenericStats::param_ironMan() {
    return sInstance->getParam_achievement(eAward_IRON_MAN);
}

arrayWithLength<unsigned char> GenericStats::param_zombieDoctor() {
    return sInstance->getParam_achievement(eAward_ZOMBIE_DOCTOR);
}
