#ifndef SPORTSNET_CORE_SCENE_CREATOR_EX_H
#define SPORTSNET_CORE_SCENE_CREATOR_EX_H
#include "types.h"

#include <RPSystem/RPSysScene.h>
#include <RPSystem/RPSysSceneCreator.h>

namespace spnet {

/**
 * @brief RP scene creator extension to support SportsNet scenes
 */
class SceneCreatorEx : public RPSysSceneCreator {
public:
    //! All scenes
    enum ESceneIDEx {
        // System scenes
        RP_BOOT_SCENE,
        RP_PLAYER_SELECT_SCENE,
        RP_NUNCHAKU_SCENE,

        // Sports Pack scenes
        RP_BSB_SCENE,
        RP_BOW_SCENE,
        RP_GOL_SCENE,
        RP_TNS_SCENE,
        RP_BOX_SCENE,
        RP_SPORTS_TITLE_SCENE,
        RP_SPORTS_MENU_SCENE,
        RP_TRAIN_MENU_SCENE,
        RP_PHYSICAL_MENU_SCENE,
        RP_PHYSICAL_PREVIEW_SCENE,
        RP_PHYSICAL_RESULT_SCENE,
        RP_GOL_SELECT_SCENE,

        // Party Pack scenes
        RP_FSH_SCENE,
        RP_HKY_SCENE,
        RP_DUC_SCENE,
        RP_PNP_SCENE,
        RP_BIL_SCENE,
        RP_COW_SCENE,
        RP_WLY_SCENE,
        RP_TNK_SCENE,
        RP_BOM_SCENE,
        RP_SCENE_18H,
        RP_PARTY_TITLE_SCENE,
        RP_SCENE_1AH,

        // Health Pack scenes
        RP_HEALTH_TITLE_SCENE,
        RP_HEALTH_COUNSEL_SCENE,
        RP_HEALTH_YOGA_SCENE,
        RP_HEALTH_TRAINING_SCENE,
        RP_HEALTH_RADIO_GYM_SCENE,
        RP_HEALTH_GRAPH_SCENE,
        RP_HEALTH_BALANCE_SCENE,
        RP_HEALTH_SKI_SCENE,
        RP_SCENE_23H,
        RP_SCENE_24H,

        // Music Pack scenes
        RP_DRM_SCENE,
        RP_OCH_SCENE,
        RP_MPE_1_SCENE,
        RP_MPE_2_SCENE,
        RP_MPE_3_SCENE,
        RP_MPE_4_SCENE,
        RP_MPE_5_SCENE,
        RP_MUSIC_TITLE_SCENE,

        // All pack scenes
        RP_ALL_PACK_SCENE,
        RP_BASIC_DEBUG_SCENE,
        RP_GRAPHICS_DEBUG_SCENE,
        RP_SYSTEM_DEBUG_SCENE,
        RP_LAYOUT_DEBUG_SCENE,
        RP_CURSOR_DEBUG_SCENE,
        RP_VIBRATION_DEBUG_SCENE,
        RP_RESULT_DEBUG_SCENE,
        RP_UI_DEBUG_SCENE,
        RP_SMK_TRAINING_SCENE,
        RP_MNT_TRAINING_SCENE,
        RP_BSB_DEBUG_SCENE,
        RP_DRM_DEBUG_SCENE,
        RP_OCH_DEBUG_SCENE,
        RP_OCH_MUSIC_SELECT_SCENE,

        // SportsNet scenes
        SPNET_LOBBY_SCENE,

        SCENE_MAX,

        RP_SCENE_MAX = RP_GOL_SELECT_SCENE + 1
    };

public:
    static SceneCreatorEx& GetInstance() {
        RPSysSceneCreator* base = RPSysSceneCreator::getInstance();
        MATO_ASSERT(base != NULL);
        return *reinterpret_cast<SceneCreatorEx*>(base);
    }

    RPSysScene* Create(ESceneIDEx id);
    RPSysScene* CreateSystemScene(ESceneIDEx id);
    RPSysScene* CreateSportsScene(ESceneIDEx id);
    RPSysScene* CreateSportsNetScene(ESceneIDEx id);
    bool ChangeSceneAfterFade(ESceneIDEx id, bool reload);

    ESceneIDEx GetSceneID(ESportID id) const;
    ESportID GetSportID(ESceneIDEx id) const;

    EPackID GetPackID(ESceneIDEx id) const;
    s32 GetCreateType(ESceneIDEx id) const;
    bool GetShowLoadingText(ESceneIDEx id) const;
    s32 GetExitType(ESceneIDEx id) const;
    bool GetUseCommonSound(ESceneIDEx id) const;
    const char* GetResDirName(ESceneIDEx id) const;
    const char* GetSceneName(ESceneIDEx id) const;

private:
    // SceneCreatorEx should not be instantiated
    SceneCreatorEx();
    SceneCreatorEx(const SceneCreatorEx&);
    ~SceneCreatorEx();

    s32 GetTableIndex(ESceneIDEx id) const;

private:
    static const SceneAttributes sSceneAttrTable[SCENE_MAX];
};

} // namespace spnet

#endif