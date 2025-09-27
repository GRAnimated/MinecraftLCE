#include "Awards.h"
#include "net/minecraft/core/profile/CProfile.h"

void RegisterAwardsWithProfileManager() {
    CProfile* instance = CProfile::sInstance;
    instance->SetRichPresenceGetStringCallback(GetRichPresenceStringFromId);

    for (int i = 0; i < 87; ++i) {
        const AwardInfo* info = UIScene_AchievementsMenu::GetInfo(Awards::sAchievementSlots[i]);
        instance->RegisterAward(info->mIdx, info->mIdx2, _0, info->mName, info->mDesc);
    }

    instance->RichPresenceInit(-1, -1);
    instance->SetRichPresenceGetStringCallback(GetRichPresenceStringFromId);
    instance->RichPresenceRegisterContext(0,           StringIDs::GameState);
    instance->RichPresenceRegisterPresenceString(0,    StringIDs::Idle);
    instance->RichPresenceRegisterPresenceString(1,    StringIDs::InMenus);
    instance->RichPresenceRegisterPresenceString(2,    StringIDs::PlayingMultiplayerGameState);
    instance->RichPresenceRegisterPresenceString(3,    StringIDs::OfflineMultiplayerGameState);
    instance->RichPresenceRegisterPresenceString(4,    StringIDs::PlayingAloneGameState);
    instance->RichPresenceRegisterPresenceString(5,    StringIDs::OfflineAloneGameState);
    instance->RichPresenceRegisterContextString(0, 0,  StringIDs::EnjoyingView);
    instance->RichPresenceRegisterContextString(0, 1,  StringIDs::RidingAPig);
    instance->RichPresenceRegisterContextString(0, 2,  StringIDs::RidingAMinecart);
    instance->RichPresenceRegisterContextString(0, 3,  StringIDs::InABoat);
    instance->RichPresenceRegisterContextString(0, 4,  StringIDs::Fishing);
    instance->RichPresenceRegisterContextString(0, 5,  StringIDs::Crafting_2);
    instance->RichPresenceRegisterContextString(0, 6,  StringIDs::Forging);
    instance->RichPresenceRegisterContextString(0, 7,  StringIDs::IntoNether);
    instance->RichPresenceRegisterContextString(0, 8,  StringIDs::ListeningToADisc);
    instance->RichPresenceRegisterContextString(0, 9,  StringIDs::LookingAtAMap);
    instance->RichPresenceRegisterContextString(0, 10, StringIDs::Enchanting);
    instance->RichPresenceRegisterContextString(0, 11, StringIDs::BrewingAPotion);
    instance->RichPresenceRegisterContextString(0, 12, StringIDs::WorkingAtAnvil);
    instance->RichPresenceRegisterContextString(0, 13, StringIDs::MeetingNeighbours);
}
