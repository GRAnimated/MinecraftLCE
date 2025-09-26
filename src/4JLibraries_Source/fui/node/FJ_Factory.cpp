#include "fui/node/FJ_AchievementsMenu.h"
#include "fui/node/FJ_AnvilMenu.h"
#include "fui/node/FJ_AttackIndicatorCrosshair.h"
#include "fui/node/FJ_AttackIndicatorHotbar.h"
#include "fui/node/FJ_AvatarSelectMenu.h"
#include "fui/node/FJ_BeaconEffectButton_Normal.h"
#include "fui/node/FJ_BeaconEffectButton_Small.h"
#include "fui/node/FJ_BeaconMenu.h"
#include "fui/node/FJ_BiomeSelectMenu.h"
#include "fui/node/FJ_BitmapIcon.h"
#include "fui/node/FJ_BookAndQuillMenu.h"
#include "fui/node/FJ_BrewingArrow.h"
#include "fui/node/FJ_BrewingArrow_Small.h"
#include "fui/node/FJ_BrewingBubbles.h"
#include "fui/node/FJ_BrewingBubbles_Small.h"
#include "fui/node/FJ_BrewingPlate.h"
#include "fui/node/FJ_BrewingPlate_Small.h"
#include "fui/node/FJ_BrewingStandMenu.h"
#include "fui/node/FJ_CheckBox_Normal.h"
#include "fui/node/FJ_CheckBox_Small.h"
#include "fui/node/FJ_CheckpointMarker.h"
#include "fui/node/FJ_ChestMenu.h"
#include "fui/node/FJ_ClassicCraftingMenu.h"
#include "fui/node/FJ_ComponentChat.h"
#include "fui/node/FJ_ComponentLogo.h"
#include "fui/node/FJ_ControlsMenu.h"
#include "fui/node/FJ_CraftingMenu.h"
#include "fui/node/FJ_CreateWorldMenu.h"
#include "fui/node/FJ_CreativeMenu.h"
#include "fui/node/FJ_CreditsMenu.h"
#include "fui/node/FJ_Cursor_Normal.h"
#include "fui/node/FJ_Cursor_Small.h"
#include "fui/node/FJ_DLCMainMenu.h"
#include "fui/node/FJ_DLCOffersMenu.h"
#include "fui/node/FJ_DeathMenu.h"
#include "fui/node/FJ_DebugBuildTools.h"
#include "fui/node/FJ_DebugCreateSchematic.h"
#include "fui/node/FJ_DebugFillArea.h"
#include "fui/node/FJ_DebugMarketingGuide.h"
#include "fui/node/FJ_DebugMenu.h"
#include "fui/node/FJ_DebugOptions.h"
#include "fui/node/FJ_DebugPuppeteer.h"
#include "fui/node/FJ_DebugSetCamera.h"
#include "fui/node/FJ_DispenserMenu.h"
#include "fui/node/FJ_DragonHealth_01.h"
#include "fui/node/FJ_DragonHealth_02.h"
#include "fui/node/FJ_DragonHealth_03.h"
#include "fui/node/FJ_DragonHealth_04.h"
#include "fui/node/FJ_DragonHealth_05.h"
#include "fui/node/FJ_DynamicHtmlText.h"
#include "fui/node/FJ_DynamicHtmlText_Normal.h"
#include "fui/node/FJ_DynamicHtmlText_Small.h"
#include "fui/node/FJ_DynamicHtmlText_WithPanel_Normal.h"
#include "fui/node/FJ_DynamicHtmlText_WithPanel_Small.h"
#include "fui/node/FJ_EnchantingButton_Normal.h"
#include "fui/node/FJ_EnchantingButton_Small.h"
#include "fui/node/FJ_EnchantingMenu.h"
#include "fui/node/FJ_EndPoem.h"
#include "fui/node/FJ_Eula.h"
#include "fui/node/FJ_ExlamationMark.h"
#include "fui/node/FJ_ExperienceBar.h"
#include "fui/node/FJ_Factory.h"
#include "fui/node/FJ_FuiNode.h"
#include "fui/node/FJ_FullscreenProgress.h"
#include "fui/node/FJ_FurnaceArrow.h"
#include "fui/node/FJ_FurnaceArrow_Small.h"
#include "fui/node/FJ_FurnaceFlame.h"
#include "fui/node/FJ_FurnaceFlame_Small.h"
#include "fui/node/FJ_FurnaceMenu.h"
#include "fui/node/FJ_GameModeScoreboard.h"
#include "fui/node/FJ_GameModeSelection.h"
#include "fui/node/FJ_Gamertag.h"
#include "fui/node/FJ_HelpAndOptionsMenu.h"
#include "fui/node/FJ_HopperMenu.h"
#include "fui/node/FJ_HorseInventoryMenu.h"
#include "fui/node/FJ_HorseJumpBar.h"
#include "fui/node/FJ_HowToPlay.h"
#include "fui/node/FJ_HowToPlayMenu.h"
#include "fui/node/FJ_HtmlTextPanel.h"
#include "fui/node/FJ_HtmlTextPanelLarge.h"
#include "fui/node/FJ_HtmlText_Normal.h"
#include "fui/node/FJ_HtmlText_Small.h"
#include "fui/node/FJ_HtmlText_WhiteNormal.h"
#include "fui/node/FJ_HtmlText_WhiteSmall.h"
#include "fui/node/FJ_HtmlText_WithPanel_Normal.h"
#include "fui/node/FJ_HtmlText_WithPanel_Small.h"
#include "fui/node/FJ_Hud.h"
#include "fui/node/FJ_IconSlot.h"
#include "fui/node/FJ_InGameHostOptions.h"
#include "fui/node/FJ_InGameInfoMenu.h"
#include "fui/node/FJ_InGamePlayerOptions.h"
#include "fui/node/FJ_InGameTeleportMenu.h"
#include "fui/node/FJ_Intro.h"
#include "fui/node/FJ_InventoryMenu.h"
#include "fui/node/FJ_JoinGameFilterList.h"
#include "fui/node/FJ_JoinMenu.h"
#include "fui/node/FJ_KeyboardButtons_Controls_Normal.h"
#include "fui/node/FJ_KeyboardButtons_Controls_Small.h"
#include "fui/node/FJ_KeyboardButtons_Keys_Normal.h"
#include "fui/node/FJ_KeyboardButtons_Keys_Small.h"
#include "fui/node/FJ_KillBar.h"
#include "fui/node/FJ_KillBarSmall.h"
#include "fui/node/FJ_Label.h"
#include "fui/node/FJ_Label_BigBlack.h"
#include "fui/node/FJ_Label_BigGrey.h"
#include "fui/node/FJ_Label_BigWhite.h"
#include "fui/node/FJ_Label_Black.h"
#include "fui/node/FJ_Label_Black_Centered.h"
#include "fui/node/FJ_Label_Black_Centered_HUD.h"
#include "fui/node/FJ_Label_Black_Small_Centered.h"
#include "fui/node/FJ_Label_Black_Small_Centered_HUD.h"
#include "fui/node/FJ_Label_Black_VerySmall_Centered.h"
#include "fui/node/FJ_Label_Blink_Normal.h"
#include "fui/node/FJ_Label_Blink_Small.h"
#include "fui/node/FJ_Label_Book_Normal.h"
#include "fui/node/FJ_Label_Book_Small.h"
#include "fui/node/FJ_Label_Book_VerySmall.h"
#include "fui/node/FJ_Label_Credits_10.h"
#include "fui/node/FJ_Label_Credits_10_Yellow.h"
#include "fui/node/FJ_Label_Credits_20.h"
#include "fui/node/FJ_Label_Credits_20_Yellow.h"
#include "fui/node/FJ_Label_Credits_30.h"
#include "fui/node/FJ_Label_DragonHealth.h"
#include "fui/node/FJ_Label_DragonHealthBig.h"
#include "fui/node/FJ_Label_DragonHealthSmall.h"
#include "fui/node/FJ_Label_DragonHealthVerySmall.h"
#include "fui/node/FJ_Label_Green.h"
#include "fui/node/FJ_Label_Grey.h"
#include "fui/node/FJ_Label_HUD_BigWhite.h"
#include "fui/node/FJ_Label_HUD_Level_01.h"
#include "fui/node/FJ_Label_HUD_Level_02.h"
#include "fui/node/FJ_Label_HUD_Level_03.h"
#include "fui/node/FJ_Label_HUD_Level_04.h"
#include "fui/node/FJ_Label_HUD_Level_05.h"
#include "fui/node/FJ_Label_HUD_SmallWhite.h"
#include "fui/node/FJ_Label_HUD_Splash.h"
#include "fui/node/FJ_Label_HUD_SplashBig.h"
#include "fui/node/FJ_Label_HUD_SplashVita.h"
#include "fui/node/FJ_Label_HUD_VerySmallWhite.h"
#include "fui/node/FJ_Label_HUD_White.h"
#include "fui/node/FJ_Label_Html.h"
#include "fui/node/FJ_Label_HtmlEndPoem.h"
#include "fui/node/FJ_Label_HtmlEndPoemHD.h"
#include "fui/node/FJ_Label_HtmlSmall.h"
#include "fui/node/FJ_Label_OutlineLevel.h"
#include "fui/node/FJ_Label_OutlineLevel_Small.h"
#include "fui/node/FJ_Label_OutlineTitle.h"
#include "fui/node/FJ_Label_OutlineTitle_Small.h"
#include "fui/node/FJ_Label_Red.h"
#include "fui/node/FJ_Label_SkinSelect.h"
#include "fui/node/FJ_Label_SkinSelectCenter.h"
#include "fui/node/FJ_Label_SkinSelectCenter_Off.h"
#include "fui/node/FJ_Label_SkinSelectCenter_Small.h"
#include "fui/node/FJ_Label_SkinSelectCenter_Small_Off.h"
#include "fui/node/FJ_Label_SkinSelect_Off.h"
#include "fui/node/FJ_Label_SkinSelect_Small.h"
#include "fui/node/FJ_Label_SkinSelect_Small_Off.h"
#include "fui/node/FJ_Label_SmallBlack.h"
#include "fui/node/FJ_Label_SmallGreen.h"
#include "fui/node/FJ_Label_SmallGrey.h"
#include "fui/node/FJ_Label_SmallRed.h"
#include "fui/node/FJ_Label_SmallWhite.h"
#include "fui/node/FJ_Label_VerySmallBlack.h"
#include "fui/node/FJ_Label_VerySmallGrey.h"
#include "fui/node/FJ_Label_VerySmallWhite.h"
#include "fui/node/FJ_Label_White.h"
#include "fui/node/FJ_Label_WhiteHtml.h"
#include "fui/node/FJ_Label_WhiteHtmlSmall.h"
#include "fui/node/FJ_Label_White_Centered.h"
#include "fui/node/FJ_Label_White_Small_Centered.h"
#include "fui/node/FJ_Label_White_VerySmall_Centered.h"
#include "fui/node/FJ_LaunchMoreOptionsMenu.h"
#include "fui/node/FJ_LayoutButton.h"
#include "fui/node/FJ_LayoutButton_Small.h"
#include "fui/node/FJ_LeaderboardEntryNormal.h"
#include "fui/node/FJ_LeaderboardEntrySmall.h"
#include "fui/node/FJ_LeaderboardHeaderNormal.h"
#include "fui/node/FJ_LeaderboardHeaderSmall.h"
#include "fui/node/FJ_LeaderboardList.h"
#include "fui/node/FJ_LeaderboardMenu.h"
#include "fui/node/FJ_ListButtonAchievement_Normal.h"
#include "fui/node/FJ_ListButtonAchievement_Small.h"
#include "fui/node/FJ_ListButtonCheckbox_Normal.h"
#include "fui/node/FJ_ListButtonCheckbox_Small.h"
#include "fui/node/FJ_ListButtonController_Normal.h"
#include "fui/node/FJ_ListButtonController_Small.h"
#include "fui/node/FJ_ListButtonDLC_Normal.h"
#include "fui/node/FJ_ListButtonDLC_Small.h"
#include "fui/node/FJ_ListButtonIconLeft_Normal.h"
#include "fui/node/FJ_ListButtonIconLeft_Small.h"
#include "fui/node/FJ_ListButtonIconX2Left_Normal.h"
#include "fui/node/FJ_ListButtonIconX2Left_Small.h"
#include "fui/node/FJ_ListButtonLayerIcon_Normal.h"
#include "fui/node/FJ_ListButtonLayerIcon_Small.h"
#include "fui/node/FJ_ListButtonLobby_Normal.h"
#include "fui/node/FJ_ListButtonLobby_Small.h"
#include "fui/node/FJ_ListButtonPlayerList_Normal.h"
#include "fui/node/FJ_ListButtonPlayerList_Small.h"
#include "fui/node/FJ_ListButtonScoreBoard_Normal.h"
#include "fui/node/FJ_ListButtonScoreBoard_Small.h"
#include "fui/node/FJ_ListButton_Medium.h"
#include "fui/node/FJ_ListButton_Normal.h"
#include "fui/node/FJ_ListButton_Small.h"
#include "fui/node/FJ_ListLabel_Black.h"
#include "fui/node/FJ_ListLabel_SmallBlack.h"
#include "fui/node/FJ_List_ListButtonAchievement.h"
#include "fui/node/FJ_List_ListButtonCheckbox.h"
#include "fui/node/FJ_List_ListButtonDLC.h"
#include "fui/node/FJ_List_ListButtonIconLeft.h"
#include "fui/node/FJ_List_ListButtonLayerIcon.h"
#include "fui/node/FJ_List_ListButtonLobby.h"
#include "fui/node/FJ_List_ListButtonScoreBoard.h"
#include "fui/node/FJ_List_MultiList.h"
#include "fui/node/FJ_LoadCreateJoinMenu.h"
#include "fui/node/FJ_LoadMenu.h"
#include "fui/node/FJ_LoadOrJoinMenu.h"
#include "fui/node/FJ_MCBREUpSell.h"
#include "fui/node/FJ_MainMenu.h"
#include "fui/node/FJ_MapSelectMenu.h"
#include "fui/node/FJ_MenuButton_Normal.h"
#include "fui/node/FJ_MenuButton_Small.h"
#include "fui/node/FJ_MessageBox.h"
#include "fui/node/FJ_MobEffect_Normal.h"
#include "fui/node/FJ_MobEffect_Small.h"
#include "fui/node/FJ_MultilistMenu.h"
#include "fui/node/FJ_Panel9GridFade.h"
#include "fui/node/FJ_PanelRecessFade.h"
#include "fui/node/FJ_Panorama.h"
#include "fui/node/FJ_PauseMenu.h"
#include "fui/node/FJ_PressStartToPlay.h"
#include "fui/node/FJ_ProgressBar_Loading.h"
#include "fui/node/FJ_QuadrantSignin.h"
#include "fui/node/FJ_SaveMenu.h"
#include "fui/node/FJ_SaveMessage.h"
#include "fui/node/FJ_ScrollArrow.h"
#include "fui/node/FJ_ScrollArrowH.h"
#include "fui/node/FJ_SettingsAudioMenu.h"
#include "fui/node/FJ_SettingsControlMenu.h"
#include "fui/node/FJ_SettingsGraphicsMenu.h"
#include "fui/node/FJ_SettingsMenu.h"
#include "fui/node/FJ_SettingsOptionsMenu.h"
#include "fui/node/FJ_SettingsUIMenu.h"
#include "fui/node/FJ_SignEntryMenu.h"
#include "fui/node/FJ_SignInput.h"
#include "fui/node/FJ_SkinSelect.h"
#include "fui/node/FJ_Slider_Normal.h"
#include "fui/node/FJ_Slider_Small.h"
#include "fui/node/FJ_SlotList.h"
#include "fui/node/FJ_SlotList_Slot.h"
#include "fui/node/FJ_SocialPost.h"
#include "fui/node/FJ_SpaceIndicatorBar.h"
#include "fui/node/FJ_SuperFlatEditLayerMenu.h"
#include "fui/node/FJ_SuperFlatMenu.h"
#include "fui/node/FJ_SuperFlatPresets.h"
#include "fui/node/FJ_TextInput.h"
#include "fui/node/FJ_TextInput_Normal.h"
#include "fui/node/FJ_TextInput_Small.h"
#include "fui/node/FJ_TextInput_Vita.h"
#include "fui/node/FJ_TexturePackList.h"
#include "fui/node/FJ_TexturePackList_Slot.h"
#include "fui/node/FJ_ToolTip_Normal.h"
#include "fui/node/FJ_ToolTip_Small.h"
#include "fui/node/FJ_ToolTips.h"
#include "fui/node/FJ_TouchControl.h"
#include "fui/node/FJ_TouchControlFrontend.h"
#include "fui/node/FJ_TradingMenu.h"
#include "fui/node/FJ_TutorialPopup.h"
#include "fui/node/FJ_UpsellButton_Normal.h"
#include "fui/node/FJ_UpsellButton_Small.h"
#include "fui/node/FJ_WiiUDRC.h"
#include "fui/node/FJ_panel9Grid_16Fade.h"
#include "fui/node/control/FJ_List_ListButton.h"
#include "fui/node/control/FJ_List_ListButtonPlayerList.h"
#include "fui/node/control/FJ_List_MenuButton.h"
#include <utility>

std::string FJ_Factory::FJ_FuiNode = "FJ_FuiNode";
std::string FJ_Factory::FJ_MenuButton_Normal = "FJ_MenuButton_Normal";
std::string FJ_Factory::FJ_MenuButton_Small = "FJ_MenuButton_Small";
std::string FJ_Factory::FJ_ListButton_Medium = "FJ_ListButton_Medium";
std::string FJ_Factory::FJ_ListButton_Normal = "FJ_ListButton_Normal";
std::string FJ_Factory::FJ_ListButton_Small = "FJ_ListButton_Small";
std::string FJ_Factory::FJ_UpsellButton_Normal = "FJ_UpsellButton_Normal";
std::string FJ_Factory::FJ_UpsellButton_Small = "FJ_UpsellButton_Small";
std::string FJ_Factory::FJ_ListButtonIconLeft_Normal = "FJ_ListButtonIconLeft_Normal";
std::string FJ_Factory::FJ_ListButtonIconLeft_Small = "FJ_ListButtonIconLeft_Small";
std::string FJ_Factory::FJ_ListButtonIconX2Left_Normal = "FJ_ListButtonIconX2Left_Normal";
std::string FJ_Factory::FJ_ListButtonIconX2Left_Small = "FJ_ListButtonIconX2Left_Small";
std::string FJ_Factory::FJ_List_ListButtonIconLeft = "FJ_List_ListButtonIconLeft";
std::string FJ_Factory::FJ_List_ListButton = "FJ_List_ListButton";
std::string FJ_Factory::FJ_List_ListButtonCheckbox = "FJ_List_ListButtonCheckbox";
std::string FJ_Factory::FJ_List_ListButtonDLC = "FJ_List_ListButtonDLC";
std::string FJ_Factory::FJ_List_ListButtonLayerIcon = "FJ_List_ListButtonLayerIcon";
std::string FJ_Factory::FJ_List_ListButtonLobby = "FJ_List_ListButtonLobby";
std::string FJ_Factory::FJ_List_ListButtonPlayerList = "FJ_List_ListButtonPlayerList";
std::string FJ_Factory::FJ_List_ListButtonScoreBoard = "FJ_List_ListButtonScoreBoard";
std::string FJ_Factory::FJ_List_ListButtonAchievement = "FJ_List_ListButtonAchievement";
std::string FJ_Factory::FJ_CheckpointMarker = "FJ_CheckpointMarker";
std::string FJ_Factory::FJ_List_MenuButton = "FJ_List_MenuButton";
std::string FJ_Factory::FJ_BeaconEffectButton_Normal = "FJ_BeaconEffectButton_Normal";
std::string FJ_Factory::FJ_BeaconEffectButton_Small = "FJ_BeaconEffectButton_Small";
std::string FJ_Factory::FJ_EnchantingButton_Normal = "FJ_EnchantingButton_Normal";
std::string FJ_Factory::FJ_EnchantingButton_Small = "FJ_EnchantingButton_Small";
std::string FJ_Factory::FJ_KeyboardButtons_Controls_Normal = "FJ_KeyboardButtons_Controls_Normal";
std::string FJ_Factory::FJ_KeyboardButtons_Controls_Small = "FJ_KeyboardButtons_Controls_Small";
std::string FJ_Factory::FJ_KeyboardButtons_Keys_Normal = "FJ_KeyboardButtons_Keys_Normal";
std::string FJ_Factory::FJ_KeyboardButtons_Keys_Small = "FJ_KeyboardButtons_Keys_Small";
std::string FJ_Factory::FJ_LayoutButton = "FJ_LayoutButton";
std::string FJ_Factory::FJ_LayoutButton_Small = "FJ_LayoutButton_Small";
std::string FJ_Factory::FJ_ListButtonAchievement_Normal = "FJ_ListButtonAchievement_Normal";
std::string FJ_Factory::FJ_ListButtonAchievement_Small = "FJ_ListButtonAchievement_Small";
std::string FJ_Factory::FJ_ListButtonCheckbox_Normal = "FJ_ListButtonCheckbox_Normal";
std::string FJ_Factory::FJ_ListButtonCheckbox_Small = "FJ_ListButtonCheckbox_Small";
std::string FJ_Factory::FJ_ListButtonDLC_Normal = "FJ_ListButtonDLC_Normal";
std::string FJ_Factory::FJ_ListButtonDLC_Small = "FJ_ListButtonDLC_Small";
std::string FJ_Factory::FJ_ListButtonLayerIcon_Normal = "FJ_ListButtonLayerIcon_Normal";
std::string FJ_Factory::FJ_ListButtonLayerIcon_Small = "FJ_ListButtonLayerIcon_Small";
std::string FJ_Factory::FJ_ListButtonLobby_Normal = "FJ_ListButtonLobby_Normal";
std::string FJ_Factory::FJ_ListButtonLobby_Small = "FJ_ListButtonLobby_Small";
std::string FJ_Factory::FJ_ListButtonPlayerList_Normal = "FJ_ListButtonPlayerList_Normal";
std::string FJ_Factory::FJ_ListButtonPlayerList_Small = "FJ_ListButtonPlayerList_Small";
std::string FJ_Factory::FJ_ListButtonScoreBoard_Normal = "FJ_ListButtonScoreBoard_Normal";
std::string FJ_Factory::FJ_ListButtonScoreBoard_Small = "FJ_ListButtonScoreBoard_Small";
std::string FJ_Factory::FJ_ListButtonController_Normal = "FJ_ListButtonController_Normal";
std::string FJ_Factory::FJ_ListButtonController_Small = "FJ_ListButtonController_Small";
std::string FJ_Factory::FJ_LeaderboardList = "FJ_LeaderboardList";
std::string FJ_Factory::FJ_LeaderboardEntryNormal = "FJ_LeaderboardEntryNormal";
std::string FJ_Factory::FJ_LeaderboardEntrySmall = "FJ_LeaderboardEntrySmall";
std::string FJ_Factory::FJ_LeaderboardHeaderNormal = "FJ_LeaderboardHeaderNormal";
std::string FJ_Factory::FJ_LeaderboardHeaderSmall = "FJ_LeaderboardHeaderSmall";
std::string FJ_Factory::FJ_IconSlot = "FJ_IconSlot";
std::string FJ_Factory::FJ_ToolTip_Normal = "FJ_ToolTip_Normal";
std::string FJ_Factory::FJ_ToolTip_Small = "FJ_ToolTip_Small";
std::string FJ_Factory::FJ_Label = "FJ_Label";
std::string FJ_Factory::FJ_Label_Blink_Normal = "FJ_Label_Blink_Normal";
std::string FJ_Factory::FJ_Label_Blink_Small = "FJ_Label_Blink_Small";
std::string FJ_Factory::FJ_ScrollArrow = "FJ_ScrollArrow";
std::string FJ_Factory::FJ_ScrollArrowH = "FJ_ScrollArrowH";
std::string FJ_Factory::FJ_Slider_Normal = "FJ_Slider_Normal";
std::string FJ_Factory::FJ_Slider_Small = "FJ_Slider_Small";
std::string FJ_Factory::FJ_TexturePackList = "FJ_TexturePackList";
std::string FJ_Factory::FJ_TexturePackList_Slot = "FJ_TexturePackList_Slot";
std::string FJ_Factory::FJ_SlotList = "FJ_SlotList";
std::string FJ_Factory::FJ_SlotList_Slot = "FJ_SlotList_Slot";
std::string FJ_Factory::FJ_CheckBox_Normal = "FJ_CheckBox_Normal";
std::string FJ_Factory::FJ_CheckBox_Small = "FJ_CheckBox_Small";
std::string FJ_Factory::FJ_ExlamationMark = "FJ_ExlamationMark";
std::string FJ_Factory::FJ_Cursor_Normal = "FJ_Cursor_Normal";
std::string FJ_Factory::FJ_Cursor_Small = "FJ_Cursor_Small";
std::string FJ_Factory::FJ_MobEffect_Small = "FJ_MobEffect_Small";
std::string FJ_Factory::FJ_MobEffect_Normal = "FJ_MobEffect_Normal";
std::string FJ_Factory::FJ_TouchControl = "FJ_TouchControl";
std::string FJ_Factory::FJ_TouchControlFrontend = "FJ_TouchControlFrontend";
std::string FJ_Factory::FJ_BitmapIcon = "FJ_BitmapIcon";
std::string FJ_Factory::FJ_List_MultiList = "FJ_List_MultiList";
std::string FJ_Factory::CreditsMenu = "CreditsMenu";
std::string FJ_Factory::EndPoem = "EndPoem";
std::string FJ_Factory::MainMenu = "MainMenu";
std::string FJ_Factory::LoadMenu = "LoadMenu";
std::string FJ_Factory::SaveMessage = "SaveMessage";
std::string FJ_Factory::ComponentLogo = "ComponentLogo";
std::string FJ_Factory::Panorama = "Panorama";
std::string FJ_Factory::ToolTips = "ToolTips";
std::string FJ_Factory::Intro = "Intro";
std::string FJ_Factory::LoadCreateJoinMenu = "LoadCreateJoinMenu";
std::string FJ_Factory::Hud = "Hud";
std::string FJ_Factory::HowToPlayMenu = "HowToPlayMenu";
std::string FJ_Factory::HowToPlay = "HowToPlay";
std::string FJ_Factory::CreativeMenu = "CreativeMenu";
std::string FJ_Factory::CraftingMenu = "CraftingMenu";
std::string FJ_Factory::InventoryMenu = "InventoryMenu";
std::string FJ_Factory::FullscreenProgress = "FullscreenProgress";
std::string FJ_Factory::Eula = "Eula";
std::string FJ_Factory::MessageBox = "MessageBox";
std::string FJ_Factory::PauseMenu = "PauseMenu";
std::string FJ_Factory::HelpAndOptionsMenu = "HelpAndOptionsMenu";
std::string FJ_Factory::SettingsMenu = "SettingsMenu";
std::string FJ_Factory::MCBREUpSell = "MCBREUpSell";
std::string FJ_Factory::AnvilMenu = "AnvilMenu";
std::string FJ_Factory::BeaconMenu = "BeaconMenu";
std::string FJ_Factory::BrewingStandMenu = "BrewingStandMenu";
std::string FJ_Factory::ClassicCraftingMenu = "ClassicCraftingMenu";
std::string FJ_Factory::ChestMenu = "ChestMenu";
std::string FJ_Factory::DispenserMenu = "DispenserMenu";
std::string FJ_Factory::EnchantingMenu = "EnchantingMenu";
std::string FJ_Factory::FurnaceMenu = "FurnaceMenu";
std::string FJ_Factory::HopperMenu = "HopperMenu";
std::string FJ_Factory::HorseInventoryMenu = "HorseInventoryMenu";
std::string FJ_Factory::BookAndQuillMenu = "BookAndQuillMenu";
std::string FJ_Factory::ControlsMenu = "ControlsMenu";
std::string FJ_Factory::PressStartToPlay = "PressStartToPlay";
std::string FJ_Factory::SuperFlatMenu = "SuperFlatMenu";
std::string FJ_Factory::SuperFlatPresets = "SuperFlatPresets";
std::string FJ_Factory::SuperFlatEditLayerMenu = "SuperFlatEditLayerMenu";
std::string FJ_Factory::QuadrantSignin = "QuadrantSignin";
std::string FJ_Factory::LeaderboardMenu = "LeaderboardMenu";
std::string FJ_Factory::TradingMenu = "TradingMenu";
std::string FJ_Factory::GameModeScoreboard = "GameModeScoreboard";
std::string FJ_Factory::BiomeSelectMenu = "BiomeSelectMenu";
std::string FJ_Factory::ComponentChat = "ComponentChat";
std::string FJ_Factory::DeathMenu = "DeathMenu";
std::string FJ_Factory::DebugBuildTools = "DebugBuildTools";
std::string FJ_Factory::DebugCreateSchematic = "DebugCreateSchematic";
std::string FJ_Factory::DebugFillArea = "DebugFillArea";
std::string FJ_Factory::DebugMarketingGuide = "DebugMarketingGuide";
std::string FJ_Factory::DebugMenu = "DebugMenu";
std::string FJ_Factory::DebugOptions = "DebugOptions";
std::string FJ_Factory::DebugPuppeteer = "DebugPuppeteer";
std::string FJ_Factory::DebugSetCamera = "DebugSetCamera";
std::string FJ_Factory::DLCMainMenu = "DLCMainMenu";
std::string FJ_Factory::DLCOffersMenu = "DLCOffersMenu";
std::string FJ_Factory::GameModeSelection = "GameModeSelection";
std::string FJ_Factory::Gamertag = "Gamertag";
std::string FJ_Factory::JoinGameFilterList = "JoinGameFilterList";
std::string FJ_Factory::JoinMenu = "JoinMenu";
std::string FJ_Factory::LoadOrJoinMenu = "LoadOrJoinMenu";
std::string FJ_Factory::SaveMenu = "SaveMenu";
std::string FJ_Factory::SettingsAudioMenu = "SettingsAudioMenu";
std::string FJ_Factory::SettingsControlMenu = "SettingsControlMenu";
std::string FJ_Factory::SettingsGraphicsMenu = "SettingsGraphicsMenu";
std::string FJ_Factory::SettingsOptionsMenu = "SettingsOptionsMenu";
std::string FJ_Factory::SettingsUIMenu = "SettingsUIMenu";
std::string FJ_Factory::SignEntryMenu = "SignEntryMenu";
std::string FJ_Factory::SocialPost = "SocialPost";
std::string FJ_Factory::WiiUDRC = "WiiUDRC";
std::string FJ_Factory::AchievementsMenu = "AchievementsMenu";
std::string FJ_Factory::AvatarSelectMenu = "AvatarSelectMenu";
std::string FJ_Factory::CreateWorldMenu = "CreateWorldMenu";
std::string FJ_Factory::LaunchMoreOptionsMenu = "LaunchMoreOptionsMenu";
std::string FJ_Factory::TutorialPopup = "TutorialPopup";
std::string FJ_Factory::MultilistMenu = "MultilistMenu";
std::string FJ_Factory::SkinSelect = "SkinSelect";
std::string FJ_Factory::InGamePlayerOptions = "InGamePlayerOptions";
std::string FJ_Factory::InGameHostOptions = "InGameHostOptions";
std::string FJ_Factory::InGameInfoMenu = "InGameInfoMenu";
std::string FJ_Factory::InGameTeleportMenu = "InGameTeleportMenu";
std::string FJ_Factory::MapSelectMenu = "MapSelectMenu";
std::string FJ_Factory::FJ_DragonHealth_01 = "FJ_DragonHealth_01";
std::string FJ_Factory::FJ_DragonHealth_02 = "FJ_DragonHealth_02";
std::string FJ_Factory::FJ_DragonHealth_03 = "FJ_DragonHealth_03";
std::string FJ_Factory::FJ_DragonHealth_04 = "FJ_DragonHealth_04";
std::string FJ_Factory::FJ_DragonHealth_05 = "FJ_DragonHealth_05";
std::string FJ_Factory::FJ_HorseJumpBar = "FJ_HorseJumpBar";
std::string FJ_Factory::FJ_ExperienceBar = "FJ_ExperienceBar";
std::string FJ_Factory::FJ_BrewingArrow = "FJ_BrewingArrow";
std::string FJ_Factory::FJ_BrewingArrow_Small = "FJ_BrewingArrow_Small";
std::string FJ_Factory::FJ_BrewingBubbles = "FJ_BrewingBubbles";
std::string FJ_Factory::FJ_BrewingBubbles_Small = "FJ_BrewingBubbles_Small";
std::string FJ_Factory::FJ_BrewingPlate = "FJ_BrewingPlate";
std::string FJ_Factory::FJ_BrewingPlate_Small = "FJ_BrewingPlate_Small";
std::string FJ_Factory::FJ_FurnaceArrow = "FJ_FurnaceArrow";
std::string FJ_Factory::FJ_FurnaceArrow_Small = "FJ_FurnaceArrow_Small";
std::string FJ_Factory::FJ_FurnaceFlame = "FJ_FurnaceFlame";
std::string FJ_Factory::FJ_FurnaceFlame_Small = "FJ_FurnaceFlame_Small";
std::string FJ_Factory::FJ_KillBar = "FJ_KillBar";
std::string FJ_Factory::FJ_KillBarSmall = "FJ_KillBarSmall";
std::string FJ_Factory::FJ_ProgressBar_Loading = "FJ_ProgressBar_Loading";
std::string FJ_Factory::FJ_AttackIndicatorCrosshair = "FJ_AttackIndicatorCrosshair";
std::string FJ_Factory::FJ_AttackIndicatorHotbar = "FJ_AttackIndicatorHotbar";
std::string FJ_Factory::FJ_SpaceIndicatorBar = "FJ_SpaceIndicatorBar";
std::string FJ_Factory::FJ_TextInput = "FJ_TextInput";
std::string FJ_Factory::FJ_TextInput_Small = "FJ_TextInput_Small";
std::string FJ_Factory::FJ_TextInput_Normal = "FJ_TextInput_Normal";
std::string FJ_Factory::FJ_TextInput_Vita = "FJ_TextInput_Vita";
std::string FJ_Factory::FJ_HtmlTextPanel = "FJ_HtmlTextPanel";
std::string FJ_Factory::FJ_HtmlTextPanelLarge = "FJ_HtmlTextPanelLarge";
std::string FJ_Factory::FJ_Label_BigBlack = "FJ_Label_BigBlack";
std::string FJ_Factory::FJ_Label_BigGrey = "FJ_Label_BigGrey";
std::string FJ_Factory::FJ_Label_BigWhite = "FJ_Label_BigWhite";
std::string FJ_Factory::FJ_Label_Black = "FJ_Label_Black";
std::string FJ_Factory::FJ_Label_Black_Centered = "FJ_Label_Black_Centered";
std::string FJ_Factory::FJ_Label_Black_Centered_HUD = "FJ_Label_Black_Centered_HUD";
std::string FJ_Factory::FJ_Label_Black_Small_Centered = "FJ_Label_Black_Small_Centered";
std::string FJ_Factory::FJ_Label_Black_Small_Centered_HUD = "FJ_Label_Black_Small_Centered_HUD";
std::string FJ_Factory::FJ_Label_Black_VerySmall_Centered = "FJ_Label_Black_VerySmall_Centered";
std::string FJ_Factory::FJ_Label_Book_Normal = "FJ_Label_Book_Normal";
std::string FJ_Factory::FJ_Label_Book_Small = "FJ_Label_Book_Small";
std::string FJ_Factory::FJ_Label_Book_VerySmall = "FJ_Label_Book_VerySmall";
std::string FJ_Factory::FJ_Label_Credits_10 = "FJ_Label_Credits_10";
std::string FJ_Factory::FJ_Label_Credits_10_Yellow = "FJ_Label_Credits_10_Yellow";
std::string FJ_Factory::FJ_Label_Credits_20 = "FJ_Label_Credits_20";
std::string FJ_Factory::FJ_Label_Credits_20_Yellow = "FJ_Label_Credits_20_Yellow";
std::string FJ_Factory::FJ_Label_Credits_30 = "FJ_Label_Credits_30";
std::string FJ_Factory::FJ_Label_DragonHealth = "FJ_Label_DragonHealth";
std::string FJ_Factory::FJ_Label_DragonHealthBig = "FJ_Label_DragonHealthBig";
std::string FJ_Factory::FJ_Label_DragonHealthSmall = "FJ_Label_DragonHealthSmall";
std::string FJ_Factory::FJ_Label_DragonHealthVerySmall = "FJ_Label_DragonHealthVerySmall";
std::string FJ_Factory::FJ_Label_Green = "FJ_Label_Green";
std::string FJ_Factory::FJ_Label_Grey = "FJ_Label_Grey";
std::string FJ_Factory::FJ_Label_Html = "FJ_Label_Html";
std::string FJ_Factory::FJ_Label_HtmlEndPoem = "FJ_Label_HtmlEndPoem";
std::string FJ_Factory::FJ_Label_HtmlEndPoemHD = "FJ_Label_HtmlEndPoemHD";
std::string FJ_Factory::FJ_Label_HtmlSmall = "FJ_Label_HtmlSmall";
std::string FJ_Factory::FJ_Label_HUD_Level_01 = "FJ_Label_HUD_Level_01";
std::string FJ_Factory::FJ_Label_HUD_Level_02 = "FJ_Label_HUD_Level_02";
std::string FJ_Factory::FJ_Label_HUD_Level_03 = "FJ_Label_HUD_Level_03";
std::string FJ_Factory::FJ_Label_HUD_Level_04 = "FJ_Label_HUD_Level_04";
std::string FJ_Factory::FJ_Label_HUD_Level_05 = "FJ_Label_HUD_Level_05";
std::string FJ_Factory::FJ_Label_HUD_SmallWhite = "FJ_Label_HUD_SmallWhite";
std::string FJ_Factory::FJ_Label_HUD_BigWhite = "FJ_Label_HUD_BigWhite";
std::string FJ_Factory::FJ_Label_HUD_Splash = "FJ_Label_HUD_Splash";
std::string FJ_Factory::FJ_Label_HUD_SplashBig = "FJ_Label_HUD_SplashBig";
std::string FJ_Factory::FJ_Label_HUD_SplashVita = "FJ_Label_HUD_SplashVita";
std::string FJ_Factory::FJ_Label_HUD_VerySmallWhite = "FJ_Label_HUD_VerySmallWhite";
std::string FJ_Factory::FJ_Label_HUD_White = "FJ_Label_HUD_White";
std::string FJ_Factory::FJ_Label_OutlineLevel = "FJ_Label_OutlineLevel";
std::string FJ_Factory::FJ_Label_OutlineLevel_Small = "FJ_Label_OutlineLevel_Small";
std::string FJ_Factory::FJ_Label_OutlineTitle = "FJ_Label_OutlineTitle";
std::string FJ_Factory::FJ_Label_OutlineTitle_Small = "FJ_Label_OutlineTitle_Small";
std::string FJ_Factory::FJ_Label_Red = "FJ_Label_Red";
std::string FJ_Factory::FJ_Label_SkinSelect = "FJ_Label_SkinSelect";
std::string FJ_Factory::FJ_Label_SkinSelectCenter = "FJ_Label_SkinSelectCenter";
std::string FJ_Factory::FJ_Label_SkinSelectCenter_Off = "FJ_Label_SkinSelectCenter_Off";
std::string FJ_Factory::FJ_Label_SkinSelectCenter_Small = "FJ_Label_SkinSelectCenter_Small";
std::string FJ_Factory::FJ_Label_SkinSelectCenter_Small_Off = "FJ_Label_SkinSelectCenter_Small_Off";
std::string FJ_Factory::FJ_Label_SkinSelect_Off = "FJ_Label_SkinSelect_Off";
std::string FJ_Factory::FJ_Label_SkinSelect_Small = "FJ_Label_SkinSelect_Small";
std::string FJ_Factory::FJ_Label_SkinSelect_Small_Off = "FJ_Label_SkinSelect_Small_Off";
std::string FJ_Factory::FJ_Label_SmallBlack = "FJ_Label_SmallBlack";
std::string FJ_Factory::FJ_Label_SmallGreen = "FJ_Label_SmallGreen";
std::string FJ_Factory::FJ_Label_SmallGrey = "FJ_Label_SmallGrey";
std::string FJ_Factory::FJ_Label_SmallRed = "FJ_Label_SmallRed";
std::string FJ_Factory::FJ_Label_SmallWhite = "FJ_Label_SmallWhite";
std::string FJ_Factory::FJ_Label_VerySmallBlack = "FJ_Label_VerySmallBlack";
std::string FJ_Factory::FJ_Label_VerySmallGrey = "FJ_Label_VerySmallGrey";
std::string FJ_Factory::FJ_Label_VerySmallWhite = "FJ_Label_VerySmallWhite";
std::string FJ_Factory::FJ_Label_White = "FJ_Label_White";
std::string FJ_Factory::FJ_Label_WhiteHtml = "FJ_Label_WhiteHtml";
std::string FJ_Factory::FJ_Label_WhiteHtmlSmall = "FJ_Label_WhiteHtmlSmall";
std::string FJ_Factory::FJ_Label_White_Centered = "FJ_Label_White_Centered";
std::string FJ_Factory::FJ_Label_White_Small_Centered = "FJ_Label_White_Small_Centered";
std::string FJ_Factory::FJ_Label_White_VerySmall_Centered = "FJ_Label_White_VerySmall_Centered";
std::string FJ_Factory::FJ_ListLabel_Black = "FJ_ListLabel_Black";
std::string FJ_Factory::FJ_ListLabel_SmallBlack = "FJ_ListLabel_SmallBlack";
std::string FJ_Factory::FJ_HtmlText_Normal = "FJ_HtmlText_Normal";
std::string FJ_Factory::FJ_HtmlText_Small = "FJ_HtmlText_Small";
std::string FJ_Factory::FJ_HtmlText_WhiteNormal = "FJ_HtmlText_WhiteNormal";
std::string FJ_Factory::FJ_HtmlText_WhiteSmall = "FJ_HtmlText_WhiteSmall";
std::string FJ_Factory::FJ_HtmlText_WithPanel_Normal = "FJ_HtmlText_WithPanel_Normal";
std::string FJ_Factory::FJ_HtmlText_WithPanel_Small = "FJ_HtmlText_WithPanel_Small";
std::string FJ_Factory::FJ_DynamicHtmlText = "FJ_DynamicHtmlText";
std::string FJ_Factory::FJ_DynamicHtmlText_Normal = "FJ_DynamicHtmlText_Normal";
std::string FJ_Factory::FJ_DynamicHtmlText_Small = "FJ_DynamicHtmlText_Small";
std::string FJ_Factory::FJ_DynamicHtmlText_WithPanel_Normal = "FJ_DynamicHtmlText_WithPanel_Normal";
std::string FJ_Factory::FJ_DynamicHtmlText_WithPanel_Small = "FJ_DynamicHtmlText_WithPanel_Small";
std::string FJ_Factory::FJ_SignInput = "FJ_SignInput";
std::string FJ_Factory::FJ_panel9Grid_16Fade = "FJ_panel9Grid_16Fade";
std::string FJ_Factory::FJ_Panel9GridFade = "FJ_Panel9GridFade";
std::string FJ_Factory::FJ_PanelRecessFade = "FJ_PanelRecessFade";

void FJ_Factory::initialise() {
    sNodes.emplace(std::make_pair(std::string(FJ_FuiNode), &FJ_FuiNode::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_MenuButton_Normal), &FJ_MenuButton_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_MenuButton_Small), &FJ_MenuButton_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListButton_Medium), &FJ_ListButton_Medium::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListButton_Normal), &FJ_ListButton_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListButton_Small), &FJ_ListButton_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_UpsellButton_Normal), &FJ_UpsellButton_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_UpsellButton_Small), &FJ_UpsellButton_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonIconLeft_Normal), &FJ_ListButtonIconLeft_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonIconLeft_Small), &FJ_ListButtonIconLeft_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonIconX2Left_Normal), &FJ_ListButtonIconX2Left_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonIconX2Left_Small), &FJ_ListButtonIconX2Left_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_List_ListButtonIconLeft), &FJ_List_ListButtonIconLeft::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_List_ListButton), &FJ_List_ListButton::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_List_ListButtonCheckbox), &FJ_List_ListButtonCheckbox::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_List_ListButtonDLC), &FJ_List_ListButtonDLC::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_List_ListButtonLayerIcon), &FJ_List_ListButtonLayerIcon::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_List_ListButtonLobby), &FJ_List_ListButtonLobby::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_List_ListButtonPlayerList), &FJ_List_ListButtonPlayerList::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_List_ListButtonScoreBoard), &FJ_List_ListButtonScoreBoard::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_List_ListButtonAchievement), &FJ_List_ListButtonAchievement::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_CheckpointMarker), &FJ_CheckpointMarker::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_List_MenuButton), &FJ_List_MenuButton::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_BeaconEffectButton_Normal), &FJ_BeaconEffectButton_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_BeaconEffectButton_Small), &FJ_BeaconEffectButton_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_EnchantingButton_Normal), &FJ_EnchantingButton_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_EnchantingButton_Small), &FJ_EnchantingButton_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_KeyboardButtons_Controls_Normal),
                                  FJ_KeyboardButtons_Controls_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_KeyboardButtons_Controls_Small),
                                  FJ_KeyboardButtons_Controls_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_KeyboardButtons_Keys_Normal), &FJ_KeyboardButtons_Keys_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_KeyboardButtons_Keys_Small), &FJ_KeyboardButtons_Keys_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_KeyboardButtons_Controls_Normal),
                                  FJ_KeyboardButtons_Controls_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_LayoutButton), &FJ_LayoutButton::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_LayoutButton_Small), &FJ_LayoutButton_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListButtonAchievement_Normal),
                                  FJ_ListButtonAchievement_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonAchievement_Small), &FJ_ListButtonAchievement_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonCheckbox_Normal), &FJ_ListButtonCheckbox_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonCheckbox_Small), &FJ_ListButtonCheckbox_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListButtonDLC_Normal), &FJ_ListButtonDLC_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListButtonDLC_Small), &FJ_ListButtonDLC_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonLayerIcon_Normal), &FJ_ListButtonLayerIcon_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonLayerIcon_Small), &FJ_ListButtonLayerIcon_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonLobby_Normal), &FJ_ListButtonLobby_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListButtonLobby_Small), &FJ_ListButtonLobby_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonPlayerList_Normal), &FJ_ListButtonPlayerList_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonPlayerList_Small), &FJ_ListButtonPlayerList_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonScoreBoard_Normal), &FJ_ListButtonScoreBoard_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonScoreBoard_Small), &FJ_ListButtonScoreBoard_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonController_Normal), &FJ_ListButtonController_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_ListButtonController_Small), &FJ_ListButtonController_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_LeaderboardList), &FJ_LeaderboardList::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_LeaderboardEntryNormal), &FJ_LeaderboardEntryNormal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_LeaderboardEntrySmall), &FJ_LeaderboardEntrySmall::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_LeaderboardHeaderNormal), &FJ_LeaderboardHeaderNormal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_LeaderboardHeaderSmall), &FJ_LeaderboardHeaderSmall::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_LeaderboardList), &FJ_LeaderboardList::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_IconSlot), &FJ_IconSlot::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ToolTip_Normal), &FJ_ToolTip_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ToolTip_Small), &FJ_ToolTip_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label), &FJ_Label::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Blink_Normal), &FJ_Label_Blink_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Blink_Small), &FJ_Label_Blink_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ScrollArrow), &FJ_ScrollArrow::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ScrollArrowH), &FJ_ScrollArrowH::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Slider_Normal), &FJ_Slider_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Slider_Small), &FJ_Slider_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_TexturePackList), &FJ_TexturePackList::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_TexturePackList_Slot), &FJ_TexturePackList_Slot::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_SlotList), &FJ_SlotList::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_SlotList_Slot), &FJ_SlotList_Slot::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_CheckBox_Normal), &FJ_CheckBox_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_CheckBox_Small), &FJ_CheckBox_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_SlotList), &FJ_SlotList::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_SlotList_Slot), &FJ_SlotList_Slot::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ExlamationMark), &FJ_ExlamationMark::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Cursor_Normal), &FJ_Cursor_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Cursor_Small), &FJ_Cursor_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_MobEffect_Small), &FJ_MobEffect_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_MobEffect_Normal), &FJ_MobEffect_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_TouchControl), &FJ_TouchControl::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_TouchControlFrontend), &FJ_TouchControlFrontend::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_BitmapIcon), &FJ_BitmapIcon::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_List_MultiList), &FJ_List_MultiList::Create));
    sNodes.emplace(std::make_pair(std::string(CreditsMenu), &FJ_CreditsMenu::Create));
    sNodes.emplace(std::make_pair(std::string(EndPoem), &FJ_EndPoem::Create));
    sNodes.emplace(std::make_pair(std::string(MainMenu), &FJ_MainMenu::Create));
    sNodes.emplace(std::make_pair(std::string(LoadMenu), &FJ_LoadMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SaveMessage), &FJ_SaveMessage::Create));
    sNodes.emplace(std::make_pair(std::string(ComponentLogo), &FJ_ComponentLogo::Create));
    sNodes.emplace(std::make_pair(std::string(Panorama), &FJ_Panorama::Create));
    sNodes.emplace(std::make_pair(std::string(ToolTips), &FJ_ToolTips::Create));
    sNodes.emplace(std::make_pair(std::string(Intro), &FJ_Intro::Create));
    sNodes.emplace(std::make_pair(std::string(LoadCreateJoinMenu), &FJ_LoadCreateJoinMenu::Create));
    sNodes.emplace(std::make_pair(std::string(Hud), &FJ_Hud::Create));
    sNodes.emplace(std::make_pair(std::string(HowToPlayMenu), &FJ_HowToPlayMenu::Create));
    sNodes.emplace(std::make_pair(std::string(HowToPlay), &FJ_HowToPlay::Create));
    sNodes.emplace(std::make_pair(std::string(CreativeMenu), &FJ_CreativeMenu::Create));
    sNodes.emplace(std::make_pair(std::string(CraftingMenu), &FJ_CraftingMenu::Create));
    sNodes.emplace(std::make_pair(std::string(InventoryMenu), &FJ_InventoryMenu::Create));
    sNodes.emplace(std::make_pair(std::string(FullscreenProgress), &FJ_FullscreenProgress::Create));
    sNodes.emplace(std::make_pair(std::string(Eula), &FJ_Eula::Create));
    sNodes.emplace(std::make_pair(std::string(MessageBox), &FJ_MessageBox::Create));
    sNodes.emplace(std::make_pair(std::string(PauseMenu), &FJ_PauseMenu::Create));
    sNodes.emplace(std::make_pair(std::string(HelpAndOptionsMenu), &FJ_HelpAndOptionsMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SettingsMenu), &FJ_SettingsMenu::Create));
    sNodes.emplace(std::make_pair(std::string(MCBREUpSell), &FJ_MCBREUpSell::Create));
    sNodes.emplace(std::make_pair(std::string(AnvilMenu), &FJ_AnvilMenu::Create));
    sNodes.emplace(std::make_pair(std::string(BeaconMenu), &FJ_BeaconMenu::Create));
    sNodes.emplace(std::make_pair(std::string(BrewingStandMenu), &FJ_BrewingStandMenu::Create));
    sNodes.emplace(std::make_pair(std::string(ClassicCraftingMenu), &FJ_ClassicCraftingMenu::Create));
    sNodes.emplace(std::make_pair(std::string(ChestMenu), &FJ_ChestMenu::Create));
    sNodes.emplace(std::make_pair(std::string(DispenserMenu), &FJ_DispenserMenu::Create));
    sNodes.emplace(std::make_pair(std::string(EnchantingMenu), &FJ_EnchantingMenu::Create));
    sNodes.emplace(std::make_pair(std::string(FurnaceMenu), &FJ_FurnaceMenu::Create));
    sNodes.emplace(std::make_pair(std::string(HopperMenu), &FJ_HopperMenu::Create));
    sNodes.emplace(std::make_pair(std::string(HorseInventoryMenu), &FJ_HorseInventoryMenu::Create));
    sNodes.emplace(std::make_pair(std::string(BookAndQuillMenu), &FJ_BookAndQuillMenu::Create));
    sNodes.emplace(std::make_pair(std::string(ControlsMenu), &FJ_ControlsMenu::Create));
    sNodes.emplace(std::make_pair(std::string(PressStartToPlay), &FJ_PressStartToPlay::Create));
    sNodes.emplace(std::make_pair(std::string(SuperFlatMenu), &FJ_SuperFlatMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SuperFlatPresets), &FJ_SuperFlatPresets::Create));
    sNodes.emplace(std::make_pair(std::string(SuperFlatEditLayerMenu), &FJ_SuperFlatEditLayerMenu::Create));
    sNodes.emplace(std::make_pair(std::string(QuadrantSignin), &FJ_QuadrantSignin::Create));
    sNodes.emplace(std::make_pair(std::string(LeaderboardMenu), &FJ_LeaderboardMenu::Create));
    sNodes.emplace(std::make_pair(std::string(TradingMenu), &FJ_TradingMenu::Create));
    sNodes.emplace(std::make_pair(std::string(GameModeScoreboard), &FJ_GameModeScoreboard::Create));
    sNodes.emplace(std::make_pair(std::string(BiomeSelectMenu), &FJ_BiomeSelectMenu::Create));
    sNodes.emplace(std::make_pair(std::string(ComponentChat), &FJ_ComponentChat::Create));
    sNodes.emplace(std::make_pair(std::string(DeathMenu), &FJ_DeathMenu::Create));
    sNodes.emplace(std::make_pair(std::string(DebugBuildTools), &FJ_DebugBuildTools::Create));
    sNodes.emplace(std::make_pair(std::string(DebugCreateSchematic), &FJ_DebugCreateSchematic::Create));
    sNodes.emplace(std::make_pair(std::string(DebugFillArea), &FJ_DebugFillArea::Create));
    sNodes.emplace(std::make_pair(std::string(DebugMarketingGuide), &FJ_DebugMarketingGuide::Create));
    sNodes.emplace(std::make_pair(std::string(DebugMenu), &FJ_DebugMenu::Create));
    sNodes.emplace(std::make_pair(std::string(DebugOptions), &FJ_DebugOptions::Create));
    sNodes.emplace(std::make_pair(std::string(DebugPuppeteer), &FJ_DebugPuppeteer::Create));
    sNodes.emplace(std::make_pair(std::string(DebugSetCamera), &FJ_DebugSetCamera::Create));
    sNodes.emplace(std::make_pair(std::string(DLCMainMenu), &FJ_DLCMainMenu::Create));
    sNodes.emplace(std::make_pair(std::string(DLCOffersMenu), &FJ_DLCOffersMenu::Create));
    sNodes.emplace(std::make_pair(std::string(GameModeSelection), &FJ_GameModeSelection::Create));
    sNodes.emplace(std::make_pair(std::string(Gamertag), &FJ_Gamertag::Create));
    sNodes.emplace(std::make_pair(std::string(JoinGameFilterList), &FJ_JoinGameFilterList::Create));
    sNodes.emplace(std::make_pair(std::string(JoinMenu), &FJ_JoinMenu::Create));
    sNodes.emplace(std::make_pair(std::string(LoadOrJoinMenu), &FJ_LoadOrJoinMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SaveMenu), &FJ_SaveMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SettingsAudioMenu), &FJ_SettingsAudioMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SettingsControlMenu), &FJ_SettingsControlMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SettingsGraphicsMenu), &FJ_SettingsGraphicsMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SettingsOptionsMenu), &FJ_SettingsOptionsMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SettingsUIMenu), &FJ_SettingsUIMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SignEntryMenu), &FJ_SignEntryMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SocialPost), &FJ_SocialPost::Create));
    sNodes.emplace(std::make_pair(std::string(WiiUDRC), &FJ_WiiUDRC::Create));
    sNodes.emplace(std::make_pair(std::string(AchievementsMenu), &FJ_AchievementsMenu::Create));
    sNodes.emplace(std::make_pair(std::string(AvatarSelectMenu), &FJ_AvatarSelectMenu::Create));
    sNodes.emplace(std::make_pair(std::string(CreateWorldMenu), &FJ_CreateWorldMenu::Create));
    sNodes.emplace(std::make_pair(std::string(LaunchMoreOptionsMenu), &FJ_LaunchMoreOptionsMenu::Create));
    sNodes.emplace(std::make_pair(std::string(TutorialPopup), &FJ_TutorialPopup::Create));
    sNodes.emplace(std::make_pair(std::string(MultilistMenu), &FJ_MultilistMenu::Create));
    sNodes.emplace(std::make_pair(std::string(SkinSelect), &FJ_SkinSelect::Create));
    sNodes.emplace(std::make_pair(std::string(InGamePlayerOptions), &FJ_InGamePlayerOptions::Create));
    sNodes.emplace(std::make_pair(std::string(InGameHostOptions), &FJ_InGameHostOptions::Create));
    sNodes.emplace(std::make_pair(std::string(InGameInfoMenu), &FJ_InGameInfoMenu::Create));
    sNodes.emplace(std::make_pair(std::string(InGameTeleportMenu), &FJ_InGameTeleportMenu::Create));
    sNodes.emplace(std::make_pair(std::string(MapSelectMenu), &FJ_MapSelectMenu::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DragonHealth_01), &FJ_DragonHealth_01::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DragonHealth_02), &FJ_DragonHealth_02::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DragonHealth_03), &FJ_DragonHealth_03::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DragonHealth_04), &FJ_DragonHealth_04::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DragonHealth_05), &FJ_DragonHealth_05::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_HorseJumpBar), &FJ_HorseJumpBar::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ExperienceBar), &FJ_ExperienceBar::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_BrewingArrow), &FJ_BrewingArrow::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_BrewingArrow_Small), &FJ_BrewingArrow_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_BrewingBubbles), &FJ_BrewingBubbles::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_BrewingBubbles_Small), &FJ_BrewingBubbles_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_BrewingPlate), &FJ_BrewingPlate::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_BrewingPlate_Small), &FJ_BrewingPlate_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_FurnaceArrow), &FJ_FurnaceArrow::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_FurnaceArrow_Small), &FJ_FurnaceArrow_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_FurnaceFlame), &FJ_FurnaceFlame::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_FurnaceFlame_Small), &FJ_FurnaceFlame_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_KillBar), &FJ_KillBar::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_KillBarSmall), &FJ_KillBarSmall::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ProgressBar_Loading), &FJ_ProgressBar_Loading::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_AttackIndicatorCrosshair), &FJ_AttackIndicatorCrosshair::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_AttackIndicatorHotbar), &FJ_AttackIndicatorHotbar::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_SpaceIndicatorBar), &FJ_SpaceIndicatorBar::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_TextInput), &FJ_TextInput::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_TextInput_Small), &FJ_TextInput_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_TextInput_Normal), &FJ_TextInput_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_TextInput_Vita), &FJ_TextInput_Vita::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_HtmlTextPanel), &FJ_HtmlTextPanel::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_HtmlTextPanelLarge), &FJ_HtmlTextPanelLarge::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_BigBlack), &FJ_Label_BigBlack::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_BigGrey), &FJ_Label_BigGrey::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_BigWhite), &FJ_Label_BigWhite::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Black), &FJ_Label_Black::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Black_Centered), &FJ_Label_Black_Centered::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_Black_Centered_HUD), &FJ_Label_Black_Centered_HUD::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_Black_Small_Centered), &FJ_Label_Black_Small_Centered::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Black_Small_Centered_HUD),
                                  FJ_Label_Black_Small_Centered_HUD::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Black_VerySmall_Centered),
                                  FJ_Label_Black_VerySmall_Centered::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Blink_Normal), &FJ_Label_Blink_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Blink_Small), &FJ_Label_Blink_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Book_Normal), &FJ_Label_Book_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Book_Small), &FJ_Label_Book_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Book_VerySmall), &FJ_Label_Book_VerySmall::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Credits_10), &FJ_Label_Credits_10::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_Credits_10_Yellow), &FJ_Label_Credits_10_Yellow::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Credits_20), &FJ_Label_Credits_20::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_Credits_20_Yellow), &FJ_Label_Credits_20_Yellow::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Credits_30), &FJ_Label_Credits_30::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_DragonHealth), &FJ_Label_DragonHealth::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_DragonHealthBig), &FJ_Label_DragonHealthBig::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_DragonHealthSmall), &FJ_Label_DragonHealthSmall::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_DragonHealthVerySmall), &FJ_Label_DragonHealthVerySmall::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Green), &FJ_Label_Green::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Grey), &FJ_Label_Grey::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Html), &FJ_Label_Html::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HtmlEndPoem), &FJ_Label_HtmlEndPoem::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HtmlEndPoemHD), &FJ_Label_HtmlEndPoemHD::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HtmlSmall), &FJ_Label_HtmlSmall::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_Level_01), &FJ_Label_HUD_Level_01::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_Level_02), &FJ_Label_HUD_Level_02::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_Level_03), &FJ_Label_HUD_Level_03::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_Level_04), &FJ_Label_HUD_Level_04::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_Level_05), &FJ_Label_HUD_Level_05::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_SmallWhite), &FJ_Label_HUD_SmallWhite::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_BigWhite), &FJ_Label_HUD_BigWhite::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_Splash), &FJ_Label_HUD_Splash::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_SplashBig), &FJ_Label_HUD_SplashBig::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_SplashVita), &FJ_Label_HUD_SplashVita::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_HUD_VerySmallWhite), &FJ_Label_HUD_VerySmallWhite::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_HUD_White), &FJ_Label_HUD_White::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_OutlineLevel), &FJ_Label_OutlineLevel::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_OutlineLevel_Small), &FJ_Label_OutlineLevel_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_OutlineTitle), &FJ_Label_OutlineTitle::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_OutlineTitle_Small), &FJ_Label_OutlineTitle_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_Red), &FJ_Label_Red::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SkinSelect), &FJ_Label_SkinSelect::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_SkinSelectCenter), &FJ_Label_SkinSelectCenter::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_SkinSelectCenter_Off), &FJ_Label_SkinSelectCenter_Off::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SkinSelectCenter_Small),
                                  FJ_Label_SkinSelectCenter_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SkinSelectCenter_Small_Off),
                                  FJ_Label_SkinSelectCenter_Small_Off::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SkinSelect_Off), &FJ_Label_SkinSelect_Off::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_SkinSelect_Small), &FJ_Label_SkinSelect_Small::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_SkinSelect_Small_Off), &FJ_Label_SkinSelect_Small_Off::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SmallBlack), &FJ_Label_SmallBlack::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SmallGreen), &FJ_Label_SmallGreen::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SmallGrey), &FJ_Label_SmallGrey::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SmallRed), &FJ_Label_SmallRed::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_SmallWhite), &FJ_Label_SmallWhite::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_VerySmallBlack), &FJ_Label_VerySmallBlack::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_VerySmallGrey), &FJ_Label_VerySmallGrey::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_VerySmallWhite), &FJ_Label_VerySmallWhite::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_White), &FJ_Label_White::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_WhiteHtml), &FJ_Label_WhiteHtml::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_WhiteHtmlSmall), &FJ_Label_WhiteHtmlSmall::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_White_Centered), &FJ_Label_White_Centered::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_Label_White_Small_Centered), &FJ_Label_White_Small_Centered::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Label_White_VerySmall_Centered),
                                  FJ_Label_White_VerySmall_Centered::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListLabel_Black), &FJ_ListLabel_Black::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_ListLabel_SmallBlack), &FJ_ListLabel_SmallBlack::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_HtmlText_Normal), &FJ_HtmlText_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_HtmlText_Small), &FJ_HtmlText_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_HtmlText_WhiteNormal), &FJ_HtmlText_WhiteNormal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_HtmlText_WhiteSmall), &FJ_HtmlText_WhiteSmall::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_HtmlText_WithPanel_Normal), &FJ_HtmlText_WithPanel_Normal::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_HtmlText_WithPanel_Small), &FJ_HtmlText_WithPanel_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DynamicHtmlText), &FJ_DynamicHtmlText::Create));
    sNodes.emplace(
        std::make_pair(std::string(FJ_DynamicHtmlText_Normal), &FJ_DynamicHtmlText_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DynamicHtmlText_Small), &FJ_DynamicHtmlText_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DynamicHtmlText_WithPanel_Normal),
                                  FJ_DynamicHtmlText_WithPanel_Normal::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_DynamicHtmlText_WithPanel_Small),
                                  FJ_DynamicHtmlText_WithPanel_Small::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_SignInput), &FJ_SignInput::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_panel9Grid_16Fade), &FJ_panel9Grid_16Fade::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_Panel9GridFade), &FJ_Panel9GridFade::Create));
    sNodes.emplace(std::make_pair(std::string(FJ_PanelRecessFade), &FJ_PanelRecessFade::Create));
}