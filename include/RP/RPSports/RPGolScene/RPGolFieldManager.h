#ifndef RP_SPORTS_GOL_FIELD_MANAGER_H
#define RP_SPORTS_GOL_FIELD_MANAGER_H
#include "RPSysUnknownBase.h"
#include "types_RP.h"

#include <nw4r/math/math_types.h>

/**
 * @brief Golf course object, effect, and shadow manager
 * @wscname
 * @todo Document all of the functions
 */
class RPGolFieldManager : RPSysUnknownBase {
public:
    enum EMapObj {
        MAP_OBJ_PLAYER = 0x00010000, //!< Player start
        MAP_OBJ_CUP,                 //!< Cup
        MAP_OBJ_TREE1,               //!< Tree (variant 1)
        MAP_OBJ_TREE2,               //!< Tree (variant 2)
        MAP_OBJ_TREE1_WATER,         //!< Tree (variant 1, reflection)
        MAP_OBJ_TREE2_WATER,         //!< Tree (variant 2, reflection)
        MAP_OBJ_TREE3,               //!< Tree (variant 3, UNUSED)
        MAP_OBJ_TREE3_WATER,         //!< Tree (variant 3, reflection, UNUSED)
        MAP_OBJ_SKY,                 //!< Skybox
        MAP_OBJ_0009,                //!< Unused slot 0x0009
        MAP_OBJ_TEE_MARKER,          //!< Tee box marker
        MAP_OBJ_TREE4,               //!< Tree (variant 4, UNUSED)
        MAP_OBJ_TREE4_WATER,         //!< Tree (variant 4, reflection, UNUSED)
        MAP_OBJ_TREE5,               //!< Tree (variant 5, UNUSED)
        MAP_OBJ_TREE5_WATER,         //!< Tree (variant 5, reflection, UNUSED)
        MAP_OBJ_000F,                //!< Unused slot 0x000F
        MAP_OBJ_0010,                //!< Unused slot 0x0010
        MAP_OBJ_TARGET_A,            //!< Target A (Large)
        MAP_OBJ_TARGET_B,            //!< Target B (Medium, UNUSED)
        MAP_OBJ_TARGET_C,            //!< Target C (Small)
        MAP_OBJ_TARGET_D             //!< Target D (Very small, UNUSED)
    };

public:
    //! @address 80294008
    static void CreateInstance();
    //! @address 80293fc4
    static void DestroyInstance();

private:
    //! @address 80293d74
    RPGolFieldManager();
    //! @address 80293d18
    virtual ~RPGolFieldManager();

private:
    //! @brief Player Mii shadow
    RPGrpShadowTexture* mPlayerShadowTexture; // at 0x4
    //! @brief Tree shadow (all objects)
    RPGrpShadowTexture* mTreeShadowTexture; // at 0x8
    //! @brief Flagpole shadow
    RPGrpShadowTexture* mFlagPoleShadow; // at 0xC

    //! @brief Allows tree shadows to update
    //! @note Set to two frames during camera transitions
    int mTreeShadowUpdateTimer; // at 0x10

    // Seems to be unused
    char UNK_0x14[0x4];

    //! @brief Course PMP data (unpacked)
    //! @note Map ID always set to 1
    RPUtlMapData* mMapData; // at 0x18

    //! @brief Tree map object count
    int mNumTreeObjs; // at 0x1C
    //! @brief Tree map object array
    RPGolMapObjTree* mTreeObjs; // at 0x20

    //! @brief Tree water (reflection) map object count
    int mNumTreeWaterObjs; // at 0x24
    //! @brief Tree water (reflection) map object array
    RPGolMapObjTreeWater* mTreeWaterObjs; // at 0x28

    //! @brief Tee marker map object
    RPGolMapObjTeeMarker* mTeeMarkerObj; // at 0x2C

    //! @brief Mato (target) map object count
    int mNumTargetObjs; // at 0x30
    //! @brief Mato (target) object array
    RPGolMapObjTarget* mTargetObjs; // at 0x34

    //! @brief Sky map object
    RPGolMapObjSky* mSkyObj; // at 0x38

    //! @brief Pin map object count
    int mNumPinObjs;                // at 0x3C
    RPGolMapObjPin* mPinObjs;       // at 0x40
    RPGolMapObjPin* mCurrentPinObj; // at 0x44

    //! @brief Player map object count
    int mNumPlayerObjs;                  // at 0x48
    RPGolMapObjPlayer* mStartObjs;       // at 0x4C
    RPGolMapObjPlayer* mCurrentStartObj; // at 0x50

    //! @brief Cup map object
    RPGolMapObjCup* mCupObj; // at 0x54

    //! @brief Course sun and lens flares
    RPUtlDohGraphSun* mSun; // at 0x58
    //! @brief Sun object position
    nw4r::math::VEC3 mSunPos; // at 0x5C

    //! @brief Wind object along with visual line effect
    RPGolMapObjWind* mWindObj; // at 0x68
    //! @brief Wind arrow visibility
    bool mShowWindArrow; // at 0x6C

    //! @brief Course model map object
    RPGolMapObjBase* mCourseObj; // at 0x70
    //! @brief Minimap course model map object
    RPGolMapObjBase* mMapCourseObj; // at 0x74
    //! @brief Minimap trees map object
    RPGolMapObjBase* mMapTreesObj; // at 0x78

    //! @brief Controls the gradient slope preview
    bool mShowGreenSlope; // at 0x7C
    //! @brief Opacity of the slope preview
    f32 mGreenSlopeOpacity; // at 0x80

    //! @brief Target hit map objects
    RPGolMapObjTargetHit* mTargetHitObjs; // at 0x84
    //! @brief Controls the minimap
    bool mShowMiniMap; // at 0x88

    //! @brief Flag icon on minimap
    RPSysEffect* mMapFlagEff; // at 0x8C
    //! @brief Cup on minimap
    RPSysEffect* mMapCupEff; // at 0x90
    //! @brief Player arrow on minimap
    RPSysEffect* mMapPlayerEff; // at 0x94
    //! @brief Shot preview line on minimap
    RPSysEffect* mMapShotLineEff; // at 0x98
    //! @brief Golf ball on minimap
    RPSysEffect* mMapBallEff; // at 0x9C
    //! @brief Yellow target diamond on minimap
    RPSysEffect* mMapTargetEff; // at 0xA0

    //! @brief Set to kill the target effect emitters
    //! @note Used to achieve the blinking effect
    bool mKillTargetEffEmitter; // at 0xA4

    /**
     * @brief Static instance
     * @address 804bf868
     */
    static RPGolFieldManager* sInstance;
};

#endif