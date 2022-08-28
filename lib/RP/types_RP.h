#ifndef TYPES_RP_H
#define TYPES_RP_H
#include <types.h>

//! Provides year, month, month day
typedef u16 RPTime16;
//! Provides year, month, month day, week day, hour
typedef u32 RPTime32;

struct RPSysUnknownBase;

// RPGraphics
struct IRPGrpDrawObject;
struct RPGrpRenderer;
struct RPGrpModel;
struct RPGrpModelG3D;
struct RPGrpFogManager;
struct RPGrpModelBoundingInfo;
struct RPGrpShadowTexture;
struct RPGrpScreen;

// RPKernel
struct RPSysSystem;
struct RPSysFile;
struct IRPSysHostIOSocket;
struct RPSysTextWriter;
struct RPSysMessage;
struct RPSysEffect;
struct RPSysLayout;
struct RPSysKokeshiIcon;
struct RPSysWideTextWriter;
struct RPSysLytBounding;
struct RPSysLytPicture;
struct RPSysLytTextBox;
struct RPSysLytWindow;
struct RPSysLytResAccessor;
struct RPSysLytAllocator;
struct RPSysLytAnmObj;
struct RPSysLytDynamicAnm;
struct RPSysLytResAccessor;

// RPSystem
struct RPSysSceneCreator;
struct RPSysScene;
struct RPSysSceneMgr;
struct RPSysProjectLocal;
struct RPSysGameConfig;
struct RPSysTagParameters;
struct RPSysTagParm;
template <typename T> struct RPSysPrimTagParm;
struct RPSysStringTagParm;
struct RPSysResourceManager;
struct RPSysQueuedScene;
struct RPSysCommonObject;
struct RPSysDvdStatus;
struct RPSysSaveDataMgr;
struct RPSysFontManager;
struct RPSysSaveData;

// RPSports
struct RPSportsCommonData;
struct RPSportsPlayerData;
struct RPSportsSequenceMgr;
struct RPSportsBaseScene;
struct RPBoxBoxer;
struct RPBoxBoxerEnergy;
struct RPBoxBoxerCombo;
struct RPBowResourceManager;
struct RPGolMapObjBase;
struct RPGolScene;
struct RPGolFieldManager;
struct RPGolMain;
struct RPGolMapObjTree;
struct RPGolMapObjTreeWater;
struct RPGolMapObjPlayer;
struct RPGolMapObjSky;
struct RPGolMapObjTeeMarker;
struct RPGolMapObjPin;
struct RPGolMapObjTarget;
struct RPGolMapObjTargetHit;
struct RPGolMapObjCup;
struct RPGolMapObjWind;
struct RPGolConfig;

// RPParty
struct RPPartyCommonData;
struct RPPartyPlayerData;

// RPUtility
struct RPUtlMapData;
struct RPUtlMapObject;
struct RPUtlDohGraphSun;

#endif