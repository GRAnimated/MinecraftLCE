#include "net/minecraft/client/renderer/texture/Textures.h"

// clang-format off
const wchar_t* Textures::_TEXTURE_PATHS[213] = {L"misc/grasscolor",L"misc/foliagecolor",L"%blur%misc/pumpkinblur",L"%clamp%misc/shadow",L"art/kz",L"environment/clouds",L"environment/rain",L"environment/snow",
L"gui/gui",L"gui/icons",L"item/arrows",L"item/cart",L"item/sign",L"misc/mapbg",L"misc/mapicons",L"misc/water",L"misc/footprint",L"mob/saddle",L"mob/sheep_fur",
L"mob/spider_eyes",L"particles",L"mob/chicken",L"mob/cow",L"mob/pig",L"mob/sheep",L"mob/squid",L"mob/wolf",L"mob/wolf_tame",L"mob/wolf_angry",L"mob/creeper",
L"mob/ghast",L"mob/ghast_fire",L"mob/zombie",L"mob/pigzombie",L"mob/skeleton",L"mob/slime",L"mob/spider",L"mob/steve",L"mob/char1",L"mob/char2",L"mob/char3",
L"mob/char4",L"mob/char5",L"mob/char6",L"mob/char7",L"terrain/moon",L"terrain/sun",L"armor/power",L"mob/cavespider",L"mob/enderman",L"mob/silverfish",
L"mob/enderman_eyes",L"misc/explosion",L"item/xporb",L"item/chest",L"item/largechest",L"item/enderchest",L"mob/redcow",L"mob/snowman",L"mob/enderdragon/ender",
L"mob/fire",L"mob/lava",L"mob/villager/villager",L"mob/villager/farmer",L"mob/villager/librarian",L"mob/villager/priest",L"mob/villager/smith",L"mob/villager/butcher",
L"mob/enderdragon/crystal",L"mob/enderdragon/shuffle",L"mob/enderdragon/beam",L"mob/enderdragon/ender_eyes",L"%blur%misc/glint",L"item/book",L"misc/tunnel",
L"misc/particlefield",L"terrain/moon_phases",L"mob/ozelot",L"mob/cat_black",L"mob/cat_red",L"mob/cat_siamese",L"mob/villager_golem",L"mob/skeleton_wither",
L"mob/wolf_collar",L"mob/zombie_villager/zombie_villager",L"item/lead_knot",L"misc/beacon_beam",L"mob/bat",L"mob/horse/donkey",L"mob/horse/horse_black",
L"mob/horse/horse_brown",L"mob/horse/horse_chestnut",L"mob/horse/horse_creamy",L"mob/horse/horse_darkbrown",L"mob/horse/horse_gray",L"mob/horse/horse_markings_blackdots",
L"mob/horse/horse_markings_white",L"mob/horse/horse_markings_whitedots",L"mob/horse/horse_markings_whitefield",L"mob/horse/horse_skeleton",L"mob/horse/horse_white",
L"mob/horse/horse_zombie",L"mob/horse/mule",L"mob/horse/armor/horse_armor_diamond",L"mob/horse/armor/horse_armor_gold",L"mob/horse/armor/horse_armor_iron",
L"mob/witch",L"mob/wither/wither",L"mob/wither/wither_armor",L"mob/wither/wither_invulnerable",L"item/trapped",L"item/trapped_double",L"mob/alex",L"mob/alex1",
L"mob/alex2",L"mob/alex3",L"mob/alex4",L"mob/alex5",L"mob/alex6",L"mob/alex7",L"misc/additionalmapicons",L"item/armorstand/wood",L"font/Default",L"font/alternate",
L"mob/endermite",L"mob/guardian",L"mob/guardian_elder",L"mob/guardian_beam",L"mob/rabbit/brown",L"mob/rabbit/white",L"mob/rabbit/black",L"mob/rabbit/gold",
L"mob/rabbit/salt",L"mob/rabbit/white_splotched",L"mob/rabbit/toast",L"mob/rabbit/caerbannog",L"textures/destroy_stage_0",L"textures/destroy_stage_1",
L"textures/destroy_stage_2",L"textures/destroy_stage_3",L"textures/destroy_stage_4",L"textures/destroy_stage_5",L"textures/destroy_stage_6",L"textures/destroy_stage_7",
L"textures/destroy_stage_8",L"textures/destroy_stage_9",L"item/banner/banner_base",L"item/banner/Banner_Atlas",L"mob/bear/polarbear",L"item/boat/boat_oak",
L"item/boat/boat_spruce",L"item/boat/boat_birch",L"item/boat/boat_jungle",L"item/boat/boat_acacia",L"item/boat/boat_darkoak",L"mob/skeleton/stray",L"mob/skeleton/stray_overlay",
L"mob/zombie_villager/zombie_farmer",L"mob/zombie_villager/zombie_librarian",L"mob/zombie_villager/zombie_priest",L"mob/zombie_villager/zombie_smith",
L"mob/zombie_villager/zombie_butcher",L"mob/zombie/husk",L"mob/enderdragon/dragon_fireball",L"mob/shulker/endergolem",L"mob/shulker/spark",L"item/spectral_arrow",
L"item/tipped_arrow",L"item/elytra",L"mob/DevSteve",L"mob/DevAlex",L"environment/Thermal_1",L"environment/Thermal_2",L"environment/BoostArrow",L"mob/Glide_Ghost",
L"mob/llama/decor/decor_white",L"mob/llama/decor/decor_orange",L"mob/llama/decor/decor_magenta",L"mob/llama/decor/decor_light_blue",L"mob/llama/decor/decor_yellow",
L"mob/llama/decor/decor_lime",L"mob/llama/decor/decor_pink",L"mob/llama/decor/decor_gray",L"mob/llama/decor/decor_silver",L"mob/llama/decor/decor_cyan",
L"mob/llama/decor/decor_purple",L"mob/llama/decor/decor_blue",L"mob/llama/decor/decor_brown",L"mob/llama/decor/decor_green",L"mob/llama/decor/decor_red",
L"mob/llama/decor/decor_black",L"mob/llama/llama_creamy",L"mob/llama/llama_white",L"mob/llama/llama_brown",L"mob/llama/llama_gray",L"mob/llama/spit",L"mob/illager/evoker",
L"mob/illager/fangs",L"mob/illager/vindicator",L"mob/illager/vex",L"mob/illager/vex_charging",L"mob/illager/illusionist",L"mob/parrot/parrot_red_blue",
L"mob/parrot/parrot_blue",L"mob/parrot/parrot_green",L"mob/parrot/parrot_yellow_blue",L"mob/parrot/parrot_grey",L"item/bed",L"item/firework",L"mob/horse/armor/horse_armor_leather_1",
L"mob/horse/armor/horse_armor_leather_1_b",L"gui/items",L"terrain"};
// clang-format on

int Textures::_TEXTURE_IDS[213];

void Textures::stitch() {
    this->atlas->stitch();
    this->atlas2->stitch();
}

void Textures::loadIndexedTextures() {
    for (int i = 0; i < 211; i++) {
        _TEXTURE_IDS[i] = this->loadTexture((_TEXTURE_NAME)i, _TEXTURE_PATHS[i]);
    }
}
