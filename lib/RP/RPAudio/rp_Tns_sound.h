#ifndef RP_AUDIO_RP_TNS_SOUND_RSAR_H
#define RP_AUDIO_RP_TNS_SOUND_RSAR_H

enum rp_Tns_sound {
    /* 0x00 */ SE_TR_TARGET_CRUSH,
    /* 0x01 */ SE_TR_WALL_CRUSH,
    /* 0x02 */ SE_TR_SERVE,
    /* 0x03 */ SE_TR_SERVE_TVSP,
    /* 0x04 */ SE_TR_SERVE_CPU,
    /* 0x05 */ SE_TR_SERVE_Rocket_CTSP,
    /* 0x06 */ SE_TR_SERVE_Rocket_TVSP,
    /* 0x07 */ SE_TR_SERVE_Rocket_CPU,
    /* 0x08 */ SE_TR_RECEIVE,
    /* 0x09 */ SE_TR_RECEIVE_TVSP,
    /* 0x0A */ SE_TR_RECEIVE_CPU,
    /* 0x0B */ SE_TR_RACKET_FURU,
    /* 0x0C */ SE_TR_RACKET_FURU_TVSP,
    /* 0x0D */ SE_TR_RACKET_FURU_CPU,
    /* 0x0E */ SE_TR_Toss,
    /* 0x0F */ SE_TR_Toss_TVSP,
    /* 0x10 */ SE_TR_Toss_CPU,
    /* 0x11 */ SE_TR_PositionCursol,
    /* 0x12 */ SE_TR_PositionCursol_TVSP,
    /* 0x13 */ SE_TR_PositionSelect,
    /* 0x14 */ SE_TR_PositionSelect_TVSP,
    /* 0x15 */ SE_TR_PositionCancel,
    /* 0x16 */ SE_TR_PositionCancel_TVSP,
    /* 0x17 */ SE_TR_StartGame,
    /* 0x18 */ SE_TR_StartGame_TVSP,
    /* 0x19 */ SE_TR_BALL_BOUND,
    /* 0x1A */ SE_TR_WALLHIT,
    /* 0x1B */ SE_TR_NETHIT,
    /* 0x1C */ SE_TR_run_grass1,
    /* 0x1D */ SE_TR_run_grass2,
    /* 0x1E */ SE_TR_run_grass3,
    /* 0x1F */ SE_TR_run_grass4,
    /* 0x20 */ SE_TR_Hit_OK_Area_Pole,
    /* 0x21 */ SE_TR_HitNetPole,
    /* 0x22 */ SE_TR_KokeshiKokeru,
    /* 0x23 */ SE_TR_OK_AREA_PATH,
    /* 0x24 */ SE_TR_RenzokuReturn_CourtIn,
    /* 0x25 */ SE_TR_OK,
    /* 0x26 */ SE_TR_RenzokuReturn_CourtOut,
    /* 0x27 */ SE_TR_ScoreDispChange,
    /* 0x28 */ SE_TR_WinGameDispChange,
    /* 0x29 */ SE_TR_WinGameDispChange_L,
    /* 0x2A */ SE_TR_WinGameDispChange_R,
    /* 0x2B */ SE_TR_GameSet,
    /* 0x2C */ SE_TR_run_HardCourt1,
    /* 0x2D */ SE_TR_run_HardCourt2,
    /* 0x2E */ SE_TR_run_HardCourt3,
    /* 0x2F */ SE_TR_run_HardCourt4,
    /* 0x30 */ SE_TR_StartFlyIn,
    /* 0x31 */ SE_TR_ZeneiKoueiChange,
    /* 0x32 */ SE_LV_Kansei_Replay,
    /* 0x33 */ SE_LV_TrainingStartENV,
    /* 0x34 */ SE_LV_ServeWait_Zawameki,
    /* 0x35 */ SE_TR_KANSEI_HAKUSHU,
    /* 0x36 */ SE_TR_KANSEI_ODOROKI,
    /* 0x37 */ SE_TR_KANSEI_ODOROKI_SMALL,
    /* 0x38 */ SE_TR_KANSEI_RAKUTAN,
    /* 0x39 */ SE_TR_KANSEI_GameSet,
    /* 0x3A */ SE_TR_KANSEI_OK,
    /* 0x3B */ SE_TR_KANSEI_TARGET_CRUSH,
    /* 0x3C */ SE_TR_KANSEI_Hit_OK_Area_Pole,
    /* 0x3D */ SE_TR_KANSEI_RenzokuReturn_CourtOut,
    /* 0x3E */ SE_TR_KANSEI_NeraiUchi_CourtOut,
    /* 0x3F */ SE_TR_KANSEI_KabeUchi_CourtOut,
    /* 0x40 */ BGM_SelectPosition,
    /* 0x41 */ BGM_GameResultDisp,
    /* 0x42 */ BGM_TrainingResultDisp,
    /* 0x43 */ BGM_GameSetReplay,
    /* 0x44 */ BGM_Training_Kabeuchi,
    /* 0x45 */ BGM_Training_Nerauchii,
    /* 0x46 */ BGM_Training_Renzoku,
    /* 0x47 */ Fanfare_Set,
    /* 0x48 */ VOICE_TR_Love_Fifteen,
    /* 0x49 */ VOICE_TR_Love_Thirty,
    /* 0x4A */ VOICE_TR_Love_Forty,
    /* 0x4B */ VOICE_TR_Fifteen_Love,
    /* 0x4C */ VOICE_TR_Fifteen_all,
    /* 0x4D */ VOICE_TR_Fifteen_Thirty,
    /* 0x4E */ VOICE_TR_Fifteen_Forty,
    /* 0x4F */ VOICE_TR_Thirty_Love,
    /* 0x50 */ VOICE_TR_Thirty_Fifteen,
    /* 0x51 */ VOICE_TR_Thirty_all,
    /* 0x52 */ VOICE_TR_Thirty_Forty,
    /* 0x53 */ VOICE_TR_Forty_Love,
    /* 0x54 */ VOICE_TR_Forty_Fifteen,
    /* 0x55 */ VOICE_TR_Forty_Thirty,
    /* 0x56 */ VOICE_TR_Forty_all_Deuce,
    /* 0x57 */ VOICE_TR_Deuce,
    /* 0x58 */ VOICE_TR_Advantage_Front_Team,
    /* 0x59 */ VOICE_TR_Advantage_Rear_Team,
    /* 0x5A */ VOICE_TR_Advantage_Left_Team,
    /* 0x5B */ VOICE_TR_Advantage_Right_Team,
    /* 0x5C */ VOICE_TR_Game_won_by_Front_Team,
    /* 0x5D */ VOICE_TR_Game_won_by_Rear_Team,
    /* 0x5E */ VOICE_TR_Game_won_by_Left_Team,
    /* 0x5F */ VOICE_TR_Game_won_by_Right_Team,
    /* 0x60 */ VOICE_TR_BreakPoint,
    /* 0x61 */ VOICE_TR_GamePoint,
    /* 0x62 */ VOICE_TR_MatchPoint,
    /* 0x63 */ RP_COM_GAME_SE_PAUSE_01_CTSP,
    /* 0x64 */ RP_COM_GAME_SE_PAUSE_01_TVSP,
    /* 0x65 */ RP_COM_GAME_SE_PAUSE_01,
    /* 0x66 */ FANFARE_GameSet,
    /* 0x67 */ FANFARE_GameSet_Win,
    /* 0x68 */ FANFARE_GameSet_Lose,
    /* 0x69 */ FANFARE_GameSet_Tie,
    /* 0x6A */ SE_TR_Common_KeikokuForDebug,
    /* 0x6B */ SE_TR_Common_Sports_Cursol,
    /* 0x6C */ SE_TR_Common_Sports_Decide,
    /* 0x6D */ SE_TR_Common_Sports_Decide_TVSP,
    /* 0x6E */ SE_TR_Common_Sports_DecideBig,
    /* 0x6F */ SE_TR_Common_Sports_DecideBig_TVSP,
    /* 0x70 */ SE_TR_Common_Sports_DemoSkipButton,
    /* 0x71 */ SE_TR_Common_Sports_DemoSkipButton_TVSP,
    /* 0x72 */ SE_TR_Common_Sports_Cancel,
    /* 0x73 */ SE_TR_Common_Sports_Cancel_TVSP,
    /* 0x74 */ SE_TR_Common_Sports_Wipe,
    /* 0x75 */ SE_TR_Common_Jyunban,
    /* 0x76 */ SE_TR_Common_Jyunban_TVSP,
    /* 0x77 */ SE_TR_Common_Medal_Platinum,
    /* 0x78 */ SE_TR_Common_Medal_Gold,
    /* 0x79 */ SE_TR_Common_Medal_Silver,
    /* 0x7A */ SE_TR_Common_Medal_Copper,
    /* 0x7B */ SE_TR_Common_Sports_Game_Start,
    /* 0x7C */ SE_TR_Common_Sports_Game_End,
    /* 0x7D */ SE_TR_Common_Sports_MyBestRecord,
    /* 0x7E */ SE_TR_Common_Sports_KanseiRecord,
    /* 0x7F */ SE_TR_Common_Sports_Training_Good,
    /* 0x80 */ SE_TR_Common_Sports_Training_GoodLong,
    /* 0x81 */ SE_TR_Common_Sports_Training_VeryGoodLong,
    /* 0x82 */ SE_TR_Common_Sports_Training_GoodLongSoft,
    /* 0x83 */ SE_TR_Common_Sports_Training_NotGood,
    /* 0x84 */ RP_COM_GAME_SE_PAUSE_KEY_A_02_CTSP,
    /* 0x85 */ RP_COM_GAME_SE_PAUSE_KEY_A_02_TVSP,
    /* 0x86 */ RP_COM_GAME_SE_PAUSE_KEY_A_02,
    /* 0x87 */ RP_COM_GAME_SE_PAUSE_KEY_A_03_CTSP,
    /* 0x88 */ RP_COM_GAME_SE_PAUSE_KEY_A_03_TVSP,
    /* 0x89 */ RP_COM_GAME_SE_PAUSE_KEY_A_03,
    /* 0x8A */ RP_COM_GAME_SE_PAUSE_Cursor_01,
    /* 0x8B */ SE_LV_Common_click_CTSP,
    /* 0x8C */ SE_LV_Common_click_TVSP,
    /* 0x8D */ SE_TR_Common_ModeChange_CTSP,
    /* 0x8E */ SE_TR_Common_ModeChange_TVSP,
    /* 0x8F */ SE_TR_Common_KeyError_CTSP,
    /* 0x90 */ SE_TR_Common_KeyError_TVSP,
    /* 0x91 */ RP_COMMON_SE_KEY_CURSOR_01,
    /* 0x92 */ RP_COMMON_SE_KEY_BACK_01_CTSP,
    /* 0x93 */ RP_COMMON_SE_KEY_BACK_01_TVSP,
    /* 0x94 */ SE_TR_COMMON_win_OPEN,
    /* 0x95 */ SE_TR_COMMON_win_CLOSE,
    /* 0x96 */ SE_TR_COMMON_Jyukurendo_ScoreFlash,
    /* 0x97 */ SE_TR_COMMON_Jyukurendo_NameFlash,
    /* 0x98 */ SE_TR_COMMON_Jyukurendo_NameSmoke,
    /* 0x99 */ SE_TR_COMMON_Push_AB_CTSP,
    /* 0x9A */ SE_TR_COMMON_Push_AB_TVSP,
    /* 0x9B */ VOICE_TR_Common_BronzeMedal,
    /* 0x9C */ VOICE_TR_Common_SilverMedal,
    /* 0x9D */ VOICE_TR_Common_GoldMedal,
    /* 0x9E */ VOICE_TR_Common_PlatinumMedal,
    /* 0x9F */ VOICE_TR_Common_HighScore,
    /* 0xA0 */ STRM_Training_Result01,
    /* 0xA1 */ STRM_Training_Result02,
    /* 0xA2 */ STRM_Training_Result03,
    /* 0xA3 */ Bgm_Tutorial,
    /* 0xA4 */ RP_COMMON_SE_MESS_10,
    /* 0xA5 */ RP_COMMON_SE_MESS_20,
    /* 0xA6 */ RP_COMMON_SE_KEY_A_04_CTSP,
    /* 0xA7 */ RP_COMMON_SE_KEY_A_04_TVSP,
    /* 0xA8 */ RP_COMMON_SE_KEY_A_04,
    /* 0xA9 */ RP_COM_GAME_SE_PAUSE_KEY_A_01_CTSP,
    /* 0xAA */ RP_COM_GAME_SE_PAUSE_KEY_A_01_TVSP,
    /* 0xAB */ RP_COM_GAME_SE_PAUSE_KEY_A_01
};

#endif