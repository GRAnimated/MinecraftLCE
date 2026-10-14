#pragma once

#include "net/minecraft/world/stats/Stat.h"
#include "types.h"

class Item;
class Block;
class ItemInstance;

class Achievement : public Stat {
public:
    Achievement(int, const std::wstring&, int, int, Item*, Achievement*);
    Achievement(int, const std::wstring&, int, int, Block*, Achievement*);
    ~Achievement() override;
    Achievement* setFlag();
    Achievement* setSpecial();
    Achievement* registerStat(bool) override;
    bool isAchievement() override;
    Achievement* setIndependent();
    int getAchievementId();

private:
    int m_x, m_y;
    Achievement* m_parent;
    std::wstring m_description;
    void* m_unused96;
    not_null_ptr<ItemInstance> m_icon;
    bool m_special;
};

class Achievements {
public:
    static void staticCtor();
    static std::vector<Achievement*>* ALL;
    static Achievement* OPEN_INVENTORY;
    static Achievement* MINE_WOOD;
    static Achievement* BUILD_WORK_BENCH;
    static Achievement* BUILD_PICKAXE;
    static Achievement* BUILD_FURNACE;
    static Achievement* ACQUIRE_IRON;
    static Achievement* BUILD_HOE;
    static Achievement* MAKE_BREAD;
    static Achievement* BAKE_CAKE;
    static Achievement* BUILD_BETTER_PICKAXE;
    static Achievement* COOK_FISH;
    static Achievement* ON_ARAIL;
    static Achievement* BUILD_SWORD;
    static Achievement* KILL_ENEMY;
    static Achievement* KILL_COW;
    static Achievement* FLY_PIG;
    static Achievement* LEADER_OF_THE_PACK;
    static Achievement* MOARTOOLS;
    static Achievement* DISPENSE_WITH_THIS;
    static Achievement* IN_TO_THE_NETHER;
    static Achievement* MINE100_BLOCKS;
    static Achievement* KILL10_CREEPERS;
    static Achievement* EAT_PORK_CHOP;
    static Achievement* PLAY100_DAYS;
    static Achievement* ARROW_KILL_CREEPER;
    static Achievement* SOCIAL_POST;
    static Achievement* SNIPE_SKELETON;
    static Achievement* DIAMONDS;
    static Achievement* GHAST;
    static Achievement* BLAZE_ROD;
    static Achievement* POTION;
    static Achievement* THE_END;
    static Achievement* THE_END2;
    static Achievement* ENCHANTMENTS;
    static Achievement* OVERKILL;
    static Achievement* BOOKCASE;
    static Achievement* ADVENTURING_TIME;
    static Achievement* REPOPULATION;
    static Achievement* DIAMONDS_TO_YOU;
    static Achievement* THE_HAGGLER;
    static Achievement* POT_PLANTER;
    static Achievement* ITS_ASIGN;
    static Achievement* IRON_BELLY;
    static Achievement* HAVE_ASHEARFUL_DAY;
    static Achievement* RAINBOW_COLLECTION;
    static Achievement* STAYING_FROSTY;
    static Achievement* CHESTFUL_OF_COBBLESTONE;
    static Achievement* RENEWABLE_ENERGY;
    static Achievement* MUSIC_TO_MY_EARS;
    static Achievement* BODY_GUARD;
    static Achievement* IRON_MAN;
    static Achievement* ZOMBIE_DOCTOR;
    static Achievement* LION_TAMER;
    static Achievement* SPAWN_WITHER;
    static Achievement* KILL_WITHER;
    static Achievement* FULL_BEACON;
    static Achievement* OVERPOWERED;
    static Achievement* THE_DYE_OUTFIT;
    static Achievement* TRAMPOLINE;
    static Achievement* THE_STUDENT;
    static Achievement* HAS_BECOME_THE_MASTER;
    static Achievement* TIS_BUT_ASCRATCH;
    static Achievement* CUPID;
    static Achievement* YOU_WONT_LIKE_ME_WHEN_IM_HUNGRY;
    static Achievement* MINE;
    static Achievement* THE_END_AGAIN;
    static Achievement* YOU_NEED_AMINT;
    static Achievement* SUPER_SONIC;
    static Achievement* DRY_SPELL;
    static Achievement* FREE_DIVER;
    static Achievement* SUPER_FUEL;
    static Achievement* SADDLE_UP;
    static Achievement* TASTE_OF_YOUR_OWN_MEDICINE;
    static Achievement* BEAM_ME_UP;
    static Achievement* MAP_ROOM;
    static Achievement* CAMOUFLAGE;
    static Achievement* BACK_FROM_THE_DEAD;
    static Achievement* EQUIP_YOUR_FISTS;
    static Achievement* TENACIOUS_BALL;
    static Achievement* DEADSHOT;
    static Achievement* SUCK_MY_SNOWBALLS;
    static Achievement* MOUNTAIN_TOP;
    static Achievement* WILL_LIKE_NO_OTHER;
    static Achievement* THE_DEEP_END;
    static Achievement* GREAT_VIEW_FROM_UP_HERE;
    static Achievement* CHANGE_OF_SHEETS;
    static Achievement* CHEATING_DEATH;
    static Achievement* SO_IGOT_THAT_GOING_FOR_ME;
    static Achievement* LET_IT_GO;
    static Achievement* FEELING_ILL;
    static Achievement* RABBIT_SEASON;
    static Achievement* ORGANIZATIONAL_WIZARD;
    static Achievement* GLIDER;
    static Achievement* PILOT;
    static Achievement* GO_GREEN;
    static Achievement* GO_YELLOW;
    static Achievement* GO_BLUE;
    static Achievement* REPOPULATION_ALIAS;
    static Achievement* ADVENTURING_TIME_ALIAS;
};
