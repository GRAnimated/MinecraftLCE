#include "fui/FJ_Factory.h"
#include "fui/node/FJ_FuiNode.h"
#include "fui/node/component/FJ_ComponentChat.h"
#include "fui/node/component/FJ_ComponentLogo.h"
#include "fui/node/control/FJ_BitmapIcon.h"
#include "fui/node/control/FJ_CheckpointMarker.h"
#include "fui/node/control/FJ_Eula.h"
#include "fui/node/control/FJ_ExlamationMark.h"
#include "fui/node/control/FJ_ExperienceBar.h"
#include "fui/node/control/FJ_Gamertag.h"
#include "fui/node/control/FJ_HorseJumpBar.h"
#include "fui/node/control/FJ_HowToPlay.h"
#include "fui/node/control/FJ_IconSlot.h"
#include "fui/node/control/FJ_KillBar.h"
#include "fui/node/control/FJ_KillBarSmall.h"
#include "fui/node/control/FJ_MCBREUpSell.h"
#include "fui/node/control/FJ_MessageBox.h"
#include "fui/node/control/FJ_Panorama.h"
#include "fui/node/control/FJ_PressStartToPlay.h"
#include "fui/node/control/FJ_ProgressBar_Loading.h"
#include "fui/node/control/FJ_QuadrantSignin.h"
#include "fui/node/control/FJ_SaveMessage.h"
#include "fui/node/control/FJ_SignInput.h"
#include "fui/node/control/FJ_SocialPost.h"
#include "fui/node/control/FJ_SpaceIndicatorBar.h"
#include "fui/node/control/FJ_SuperFlatPresets.h"
#include "fui/node/control/FJ_TutorialPopup.h"
#include "fui/node/control/FJ_WiiUDRC.h"
#include "fui/node/control/attackindicator/FJ_AttackIndicatorCrosshair.h"
#include "fui/node/control/attackindicator/FJ_AttackIndicatorHotbar.h"
#include "fui/node/control/beacon/FJ_BeaconEffectButton_Normal.h"
#include "fui/node/control/beacon/FJ_BeaconEffectButton_Small.h"
#include "fui/node/control/brewing/FJ_BrewingArrow.h"
#include "fui/node/control/brewing/FJ_BrewingArrow_Small.h"
#include "fui/node/control/brewing/FJ_BrewingBubbles.h"
#include "fui/node/control/brewing/FJ_BrewingBubbles_Small.h"
#include "fui/node/control/brewing/FJ_BrewingPlate.h"
#include "fui/node/control/brewing/FJ_BrewingPlate_Small.h"
#include "fui/node/control/button/FJ_LayoutButton.h"
#include "fui/node/control/button/FJ_MenuButton_Normal.h"
#include "fui/node/control/button/FJ_UpsellButton_Normal.h"
#include "fui/node/control/button/small/FJ_LayoutButton_Small.h"
#include "fui/node/control/button/small/FJ_MenuButton_Small.h"
#include "fui/node/control/button/small/FJ_UpsellButton_Small.h"
#include "fui/node/control/checkbox/FJ_CheckBox_Normal.h"
#include "fui/node/control/checkbox/FJ_CheckBox_Small.h"
#include "fui/node/control/cursor/FJ_Cursor_Normal.h"
#include "fui/node/control/cursor/FJ_Cursor_Small.h"
#include "fui/node/control/debug/FJ_DebugBuildTools.h"
#include "fui/node/control/debug/FJ_DebugCreateSchematic.h"
#include "fui/node/control/debug/FJ_DebugFillArea.h"
#include "fui/node/control/debug/FJ_DebugMarketingGuide.h"
#include "fui/node/control/debug/FJ_DebugOptions.h"
#include "fui/node/control/debug/FJ_DebugPuppeteer.h"
#include "fui/node/control/debug/FJ_DebugSetCamera.h"
#include "fui/node/control/dragon/FJ_DragonHealth_01.h"
#include "fui/node/control/dragon/FJ_DragonHealth_02.h"
#include "fui/node/control/dragon/FJ_DragonHealth_03.h"
#include "fui/node/control/dragon/FJ_DragonHealth_04.h"
#include "fui/node/control/dragon/FJ_DragonHealth_05.h"
#include "fui/node/control/dragon/FJ_EndPoem.h"
#include "fui/node/control/enchanting/FJ_EnchantingButton_Normal.h"
#include "fui/node/control/enchanting/FJ_EnchantingButton_Small.h"
#include "fui/node/control/furnace/FJ_FurnaceArrow.h"
#include "fui/node/control/furnace/FJ_FurnaceArrow_Small.h"
#include "fui/node/control/furnace/FJ_FurnaceFlame.h"
#include "fui/node/control/furnace/FJ_FurnaceFlame_Small.h"
#include "fui/node/control/gamemode/FJ_GameModeScoreboard.h"
#include "fui/node/control/gamemode/FJ_GameModeSelection.h"
#include "fui/node/control/htmltext/FJ_HtmlTextPanel.h"
#include "fui/node/control/htmltext/FJ_HtmlTextPanelLarge.h"
#include "fui/node/control/htmltext/FJ_HtmlText_Normal.h"
#include "fui/node/control/htmltext/FJ_HtmlText_Small.h"
#include "fui/node/control/htmltext/FJ_HtmlText_WhiteNormal.h"
#include "fui/node/control/htmltext/FJ_HtmlText_WhiteSmall.h"
#include "fui/node/control/htmltext/FJ_HtmlText_WithPanel_Normal.h"
#include "fui/node/control/htmltext/FJ_HtmlText_WithPanel_Small.h"
#include "fui/node/control/htmltext/dynamic/FJ_DynamicHtmlText.h"
#include "fui/node/control/htmltext/dynamic/FJ_DynamicHtmlText_Normal.h"
#include "fui/node/control/htmltext/dynamic/FJ_DynamicHtmlText_Small.h"
#include "fui/node/control/htmltext/dynamic/FJ_DynamicHtmlText_WithPanel_Normal.h"
#include "fui/node/control/htmltext/dynamic/FJ_DynamicHtmlText_WithPanel_Small.h"
#include "fui/node/control/keyboard/FJ_KeyboardButtons_Controls_Normal.h"
#include "fui/node/control/keyboard/FJ_KeyboardButtons_Controls_Small.h"
#include "fui/node/control/keyboard/FJ_KeyboardButtons_Keys_Normal.h"
#include "fui/node/control/keyboard/FJ_KeyboardButtons_Keys_Small.h"
#include "fui/node/control/label/FJ_Label.h"
#include "fui/node/control/label/FJ_Label_BigBlack.h"
#include "fui/node/control/label/FJ_Label_BigGrey.h"
#include "fui/node/control/label/FJ_Label_BigWhite.h"
#include "fui/node/control/label/FJ_Label_Black.h"
#include "fui/node/control/label/FJ_Label_Black_Centered.h"
#include "fui/node/control/label/FJ_Label_Black_Centered_HUD.h"
#include "fui/node/control/label/FJ_Label_Black_Small_Centered.h"
#include "fui/node/control/label/FJ_Label_Black_Small_Centered_HUD.h"
#include "fui/node/control/label/FJ_Label_Black_VerySmall_Centered.h"
#include "fui/node/control/label/FJ_Label_Blink_Normal.h"
#include "fui/node/control/label/FJ_Label_Blink_Small.h"
#include "fui/node/control/label/FJ_Label_Book_Normal.h"
#include "fui/node/control/label/FJ_Label_Book_Small.h"
#include "fui/node/control/label/FJ_Label_Book_VerySmall.h"
#include "fui/node/control/label/FJ_Label_Credits_10.h"
#include "fui/node/control/label/FJ_Label_Credits_10_Yellow.h"
#include "fui/node/control/label/FJ_Label_Credits_20.h"
#include "fui/node/control/label/FJ_Label_Credits_20_Yellow.h"
#include "fui/node/control/label/FJ_Label_Credits_30.h"
#include "fui/node/control/label/FJ_Label_DragonHealth.h"
#include "fui/node/control/label/FJ_Label_DragonHealthBig.h"
#include "fui/node/control/label/FJ_Label_DragonHealthSmall.h"
#include "fui/node/control/label/FJ_Label_DragonHealthVerySmall.h"
#include "fui/node/control/label/FJ_Label_Green.h"
#include "fui/node/control/label/FJ_Label_Grey.h"
#include "fui/node/control/label/FJ_Label_HUD_BigWhite.h"
#include "fui/node/control/label/FJ_Label_HUD_Level_01.h"
#include "fui/node/control/label/FJ_Label_HUD_Level_02.h"
#include "fui/node/control/label/FJ_Label_HUD_Level_03.h"
#include "fui/node/control/label/FJ_Label_HUD_Level_04.h"
#include "fui/node/control/label/FJ_Label_HUD_Level_05.h"
#include "fui/node/control/label/FJ_Label_HUD_SmallWhite.h"
#include "fui/node/control/label/FJ_Label_HUD_Splash.h"
#include "fui/node/control/label/FJ_Label_HUD_SplashBig.h"
#include "fui/node/control/label/FJ_Label_HUD_SplashVita.h"
#include "fui/node/control/label/FJ_Label_HUD_VerySmallWhite.h"
#include "fui/node/control/label/FJ_Label_HUD_White.h"
#include "fui/node/control/label/FJ_Label_Html.h"
#include "fui/node/control/label/FJ_Label_HtmlEndPoem.h"
#include "fui/node/control/label/FJ_Label_HtmlEndPoemHD.h"
#include "fui/node/control/label/FJ_Label_HtmlSmall.h"
#include "fui/node/control/label/FJ_Label_OutlineLevel.h"
#include "fui/node/control/label/FJ_Label_OutlineLevel_Small.h"
#include "fui/node/control/label/FJ_Label_OutlineTitle.h"
#include "fui/node/control/label/FJ_Label_OutlineTitle_Small.h"
#include "fui/node/control/label/FJ_Label_Red.h"
#include "fui/node/control/label/FJ_Label_SkinSelect.h"
#include "fui/node/control/label/FJ_Label_SkinSelectCenter.h"
#include "fui/node/control/label/FJ_Label_SkinSelectCenter_Off.h"
#include "fui/node/control/label/FJ_Label_SkinSelectCenter_Small.h"
#include "fui/node/control/label/FJ_Label_SkinSelectCenter_Small_Off.h"
#include "fui/node/control/label/FJ_Label_SkinSelect_Off.h"
#include "fui/node/control/label/FJ_Label_SkinSelect_Small.h"
#include "fui/node/control/label/FJ_Label_SkinSelect_Small_Off.h"
#include "fui/node/control/label/FJ_Label_SmallBlack.h"
#include "fui/node/control/label/FJ_Label_SmallGreen.h"
#include "fui/node/control/label/FJ_Label_SmallGrey.h"
#include "fui/node/control/label/FJ_Label_SmallRed.h"
#include "fui/node/control/label/FJ_Label_SmallWhite.h"
#include "fui/node/control/label/FJ_Label_VerySmallBlack.h"
#include "fui/node/control/label/FJ_Label_VerySmallGrey.h"
#include "fui/node/control/label/FJ_Label_VerySmallWhite.h"
#include "fui/node/control/label/FJ_Label_White.h"
#include "fui/node/control/label/FJ_Label_WhiteHtml.h"
#include "fui/node/control/label/FJ_Label_WhiteHtmlSmall.h"
#include "fui/node/control/label/FJ_Label_White_Centered.h"
#include "fui/node/control/label/FJ_Label_White_Small_Centered.h"
#include "fui/node/control/label/FJ_Label_White_VerySmall_Centered.h"
#include "fui/node/control/leaderboard/FJ_LeaderboardEntryNormal.h"
#include "fui/node/control/leaderboard/FJ_LeaderboardEntrySmall.h"
#include "fui/node/control/leaderboard/FJ_LeaderboardHeaderNormal.h"
#include "fui/node/control/leaderboard/FJ_LeaderboardHeaderSmall.h"
#include "fui/node/control/leaderboard/FJ_LeaderboardList.h"
#include "fui/node/control/list/FJ_JoinGameFilterList.h"
#include "fui/node/control/list/FJ_List_MultiList.h"
#include "fui/node/control/list/FJ_SlotList.h"
#include "fui/node/control/list/FJ_SlotList_Slot.h"
#include "fui/node/control/list/FJ_TexturePackList.h"
#include "fui/node/control/list/FJ_TexturePackList_Slot.h"
#include "fui/node/control/list/button/FJ_ListButtonAchievement_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonAchievement_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonCheckbox_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonCheckbox_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonController_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonController_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonDLC_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonDLC_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonIconLeft_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonIconLeft_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonIconX2Left_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonIconX2Left_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonLayerIcon_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonLayerIcon_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonLobby_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonLobby_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonPlayerList_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonPlayerList_Small.h"
#include "fui/node/control/list/button/FJ_ListButtonScoreBoard_Normal.h"
#include "fui/node/control/list/button/FJ_ListButtonScoreBoard_Small.h"
#include "fui/node/control/list/button/FJ_ListButton_Medium.h"
#include "fui/node/control/list/button/FJ_ListButton_Normal.h"
#include "fui/node/control/list/button/FJ_ListButton_Small.h"
#include "fui/node/control/list/button/FJ_List_ListButtonAchievement.h"
#include "fui/node/control/list/button/FJ_List_ListButtonCheckbox.h"
#include "fui/node/control/list/button/FJ_List_ListButtonDLC.h"
#include "fui/node/control/list/button/FJ_List_ListButtonIconLeft.h"
#include "fui/node/control/list/button/FJ_List_ListButtonLayerIcon.h"
#include "fui/node/control/list/button/FJ_List_ListButtonLobby.h"
#include "fui/node/control/list/button/FJ_List_ListButtonScoreBoard.h"
#include "fui/node/control/list/label/FJ_ListLabel_Black.h"
#include "fui/node/control/list/label/FJ_ListLabel_SmallBlack.h"
#include "fui/node/control/mobeffect/FJ_MobEffect_Normal.h"
#include "fui/node/control/mobeffect/FJ_MobEffect_Small.h"
#include "fui/node/control/panel/FJ_Panel9GridFade.h"
#include "fui/node/control/panel/FJ_PanelRecessFade.h"
#include "fui/node/control/panel/FJ_panel9Grid_16Fade.h"
#include "fui/node/control/scroll/FJ_ScrollArrow.h"
#include "fui/node/control/scroll/FJ_ScrollArrowH.h"
#include "fui/node/control/slider/FJ_Slider_Normal.h"
#include "fui/node/control/slider/FJ_Slider_Small.h"
#include "fui/node/control/textinput/FJ_TextInput.h"
#include "fui/node/control/textinput/FJ_TextInput_Normal.h"
#include "fui/node/control/textinput/FJ_TextInput_Small.h"
#include "fui/node/control/textinput/FJ_TextInput_Vita.h"
#include "fui/node/control/tooltip/FJ_ToolTip_Normal.h"
#include "fui/node/control/tooltip/FJ_ToolTip_Small.h"
#include "fui/node/control/tooltip/FJ_ToolTips.h"
#include "fui/node/control/touch/FJ_TouchControl.h"
#include "fui/node/control/touch/FJ_TouchControlFrontend.h"
#include "fui/node/menu/FJ_AchievementsMenu.h"
#include "fui/node/menu/FJ_AnvilMenu.h"
#include "fui/node/menu/FJ_AvatarSelectMenu.h"
#include "fui/node/menu/FJ_BeaconMenu.h"
#include "fui/node/menu/FJ_BiomeSelectMenu.h"
#include "fui/node/menu/FJ_BookAndQuillMenu.h"
#include "fui/node/menu/FJ_BrewingStandMenu.h"
#include "fui/node/menu/FJ_ChestMenu.h"
#include "fui/node/menu/FJ_ClassicCraftingMenu.h"
#include "fui/node/menu/FJ_ControlsMenu.h"
#include "fui/node/menu/FJ_CraftingMenu.h"
#include "fui/node/menu/FJ_CreateWorldMenu.h"
#include "fui/node/menu/FJ_CreativeMenu.h"
#include "fui/node/menu/FJ_CreditsMenu.h"
#include "fui/node/menu/FJ_DLCMainMenu.h"
#include "fui/node/menu/FJ_DLCOffersMenu.h"
#include "fui/node/menu/FJ_DeathMenu.h"
#include "fui/node/menu/FJ_DebugMenu.h"
#include "fui/node/menu/FJ_DispenserMenu.h"
#include "fui/node/menu/FJ_EnchantingMenu.h"
#include "fui/node/menu/FJ_FullScreenProgress.h"
#include "fui/node/menu/FJ_FurnaceMenu.h"
#include "fui/node/menu/FJ_HelpAndOptionsMenu.h"
#include "fui/node/menu/FJ_HopperMenu.h"
#include "fui/node/menu/FJ_HorseInventoryMenu.h"
#include "fui/node/menu/FJ_HowToPlayMenu.h"
#include "fui/node/menu/FJ_Intro.h"
#include "fui/node/menu/FJ_InventoryMenu.h"
#include "fui/node/menu/FJ_JoinMenu.h"
#include "fui/node/menu/FJ_LaunchMoreOptionsMenu.h"
#include "fui/node/menu/FJ_LeaderboardMenu.h"
#include "fui/node/menu/FJ_LoadCreateJoinMenu.h"
#include "fui/node/menu/FJ_LoadMenu.h"
#include "fui/node/menu/FJ_LoadOrJoinMenu.h"
#include "fui/node/menu/FJ_MainMenu.h"
#include "fui/node/menu/FJ_MapSelectMenu.h"
#include "fui/node/menu/FJ_MultilistMenu.h"
#include "fui/node/menu/FJ_PauseMenu.h"
#include "fui/node/menu/FJ_SaveMenu.h"
#include "fui/node/menu/FJ_SettingsAudioMenu.h"
#include "fui/node/menu/FJ_SettingsControlMenu.h"
#include "fui/node/menu/FJ_SettingsGraphicsMenu.h"
#include "fui/node/menu/FJ_SettingsMenu.h"
#include "fui/node/menu/FJ_SettingsOptionsMenu.h"
#include "fui/node/menu/FJ_SettingsUIMenu.h"
#include "fui/node/menu/FJ_SignEntryMenu.h"
#include "fui/node/menu/FJ_SkinSelect.h"
#include "fui/node/menu/FJ_SuperFlatEditLayerMenu.h"
#include "fui/node/menu/FJ_SuperFlatMenu.h"
#include "fui/node/menu/FJ_TradingMenu.h"
#include "fui/node/menu/ingame/FJ_Hud.h"
#include "fui/node/menu/ingame/FJ_InGameHostOptions.h"
#include "fui/node/menu/ingame/FJ_InGameInfoMenu.h"
#include "fui/node/menu/ingame/FJ_InGamePlayerOptions.h"
#include "fui/node/menu/ingame/FJ_InGameTeleportMenu.h"
#include "node/control/list/button/FJ_List_ListButton.h"
#include "node/control/list/button/FJ_List_ListButtonPlayerList.h"
#include "node/control/list/button/FJ_List_MenuButton.h"

void FJ_Factory::initialise() {
    ADD_NODE(FJ_FuiNode);
    ADD_NODE(FJ_MenuButton_Normal);
    ADD_NODE(FJ_MenuButton_Small);
    ADD_NODE(FJ_ListButton_Medium);
    ADD_NODE(FJ_ListButton_Normal);
    ADD_NODE(FJ_ListButton_Small);
    ADD_NODE(FJ_UpsellButton_Normal);
    ADD_NODE(FJ_UpsellButton_Small);
    ADD_NODE(FJ_ListButtonIconLeft_Normal);
    ADD_NODE(FJ_ListButtonIconLeft_Small);
    ADD_NODE(FJ_ListButtonIconX2Left_Normal);
    ADD_NODE(FJ_ListButtonIconX2Left_Small);
    ADD_NODE(FJ_List_ListButtonIconLeft);
    ADD_NODE(FJ_List_ListButton);
    ADD_NODE(FJ_List_ListButtonCheckbox);
    ADD_NODE(FJ_List_ListButtonDLC);
    ADD_NODE(FJ_List_ListButtonLayerIcon);
    ADD_NODE(FJ_List_ListButtonLobby);
    ADD_NODE(FJ_List_ListButtonPlayerList);
    ADD_NODE(FJ_List_ListButtonScoreBoard);
    ADD_NODE(FJ_List_ListButtonAchievement);
    ADD_NODE(FJ_CheckpointMarker);
    ADD_NODE(FJ_List_MenuButton);
    ADD_NODE(FJ_BeaconEffectButton_Normal);
    ADD_NODE(FJ_BeaconEffectButton_Small);
    ADD_NODE(FJ_EnchantingButton_Normal);
    ADD_NODE(FJ_EnchantingButton_Small);
    ADD_NODE(FJ_KeyboardButtons_Controls_Normal);
    ADD_NODE(FJ_KeyboardButtons_Controls_Small);
    ADD_NODE(FJ_KeyboardButtons_Keys_Normal);
    ADD_NODE(FJ_KeyboardButtons_Keys_Small);
    ADD_NODE(FJ_KeyboardButtons_Controls_Normal);
    ADD_NODE(FJ_LayoutButton);
    ADD_NODE(FJ_LayoutButton_Small);
    ADD_NODE(FJ_ListButtonAchievement_Normal);
    ADD_NODE(FJ_ListButtonAchievement_Small);
    ADD_NODE(FJ_ListButtonCheckbox_Normal);
    ADD_NODE(FJ_ListButtonCheckbox_Small);
    ADD_NODE(FJ_ListButtonDLC_Normal);
    ADD_NODE(FJ_ListButtonDLC_Small);
    ADD_NODE(FJ_ListButtonLayerIcon_Normal);
    ADD_NODE(FJ_ListButtonLayerIcon_Small);
    ADD_NODE(FJ_ListButtonLobby_Normal);
    ADD_NODE(FJ_ListButtonLobby_Small);
    ADD_NODE(FJ_ListButtonPlayerList_Normal);
    ADD_NODE(FJ_ListButtonPlayerList_Small);
    ADD_NODE(FJ_ListButtonScoreBoard_Normal);
    ADD_NODE(FJ_ListButtonScoreBoard_Small);
    ADD_NODE(FJ_ListButtonController_Normal);
    ADD_NODE(FJ_ListButtonController_Small);
    ADD_NODE(FJ_LeaderboardList);
    ADD_NODE(FJ_LeaderboardEntryNormal);
    ADD_NODE(FJ_LeaderboardEntrySmall);
    ADD_NODE(FJ_LeaderboardHeaderNormal);
    ADD_NODE(FJ_LeaderboardHeaderSmall);
    ADD_NODE(FJ_LeaderboardList);
    ADD_NODE(FJ_IconSlot);
    ADD_NODE(FJ_ToolTip_Normal);
    ADD_NODE(FJ_ToolTip_Small);
    ADD_NODE(FJ_Label);
    ADD_NODE(FJ_Label_Blink_Normal);
    ADD_NODE(FJ_Label_Blink_Small);
    ADD_NODE(FJ_ScrollArrow);
    ADD_NODE(FJ_ScrollArrowH);
    ADD_NODE(FJ_Slider_Normal);
    ADD_NODE(FJ_Slider_Small);
    ADD_NODE(FJ_TexturePackList);
    ADD_NODE(FJ_TexturePackList_Slot);
    ADD_NODE(FJ_SlotList);
    ADD_NODE(FJ_SlotList_Slot);
    ADD_NODE(FJ_CheckBox_Normal);
    ADD_NODE(FJ_CheckBox_Small);
    ADD_NODE(FJ_SlotList);
    ADD_NODE(FJ_SlotList_Slot);
    ADD_NODE(FJ_ExlamationMark);
    ADD_NODE(FJ_Cursor_Normal);
    ADD_NODE(FJ_Cursor_Small);
    ADD_NODE(FJ_MobEffect_Small);
    ADD_NODE(FJ_MobEffect_Normal);
    ADD_NODE(FJ_TouchControl);
    ADD_NODE(FJ_TouchControlFrontend);
    ADD_NODE(FJ_BitmapIcon);
    ADD_NODE(FJ_List_MultiList);
    ADD_NODE(FJ_CreditsMenu);
    ADD_NODE(FJ_EndPoem);
    ADD_NODE(FJ_MainMenu);
    ADD_NODE(FJ_LoadMenu);
    ADD_NODE(FJ_SaveMessage);
    ADD_NODE(FJ_ComponentLogo);
    ADD_NODE(FJ_Panorama);
    ADD_NODE(FJ_ToolTips);
    ADD_NODE(FJ_Intro);
    ADD_NODE(FJ_LoadCreateJoinMenu);
    ADD_NODE(FJ_Hud);
    ADD_NODE(FJ_HowToPlayMenu);
    ADD_NODE(FJ_HowToPlay);
    ADD_NODE(FJ_CreativeMenu);
    ADD_NODE(FJ_CraftingMenu);
    ADD_NODE(FJ_InventoryMenu);
    ADD_NODE(FJ_FullScreenProgress);
    ADD_NODE(FJ_Eula);
    ADD_NODE(FJ_MessageBox);
    ADD_NODE(FJ_PauseMenu);
    ADD_NODE(FJ_HelpAndOptionsMenu);
    ADD_NODE(FJ_SettingsMenu);
    ADD_NODE(FJ_MCBREUpSell);
    ADD_NODE(FJ_AnvilMenu);
    ADD_NODE(FJ_BeaconMenu);
    ADD_NODE(FJ_BrewingStandMenu);
    ADD_NODE(FJ_ClassicCraftingMenu);
    ADD_NODE(FJ_ChestMenu);
    ADD_NODE(FJ_DispenserMenu);
    ADD_NODE(FJ_EnchantingMenu);
    ADD_NODE(FJ_FurnaceMenu);
    ADD_NODE(FJ_HopperMenu);
    ADD_NODE(FJ_HorseInventoryMenu);
    ADD_NODE(FJ_BookAndQuillMenu);
    ADD_NODE(FJ_ControlsMenu);
    ADD_NODE(FJ_PressStartToPlay);
    ADD_NODE(FJ_SuperFlatMenu);
    ADD_NODE(FJ_SuperFlatPresets);
    ADD_NODE(FJ_SuperFlatEditLayerMenu);
    ADD_NODE(FJ_QuadrantSignin);
    ADD_NODE(FJ_LeaderboardMenu);
    ADD_NODE(FJ_TradingMenu);
    ADD_NODE(FJ_GameModeScoreboard);
    ADD_NODE(FJ_BiomeSelectMenu);
    ADD_NODE(FJ_ComponentChat);
    ADD_NODE(FJ_DeathMenu);
    ADD_NODE(FJ_DebugBuildTools);
    ADD_NODE(FJ_DebugCreateSchematic);
    ADD_NODE(FJ_DebugFillArea);
    ADD_NODE(FJ_DebugMarketingGuide);
    ADD_NODE(FJ_DebugMenu);
    ADD_NODE(FJ_DebugOptions);
    ADD_NODE(FJ_DebugPuppeteer);
    ADD_NODE(FJ_DebugSetCamera);
    ADD_NODE(FJ_DLCMainMenu);
    ADD_NODE(FJ_DLCOffersMenu);
    ADD_NODE(FJ_GameModeSelection);
    ADD_NODE(FJ_Gamertag);
    ADD_NODE(FJ_JoinGameFilterList);
    ADD_NODE(FJ_JoinMenu);
    ADD_NODE(FJ_LoadOrJoinMenu);
    ADD_NODE(FJ_SaveMenu);
    ADD_NODE(FJ_SettingsAudioMenu);
    ADD_NODE(FJ_SettingsControlMenu);
    ADD_NODE(FJ_SettingsGraphicsMenu);
    ADD_NODE(FJ_SettingsOptionsMenu);
    ADD_NODE(FJ_SettingsUIMenu);
    ADD_NODE(FJ_SignEntryMenu);
    ADD_NODE(FJ_SocialPost);
    ADD_NODE(FJ_WiiUDRC);
    ADD_NODE(FJ_AchievementsMenu);
    ADD_NODE(FJ_AvatarSelectMenu);
    ADD_NODE(FJ_CreateWorldMenu);
    ADD_NODE(FJ_LaunchMoreOptionsMenu);
    ADD_NODE(FJ_TutorialPopup);
    ADD_NODE(FJ_MultilistMenu);
    ADD_NODE(FJ_SkinSelect);
    ADD_NODE(FJ_InGamePlayerOptions);
    ADD_NODE(FJ_InGameHostOptions);
    ADD_NODE(FJ_InGameInfoMenu);
    ADD_NODE(FJ_InGameTeleportMenu);
    ADD_NODE(FJ_MapSelectMenu);
    ADD_NODE(FJ_DragonHealth_01);
    ADD_NODE(FJ_DragonHealth_02);
    ADD_NODE(FJ_DragonHealth_03);
    ADD_NODE(FJ_DragonHealth_04);
    ADD_NODE(FJ_DragonHealth_05);
    ADD_NODE(FJ_HorseJumpBar);
    ADD_NODE(FJ_ExperienceBar);
    ADD_NODE(FJ_BrewingArrow);
    ADD_NODE(FJ_BrewingArrow_Small);
    ADD_NODE(FJ_BrewingBubbles);
    ADD_NODE(FJ_BrewingBubbles_Small);
    ADD_NODE(FJ_BrewingPlate);
    ADD_NODE(FJ_BrewingPlate_Small);
    ADD_NODE(FJ_FurnaceArrow);
    ADD_NODE(FJ_FurnaceArrow_Small);
    ADD_NODE(FJ_FurnaceFlame);
    ADD_NODE(FJ_FurnaceFlame_Small);
    ADD_NODE(FJ_KillBar);
    ADD_NODE(FJ_KillBarSmall);
    ADD_NODE(FJ_ProgressBar_Loading);
    ADD_NODE(FJ_AttackIndicatorCrosshair);
    ADD_NODE(FJ_AttackIndicatorHotbar);
    ADD_NODE(FJ_SpaceIndicatorBar);
    ADD_NODE(FJ_TextInput);
    ADD_NODE(FJ_TextInput_Small);
    ADD_NODE(FJ_TextInput_Normal);
    ADD_NODE(FJ_TextInput_Vita);
    ADD_NODE(FJ_HtmlTextPanel);
    ADD_NODE(FJ_HtmlTextPanelLarge);
    ADD_NODE(FJ_Label_BigBlack);
    ADD_NODE(FJ_Label_BigGrey);
    ADD_NODE(FJ_Label_BigWhite);
    ADD_NODE(FJ_Label_Black);
    ADD_NODE(FJ_Label_Black_Centered);
    ADD_NODE(FJ_Label_Black_Centered_HUD);
    ADD_NODE(FJ_Label_Black_Small_Centered);
    ADD_NODE(FJ_Label_Black_Small_Centered_HUD);
    ADD_NODE(FJ_Label_Black_VerySmall_Centered);
    ADD_NODE(FJ_Label_Blink_Normal);
    ADD_NODE(FJ_Label_Blink_Small);
    ADD_NODE(FJ_Label_Book_Normal);
    ADD_NODE(FJ_Label_Book_Small);
    ADD_NODE(FJ_Label_Book_VerySmall);
    ADD_NODE(FJ_Label_Credits_10);
    ADD_NODE(FJ_Label_Credits_10_Yellow);
    ADD_NODE(FJ_Label_Credits_20);
    ADD_NODE(FJ_Label_Credits_20_Yellow);
    ADD_NODE(FJ_Label_Credits_30);
    ADD_NODE(FJ_Label_DragonHealth);
    ADD_NODE(FJ_Label_DragonHealthBig);
    ADD_NODE(FJ_Label_DragonHealthSmall);
    ADD_NODE(FJ_Label_DragonHealthVerySmall);
    ADD_NODE(FJ_Label_Green);
    ADD_NODE(FJ_Label_Grey);
    ADD_NODE(FJ_Label_Html);
    ADD_NODE(FJ_Label_HtmlEndPoem);
    ADD_NODE(FJ_Label_HtmlEndPoemHD);
    ADD_NODE(FJ_Label_HtmlSmall);
    ADD_NODE(FJ_Label_HUD_Level_01);
    ADD_NODE(FJ_Label_HUD_Level_02);
    ADD_NODE(FJ_Label_HUD_Level_03);
    ADD_NODE(FJ_Label_HUD_Level_04);
    ADD_NODE(FJ_Label_HUD_Level_05);
    ADD_NODE(FJ_Label_HUD_SmallWhite);
    ADD_NODE(FJ_Label_HUD_BigWhite);
    ADD_NODE(FJ_Label_HUD_Splash);
    ADD_NODE(FJ_Label_HUD_SplashBig);
    ADD_NODE(FJ_Label_HUD_SplashVita);
    ADD_NODE(FJ_Label_HUD_VerySmallWhite);
    ADD_NODE(FJ_Label_HUD_White);
    ADD_NODE(FJ_Label_OutlineLevel);
    ADD_NODE(FJ_Label_OutlineLevel_Small);
    ADD_NODE(FJ_Label_OutlineTitle);
    ADD_NODE(FJ_Label_OutlineTitle_Small);
    ADD_NODE(FJ_Label_Red);
    ADD_NODE(FJ_Label_SkinSelect);
    ADD_NODE(FJ_Label_SkinSelectCenter);
    ADD_NODE(FJ_Label_SkinSelectCenter_Off);
    ADD_NODE(FJ_Label_SkinSelectCenter_Small);
    ADD_NODE(FJ_Label_SkinSelectCenter_Small_Off);
    ADD_NODE(FJ_Label_SkinSelect_Off);
    ADD_NODE(FJ_Label_SkinSelect_Small);
    ADD_NODE(FJ_Label_SkinSelect_Small_Off);
    ADD_NODE(FJ_Label_SmallBlack);
    ADD_NODE(FJ_Label_SmallGreen);
    ADD_NODE(FJ_Label_SmallGrey);
    ADD_NODE(FJ_Label_SmallRed);
    ADD_NODE(FJ_Label_SmallWhite);
    ADD_NODE(FJ_Label_VerySmallBlack);
    ADD_NODE(FJ_Label_VerySmallGrey);
    ADD_NODE(FJ_Label_VerySmallWhite);
    ADD_NODE(FJ_Label_White);
    ADD_NODE(FJ_Label_WhiteHtml);
    ADD_NODE(FJ_Label_WhiteHtmlSmall);
    ADD_NODE(FJ_Label_White_Centered);
    ADD_NODE(FJ_Label_White_Small_Centered);
    ADD_NODE(FJ_Label_White_VerySmall_Centered);
    ADD_NODE(FJ_ListLabel_Black);
    ADD_NODE(FJ_ListLabel_SmallBlack);
    ADD_NODE(FJ_HtmlText_Normal);
    ADD_NODE(FJ_HtmlText_Small);
    ADD_NODE(FJ_HtmlText_WhiteNormal);
    ADD_NODE(FJ_HtmlText_WhiteSmall);
    ADD_NODE(FJ_HtmlText_WithPanel_Normal);
    ADD_NODE(FJ_HtmlText_WithPanel_Small);
    ADD_NODE(FJ_DynamicHtmlText);
    ADD_NODE(FJ_DynamicHtmlText_Normal);
    ADD_NODE(FJ_DynamicHtmlText_Small);
    ADD_NODE(FJ_DynamicHtmlText_WithPanel_Normal);
    ADD_NODE(FJ_DynamicHtmlText_WithPanel_Small);
    ADD_NODE(FJ_SignInput);
    ADD_NODE(FJ_panel9Grid_16Fade);
    ADD_NODE(FJ_Panel9GridFade);
    ADD_NODE(FJ_PanelRecessFade);
}
